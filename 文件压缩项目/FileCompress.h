#pragma once
#pragma warning(disable:4996)

#include <iostream>

//########################################################
//###################   头文件  ##########################
//########################################################

#include <string>
using namespace std;
#include "HuffmanTree.h"

//########################################################
//#################   文件压缩类  ########################
//########################################################

//存储信息，存放字符，字符出现次数，编码
struct CharData {
	char _ch;
	size_t _count;
	string code;

	bool operator==(const CharData& data)
	{
		return _count == data._count;
	}
	bool operator!=(const CharData& data)
	{
		return !(operator==(data));
	}
	CharData operator+(const CharData& data)
	{
		CharData ret;
		ret._count = _count + data._count;
		return ret;
	}
	bool operator>(const CharData& data)
	{
		return (_count > data._count);
	}
	bool operator<(const CharData& data)
	{
		return (_count < data._count);
	}
};


class FileCompress {
	typedef struct HuffmanTreeNode<CharData> Node;
public:
	FileCompress();//缺省构造函数
	void Compress(const char* file);//压缩准备
	void _Docompress(const char* file);//开始压缩
	void UnCompress(const char* file);//解压准备
	void _Douncompress(const char* file, FILE* fp_r, Node* _root);//开始解压
	void CreateHuffmanCode(Node* root);//生成Huffman编码

private:
	CharData _hashtable[256];
};

FileCompress::FileCompress()//缺省构造函数
{
	//哈希表初始化
	for (int i = 0; i < 256; i++)
	{
		_hashtable[i]._ch = i;
		_hashtable[i]._count = 0;
	}	

}
void FileCompress::Compress(const char* file)//压缩准备
{
	cout << "压缩准备阶段..." << endl;
	//1. 统计字符个数，并写入哈希表中
	FILE* fp = fopen(file,"r");
	int ch;
	while ((ch = fgetc(fp)) != EOF)
	{
		_hashtable[ch]._count++;
	}
	cout << "源文件数据统计 完成..." << endl;

	//2. 用哈希表构建huffmanTree
	CharData end;
	end._count = 0;
	HuffmanTree<CharData> Tree(_hashtable, 256, end);
	cout << "Huffman树构建 完成..." << endl;
	//3. 根据huffmanTree生成Huffman编码
	CreateHuffmanCode(Tree.GetRoot());
	cout << "生成Huffman编码 完成..." << endl;

	//4. 开始压缩
	cout << "开始压缩..." << endl;
	_Docompress(file);
	cout << "压缩完成..." << endl;
}

void FileCompress::_Docompress(const char* file)//开始压缩
{
	//1. 构建压缩文件
	string FileName = file;
	FileName = FileName + ".huffman";
	FILE *fp_w = fopen(FileName.c_str(), "wb");

	//2. 先将统计好的字符和字符数写入压缩文件中，方便解压
	struct _data {
		char _ch;
		size_t _count;
	}data;
	int num = 0;
	for (int i = 0; i < 256; i++)
	{
		if (_hashtable[i]._count > 0)
		{
			++num;
			data._ch = i;
			data._count = _hashtable[i]._count;
			fwrite(&data, sizeof(data), 1, fp_w);
		}
	}
	cout << num << endl;
	data._count = 0;
	fwrite(&data, sizeof(data), 1, fp_w);

	//3. 从源文件中读取一个字符根据HuffmanTree,构成几个编码位并
	//	 保存下来,够8位将其写入压缩文件,直到源文件全部被读取完
	FILE *fp_r = fopen(file, "r");
	int ch; //读取字符
	int n = 0; //记录比特位数
	char buf; //存放压缩编码

	//while (!feof(fp_r))
	//{
	//	ch = fgetc(fp_r);
	//	if (ch == EOF)
	//		printf("saf");
	//	string* code = &_hashtable[ch].code; //获得字符代码
	//	for (int i = 0; i < code->size(); i++)
	//	{
	//		buf |= 1 << n++;
	//		if (n > 7)
	//		{
	//			fputc((int)ch, fp_w);
	//			n = 0;
	//		}
	//	}
	//}

	while ((ch = fgetc(fp_r)) != EOF)
	{
		string code = _hashtable[ch].code; //获得字符代码
		for (int i = 0; i < code.size(); i++)
		{

			if (code[i] == '1')
				buf |= (1 << n++);
			else
				buf &= ~(1 << n++);
			if (n > 7)
			{
				//for (int i = 0; i < 8; i++)
				//{
				//	if ( buf & (1 << i))
				//		cout << 1;
				//	else cout << 0;
				//}
				//cout << endl;

				fputc((int)buf, fp_w);
				n = 0;
			}

		}
	}
	if (n < 7)
	{
		//for (int i = 0; i < n; i++)
		//{
		//	if (  buf & (1 << i) )
		//		cout << 1;
		//	else cout << 0;
		//}
		//cout << endl;

		fputc((int)buf, fp_w);
	}
	fclose(fp_r);
	fclose(fp_w);
}

