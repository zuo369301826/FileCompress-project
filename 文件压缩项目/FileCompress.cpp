#include "FileCompress.h"

#define TXT_NAME "./data/input.txt"
#define TXT_NAME_un "./data/input.txt.huffman"

void compare_test()
{
	FileCompress fc;
	fc.Compress(TXT_NAME);
}

void uncompare_test()
{

}


int main()
{
	compare_test();
	uncompare_test();
	return 0;
}