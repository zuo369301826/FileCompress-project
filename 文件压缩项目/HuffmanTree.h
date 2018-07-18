#pragma once

#include <queue>

//huffman�����
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

//huffman��  TΪhuffman�����Ĳ���
template<class T>
class HuffmanTree {
	typedef struct HuffmanTreeNode<T> Node;

	//�º���  TΪ���
	struct compare {
		bool operator()(Node* n1, Node* n2)
		{
			if (n1->_data > n2->_data)
				return true;
		}
	};

public:
	//����Huffman����Ҫ�����������ֱ�Ϊ��ͳ��֮����������飬���ݸ������ǿ�Ԫ��
	HuffmanTree(T* data, size_t size, const T& end)
	{
		//ʹ�����ȼ����й���һ��С��
		priority_queue<Node*, vector<Node*>, compare> heap;

		//1.���������ݹ��ɽ�㣬¼��С����
		for (int i = 0; i < size; ++i)
		{
			if (data[i] != end)
				heap.push(new Node(data[i]));
		}

		//2. ��ʼ����HuffmanTree��ÿ����ȡ������С�����ݣ���Ϊ���ڵ������������������
		//   �������ڵ�¼����У�ֱ������û����
		Node* pN1;
		Node* pN2;
		Node* newNode;
		while (heap.size() > 1)
		{
			pN1 = heap.top();
			heap.pop();
			pN2 = heap.top();
			heap.pop();
			newNode = new Node(pN1->_data + pN2->_data);
			if (pN1->_data > pN2->_data)
			{
				newNode->_left  = pN1;
				newNode->_right = pN2;
			}
			heap.push(newNode);
		}
		_root = newNode;
	}
	
	void Getroot()

private:
	HuffmanTree(const HuffmanTree<T>&);
	HuffmanTree<T>& operator=(const HuffmanTree<T>&);
private:
	Node* _root;
};






