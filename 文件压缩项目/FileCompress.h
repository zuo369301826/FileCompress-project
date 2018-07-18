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
	void Compress();//ѹ��׼��
	void _Docompress();//��ʼѹ��
	void UnCompress();//��ѹ׼��
	void _Douncompress();//��ʼ��ѹ
	void CreateHuffmanCode();//����Huffman����

private:
	CharData _hashtable[256];
};

FileCompress::FileCompress()//ȱʡ���캯��
{
	//��ϣ���ʼ��
}
void FileCompress::Compress()//ѹ��׼��
{
	//1. ͳ���ַ���������д���ϣ����
	
	//2. �ù�ϣ����huffmanTree

	//3. ����huffmanTree����Huffman����

	//4. ��ʼѹ��
}

void FileCompress::_Docompress()//��ʼѹ��
{
	//1. ����ѹ���ļ�

	//2. �Ƚ�ͳ�ƺõ��ַ����ַ�����д��ѹ���ļ��ܣ������ѹ

	//3. ��Դ�ļ��ж�ȡһ���ַ�����HuffmanTree,���ɼ�������λ��
	//	 ��������,��8λ����д��ѹ���ļ�,ֱ��Դ�ļ�ȫ������ȡ��

}
void FileCompress::UnCompress()//��ѹ׼��
{
	//1.�ȴ��ļ��н�Ҫ����HuffmanTree������(�ַ����ַ�����)ȡ��

	//2.����HuffmanTree

	//3.��ʼ��ѹ
}
void  FileCompress::_Douncompress()//��ʼ��ѹ
{
	//1.������ѹ�ļ�

	//2.��ѹ���ļ��ж�ȡһ���ַ�����ʼ��HuffmanTree�Ͽ�ʼ���ң�ֱ��Ҷ�ӽ�㣬д���ѹ�ļ�
}
void FileCompress::CreateHuffmanCode()//����Huffman����
{
	//����HuffmanTree,ʹ�õ��������ڸ�������ߣ�����+1����֮+0
}
