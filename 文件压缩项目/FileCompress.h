#pragma once


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
};


class FileCompress {
	typedef struct HuffmanTreeNode<CharData> Node;
public:
	FileCompress();//缺省构造函数
	void Compress();//压缩
	void UnCompress();//解压
	void CreateHuffmanCode();//生成Huffman编码

private:
	CharData _hashtable[256];
};

FileCompress::FileCompress()//缺省构造函数
{

}
void FileCompress::Compress()//压缩
{

}
void FileCompress::UnCompress()//解压
{

}
void FileCompress::CreateHuffmanCode()//生成Huffman编码
{

}
