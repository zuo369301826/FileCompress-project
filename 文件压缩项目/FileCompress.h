#pragma once
#pragma warning(disable:4996)

#include <iostream>

//########################################################
//###################   ͷ�ļ�  ##########################
//########################################################

#include <string>
using namespace std;
#include "HuffmanTree.h"

//########################################################
//#################   �ļ�ѹ����  ########################
//########################################################

//�洢��Ϣ������ַ����ַ����ִ���������
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
	FileCompress();//ȱʡ���캯��
	void Compress(const char* file);//ѹ��׼��
	void _Docompress(const char* file);//��ʼѹ��
	void UnCompress(const char* file);//��ѹ׼��
	void _Douncompress(const char* file, FILE* fp_r, Node* _root);//��ʼ��ѹ
	void CreateHuffmanCode(Node* root);//����Huffman����

private:
	CharData _hashtable[256];
};

FileCompress::FileCompress()//ȱʡ���캯��
{
	//��ϣ���ʼ��
	for (int i = 0; i < 256; i++)
	{
		_hashtable[i]._ch = i;
		_hashtable[i]._count = 0;
	}	

}
void FileCompress::Compress(const char* file)//ѹ��׼��
{
	cout << "ѹ��׼���׶�..." << endl;
	//1. ͳ���ַ���������д���ϣ����
	FILE* fp = fopen(file,"r");
	int ch;
	while ((ch = fgetc(fp)) != EOF)
	{
		_hashtable[ch]._count++;
	}
	cout << "Դ�ļ�����ͳ�� ���..." << endl;

	//2. �ù�ϣ����huffmanTree
	CharData end;
	end._count = 0;
	HuffmanTree<CharData> Tree(_hashtable, 256, end);
	cout << "Huffman������ ���..." << endl;
	//3. ����huffmanTree����Huffman����
	CreateHuffmanCode(Tree.GetRoot());
	cout << "����Huffman���� ���..." << endl;

	//4. ��ʼѹ��
	cout << "��ʼѹ��..." << endl;
	_Docompress(file);
	cout << "ѹ�����..." << endl;
}

void FileCompress::_Docompress(const char* file)//��ʼѹ��
{
	//1. ����ѹ���ļ�
	string FileName = file;
	FileName = FileName + ".huffman";
	FILE *fp_w = fopen(FileName.c_str(), "wb");

	//2. �Ƚ�ͳ�ƺõ��ַ����ַ���д��ѹ���ļ��У������ѹ
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

	//3. ��Դ�ļ��ж�ȡһ���ַ�����HuffmanTree,���ɼ�������λ��
	//	 ��������,��8λ����д��ѹ���ļ�,ֱ��Դ�ļ�ȫ������ȡ��
	FILE *fp_r = fopen(file, "r");
	int ch; //��ȡ�ַ�
	int n = 0; //��¼����λ��
	char buf; //���ѹ������

	//while (!feof(fp_r))
	//{
	//	ch = fgetc(fp_r);
	//	if (ch == EOF)
	//		printf("saf");
	//	string* code = &_hashtable[ch].code; //����ַ�����
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
		string code = _hashtable[ch].code; //����ַ�����
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

void FileCompress::UnCompress(const char* file)//��ѹ׼��
{
	cout << "��ѹ׼��..." << endl;
	//1.�ȴ�ѹ���ļ��н�Ҫ����HuffmanTree������(�ַ����ַ�����)ȡ��
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

	//2.����HuffmanTree
	CharData end;
	end._count = 0;
	HuffmanTree<CharData> tree(_hashtable, 256, end);
	cout << "huffman������..." << endl;

	//3.��ʼ��ѹ
	cout << "��ʼ��ѹ..." << endl;
	_Douncompress(file, fp_r, tree.GetRoot());
	cout << "��ѹ���..." << endl;
}
void  FileCompress::_Douncompress(const char* file, FILE* fp_r, Node* _root)//��ʼ��ѹ
{
	//1.������ѹ�ļ�
	string FileName = file;
	for (int i = 0; i < 7; i++)
		FileName.pop_back();
	FileName += "un";
	FILE* fp_w = fopen(FileName.c_str(), "w");



	//2.��ѹ���ļ��ж�ȡһ���ַ�����ʼ��HuffmanTree�Ͽ�ʼ���ң�ֱ��Ҷ�ӽ�㣬д���ѹ�ļ�
	int ch = 0;
	int num = _root->_data._count;
	Node* cur = _root;
	while ( num > 0)
	{
		ch = fgetc(fp_r);
		for (int i = 0; i < 8; i++)
		{
			if ((ch & (1 << i)) ) //Ϊ1
				cur = cur->_left;
			else
				cur = cur->_right;
			if (cur && cur->_left == NULL && cur->_right == NULL)//�ҵ�Ҷ�ӽ��
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
void FileCompress::CreateHuffmanCode(Node* root)//����Huffman����
{
	//����HuffmanTree,ʹ�õݹ飬�ڸ�������ߣ�����+1����֮+0
	if (root == NULL)
		return;

	Node* parent = root->_parent;
	if (parent)
	{
		if (root == parent->_left)//���+1
			root->_data.code = parent->_data.code + "1";
		else
			root->_data.code = parent->_data.code + "0";
	}
	//�����Ҷ�ӽ�㣬�Ͱѱ���д��hashtable��洢
	if (root->_left == NULL && root->_right == NULL)
	{
		_hashtable[(unsigned char)root->_data._ch].code = root->_data.code;
		return;
	}


	CreateHuffmanCode(root->_left);
	CreateHuffmanCode(root->_right);
}