void FileCompress::UnCompress(const char* file)//解压准备
{
	cout << "解压准备..." << endl;
	//1.先从压缩文件中将要构成HuffmanTree的数据(字符和字符总数)取出
	struct Data { char _ch; size_t _count; }data;
	FILE* fp_r = fopen(file, "rb");
	fread(&data, sizeof(data), 1, fp_r);
	int num = 0;
	while (data._count != 0)
	{
		_hashtable[(unsigned char)data._ch]._count = data._count;
		fread(&data, sizeof(data), 1, fp_r);
		cout << num++ << endl;
	}

	//2.构建HuffmanTree
	CharData end;
	end._count = 0;
	HuffmanTree<CharData> tree(_hashtable, 256, end);
	cout << "huffman树构建..." << endl;

	//3.开始解压
	cout << "开始解压..." << endl;
	_Douncompress(file, fp_r, tree.GetRoot());
	cout << "解压完成..." << endl;
}
void  FileCompress::_Douncompress(const char* file, FILE* fp_r, Node* _root)//开始解压
{
	//1.创建解压文件
	string FileName = file;
	for (int i = 0; i < 7; i++)
		FileName.pop_back();
	FileName += "un";
	FILE* fp_w = fopen(FileName.c_str(), "w");



	//2.从压缩文件中读取一个字符，开始从HuffmanTree上开始查找，直到叶子结点，写入解压文件
	int ch = 0;
	int num = _root->_data._count;
	Node* cur = _root;
	while ( num > 0)
	{
		ch = fgetc(fp_r);
		for (int i = 0; i < 8; i++)
		{
			if ((ch & (1 << i)) ) //为1
				cur = cur->_left;
			else
				cur = cur->_right;
			if (cur && cur->_left == NULL && cur->_right == NULL)//找到叶子结点
			{
				--num;
				fputc((int)cur->_data._ch, fp_w);
				cur = _root;
				if (num == 0)
					break;
			}
		}
	}


	fclose(fp_w);
	fclose(fp_r);
}
void FileCompress::CreateHuffmanCode(Node* root)//生成Huffman编码
{
	//根据HuffmanTree,使用递归，在父结点的左边，代码+1，反之+0
	if (root == NULL)
		return;

	Node* parent = root->_parent;
	if (parent)
	{
		if (root == parent->_left)//左边+1
			root->_data.code = parent->_data.code + "1";
		else
			root->_data.code = parent->_data.code + "0";
	}
	//如果是叶子结点，就把编码写进hashtable里存储
	if (root->_left == NULL && root->_right == NULL)
	{
		_hashtable[(unsigned char)root->_data._ch].code = root->_data.code;
		return;
	}


	CreateHuffmanCode(root->_left);
	CreateHuffmanCode(root->_right);
}
