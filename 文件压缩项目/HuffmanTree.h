#pragma once

template<class T>
struct HuffmanTreeNode{
	T _data;
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	HuffmanTreeNode<T>* _parent;

	HuffmanTreeNode<T>()
		:_left(NULL)
		:_right(NULL)
		:_parent(NULL)
	{
		;
	}
};

template<class T>
class HuffmanTree {
	typedef struct HuffmanTreeNode<T> Node;
public:
	HuffmanTree()
		_root(NULL)
	{}
	~HuffmanTree()
	{}
	void insert();
private:
	Node* _root;
};
