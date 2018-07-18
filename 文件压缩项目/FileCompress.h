#pragma once


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
};


class FileCompress {
	typedef struct HuffmanTreeNode<CharData> Node;
public:
	FileCompress();//ȱʡ���캯��
	void Compress();//ѹ��
	void UnCompress();//��ѹ
	void CreateHuffmanCode();//����Huffman����

private:
	CharData _hashtable[256];
};

FileCompress::FileCompress()//ȱʡ���캯��
{

}
void FileCompress::Compress()//ѹ��
{

}
void FileCompress::UnCompress()//��ѹ
{

}
void FileCompress::CreateHuffmanCode()//����Huffman����
{

}
