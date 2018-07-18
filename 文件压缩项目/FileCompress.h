#pragma once
#pragma warning(disable:4996)

//########################################################
//###################   ͷ�ļ�  ##########################
//########################################################

#include <string>
using namespace std;
#include "HuffmanTree.h"

//########################################################
//#################   �ļ�ѹ����  ########################
//########################################################

//�����Ϣ������ַ������ִ�ʱ������
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
	FileCompress();//ȱʡ���캯��
	void Compress(const char* file);//ѹ��׼��
	void _Docompress(const char* file);//��ʼѹ��
	void UnCompress(const char* file);//��ѹ׼��
	void _Douncompress(const char* file);//��ʼ��ѹ
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
	//1. ͳ���ַ���������д���ϣ����
	FILE* fp = fopen(file,"r");
	unsigned char ch;
	while ((ch = fgetc(fp)) && (char)ch != EOF)
	{
		_hashtable[ch]._count++;
	}

	//2. �ù�ϣ����huffmanTree
	CharData end;
	end._count = 0;
	HuffmanTree<CharData> Tree(_hashtable, 256, end);
	
	//3. ����huffmanTree����Huffman����
	CreateHuffmanCode(Tree.GetRoot());

	//4. ��ʼѹ��
	_Docompress(file);
}

void FileCompress::_Docompress(const char* file)//��ʼѹ��
{
	//1. ����ѹ���ļ�

	//2. �Ƚ�ͳ�ƺõ��ַ����ַ�����д��ѹ���ļ��ܣ������ѹ

	//3. ��Դ�ļ��ж�ȡһ���ַ�����HuffmanTree,���ɼ�������λ��
	//	 ��������,��8λ����д��ѹ���ļ�,ֱ��Դ�ļ�ȫ������ȡ��

}
void FileCompress::UnCompress(const char* file)//��ѹ׼��
{
	//1.�ȴ��ļ��н�Ҫ����HuffmanTree������(�ַ����ַ�����)ȡ��

	//2.����HuffmanTree

	//3.��ʼ��ѹ
}
void  FileCompress::_Douncompress(const char* file)//��ʼ��ѹ
{
	//1.������ѹ�ļ�

	//2.��ѹ���ļ��ж�ȡһ���ַ�����ʼ��HuffmanTree�Ͽ�ʼ���ң�ֱ��Ҷ�ӽ�㣬д���ѹ�ļ�
}
void FileCompress::CreateHuffmanCode(Node* root)//����Huffman����
{
	//����HuffmanTree,ʹ�õݹ飬�ڸ�������ߣ�����+1����֮+0
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
	//�����Ҷ�ӽ�㣬�Ͱѱ���д��hashtable��洢
	if (root->_left == NULL && root->_right == NULL)
	{
		_hashtable[root->_data._ch].code = root->_data.code;
		return;
	}

	CreateHuffmanCode(root->_left);
	CreateHuffmanCode(root->_right);
}
