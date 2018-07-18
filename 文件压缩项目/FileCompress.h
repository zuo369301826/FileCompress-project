#pragma once
#pragma warning(disable:4996)

//########################################################
//###################   头文件  ##########################
//########################################################

#include <string>
using namespace std;
#include "HuffmanTree.h"

//########################################################
//#################   文件压缩类  ########################
//########################################################

//结点信息，存放字符，出现此时，编码
struct CharData {
	unsigned char _ch;
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
	void _Douncompress(const char* file);//开始解压
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
	//1. 统计字符个数，并写入哈希表中
	FILE* fp = fopen(file,"r");
	unsigned char ch;
	while ((ch = fgetc(fp)) && (char)ch != EOF)
	{
		_hashtable[ch]._count++;
	}

	//2. 用哈希表构建huffmanTree
	CharData end;
	end._count = 0;
	HuffmanTree<CharData> Tree(_hashtable, 256, end);
	
	//3. 根据huffmanTree生成Huffman编码
	CreateHuffmanCode(Tree.GetRoot());

	//4. 开始压缩
	_Docompress(file);
}

void FileCompress::_Docompress(const char* file)//开始压缩
{
	//1. 构建压缩文件

	//2. 先将统计好的字符和字符数，写入压缩文件总，方便解压

	//3. 从源文件中读取一个字符根据HuffmanTree,构成几个编码位并
	//	 保存下来,够8位将其写入压缩文件,直到源文件全部被读取完

}
void FileCompress::UnCompress(const char* file)//解压准备
{
	//1.先从文件中将要构成HuffmanTree的数据(字符和字符总数)取出

	//2.构建HuffmanTree

	//3.开始解压
}
void  FileCompress::_Douncompress(const char* file)//开始解压
{
	//1.创建解压文件

	//2.从压缩文件中读取一个字符，开始从HuffmanTree上开始查找，直到叶子结点，写入解压文件
}
void FileCompress::CreateHuffmanCode(Node* root)//生成Huffman编码
{
	//根据HuffmanTree,使用递归，在父结点的左边，代码+1，反之+0
	if (root == NULL)
		return;

	Node* parent = root->_parent;
	if (parent)
	{
		if (root == parent->_left)
			root->_data.code = parent->_data.code + "1";
		else
			root->_data.code = parent->_data.code + "0";
	}
	//如果是叶子结点，就把编码写进hashtable里存储
	if (root->_left == NULL && root->_right == NULL)
	{
		_hashtable[root->_data._ch].code = root->_data.code;
		return;
	}

	CreateHuffmanCode(root->_left);
	CreateHuffmanCode(root->_right);
}
