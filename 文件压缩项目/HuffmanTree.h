#pragma once

#include <queue>

//huffman树结点
template<class T>
struct HuffmanTreeNode{
	T _data;
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	HuffmanTreeNode<T>* _parent;

	HuffmanTreeNode<T>(const T& data)
		:_data(data),
		_left(NULL),
		_right(NULL),
		_parent(NULL)
	{;}
};

//huffman树  T为huffman树结点的参数
template<class T>
class HuffmanTree {
	typedef struct HuffmanTreeNode<T> Node;

	//仿函数  T为结点
	struct compare {
		bool operator()(Node* n1, Node* n2)
		{
			return  (n1->_data >  n2->_data);
		}
	};

public:
	//构建Huffman树需要三个参数，分别为：统计之后的数据数组，数据个数，非空元素
	HuffmanTree(T* data, size_t size, const T& end)
	{
		//使用优先级队列构建一个小堆   < 是大堆  > 是小堆
		priority_queue<Node*, vector<Node*>, compare> heap;

		//1.将所有数据构成结点，录入小堆中
		for (size_t i = 0; i < size; ++i)
		{
			if (data[i] != end)
				heap.push(new Node(data[i]));
		}

		//2. 开始构建HuffmanTree，每堆中取两个最小的数据，作为根节点的左子树和右子树，
		//   并将根节点录入堆中，直到堆中没数据
		Node* pN1;
		Node* pN2;
		Node* newNode=NULL;
		while (heap.size() > 1)
		{
			pN1 = heap.top();
			heap.pop();
			pN2 = heap.top();
			heap.pop();
			newNode = new Node(pN1->_data + pN2->_data);
			pN1->_parent = newNode;
			pN2->_parent = newNode;
			if (pN1->_data > pN2->_data)
			{
				newNode->_left  = pN1;
				newNode->_right = pN2;
			}
			else
			{
				newNode->_left = pN2;
				newNode->_right = pN1;
			}
			heap.push(newNode);
		}
		_root = newNode;
	}
	
	Node* GetRoot()
	{
		return _root;
	}

private:
	HuffmanTree(const HuffmanTree<T>&);
	HuffmanTree<T>& operator=(const HuffmanTree<T>&);
private:
	Node* _root;
};

