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
	void Compress();//压缩准备
	void _Docompress();//开始压缩
	void UnCompress();//解压准备
	void _Douncompress();//开始解压
	void CreateHuffmanCode();//生成Huffman编码

private:
	CharData _hashtable[256];
};

FileCompress::FileCompress()//缺省构造函数
{
	//哈希表初始化
}
void FileCompress::Compress()//压缩准备
{
	//1. 统计字符个数，并写入哈希表中
	
	//2. 用哈希表构建huffmanTree

	//3. 根据huffmanTree生成Huffman编码

	//4. 开始压缩
}

void FileCompress::_Docompress()//开始压缩
{
	//1. 构建压缩文件

	//2. 先将统计好的字符和字符数，写入压缩文件总，方便解压

	//3. 从源文件中读取一个字符根据HuffmanTree,构成几个编码位并
	//	 保存下来,够8位将其写入压缩文件,直到源文件全部被读取完

}
void FileCompress::UnCompress()//解压准备
{
	//1.先从文件中将要构成HuffmanTree的数据(字符和字符总数)取出

	//2.构建HuffmanTree

	//3.开始解压
}
void  FileCompress::_Douncompress()//开始解压
{
	//1.创建解压文件

	//2.从压缩文件中读取一个字符，开始从HuffmanTree上开始查找，直到叶子结点，写入解压文件
}
void FileCompress::CreateHuffmanCode()//生成Huffman编码
{
	//根据HuffmanTree,使用迭代法，在父结点的左边，代码+1，反之+0
}
