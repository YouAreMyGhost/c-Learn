#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;//�Ǳ���
	pair<K, V> _kv;
	int _bf;//balance factorƽ������ ���Ҹ߶Ȳ� �Ǳ���

	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr),_right(nullptr)
		,_parent(nullptr),_kv(kv),_bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
private: 
	Node* _root = nullptr;
public:
	AVLTree() = default;
	/*AVLTree(const AVLTree<K, V>& t)
	{

	}
	AVLTree<K, V>& operator(AVLTree<K, V>t)
	{

	}*/
	//����
	pair<Node*, bool>Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return make_pair(_root, true);
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kv.first > cur->kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kv.first < cur->kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			//�������и�ֵ�Ľڵ㣬�����벢����false
			else
			{
				make_pair(cur, false);
			}
		}
		cur = new Node(kv);
		if (kv.first > parent->first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		Node* newNode = cur;
		//����_bf ƽ������
		while (parent)
		{
			if (cur == parent->_right)
			{
				parent->_bf++;
			}
			else
			{
				parent->_bf--;
			}
			if (parent->_bf == 0)
			{
				break;
			}
			else if (abs(parent->_bf) == 1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if(abs(parent->_bf) == 2)
			{
				//��ת
				if (parent->_bf == -2)
				{
					if (cur->_bf = -1)
					{
						rotateRight(parent); 
					}
					else if (cur->_bf = 1)
					{
						rotateLR(parent);
					}
				}
				else
				{
					if (cur->_bf = 1)
					{
						rotateLeft(parent);
					}
					else
					{
						rotateRL(parent);
					}
				}
			}
			else
			{
				//�������ߵ���һ�������Դ���
				assert(false);
			}
		}
		make_pair(newNode, true);
	}
	//�ҵ���
	void rotateRight(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		
		//�������� 
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		Node* parentParent = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;
		//���parentΪ���ڵ�Ĵ���ʽ
		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		//���parentΪ�����Ͻڵ�Ĵ���ʽ��
		else
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subL;
				subL->_parent == parentParent;
			}
			else if (parentParent->_right == parent)
			{
				parentParent->_right = subL;
				subL->_parent == parentParent;
			}
		}
		//����ƽ������
		subL->_bf = parent->_bf = 0;
	}
	//����
	void rotateLeft(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//�������� 
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		Node* parentParent = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;
		//���parentΪ���ڵ�Ĵ���ʽ
		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		//���parentΪ�����Ͻڵ�Ĵ���ʽ��
		else
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subR;
				subR->_parent == parentParent;
			}
			else if (parentParent->_right == parent)
			{
				parentParent->_right = subR;
				subR->_parent == parentParent;
			}
		}
		//����ƽ������
		subR->_bf = parent->_bf = 0;
	}
	//����˫��
	void rotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = parent->_left->_right;
		int bf = subLR->_bf;
		rotateLeft(parent->_left);
		rotateRight(parent);
		//subLR��������
		if (bf == 1)
		{
			parent->_bf = 0;
			subLR->_bf = 0;
			subL->_bf = -1;
		}
		//subLR��������
		else if (bf == -1)
		{
			parent->_bf = 1;
			subLR->_bf = 0;
			subL->_bf = 0;
		}
		//bf==0��˵��subLR�������ڵ�
		else
		{
			subLR->_bf == subL->_bf = 0;
		}
	}
	//����˫��
	void rotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = parent->_right->_left;
		int bf = subRL->_bf;
		rotateRight(parent->_left);
		rotateLeft(parent);
		//subLR��������
		if (bf == 1)
		{
			parent->_bf = -1;
			subRL->_bf = 0;
			subR->_bf = 0;
		}
		//subLR��������
		else if (bf == -1)
		{
			parent->_bf = 0;
			subRL->_bf = 0;
			subR->_bf = 1;
		}
		//bf==0��˵��subLR�������ڵ�
		else
		{
			subRL->_bf == subR->_bf = 0;
		}
	}
	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}
		int leftH = Height(root->_left);
		int rightH = Height(root->_right);

		if (rightH - leftH != root->_bf)
		{
			cout << "balance factor error!" << root->_kv.first << endl;
		}

		return abs(leftH - rightH) <=1 &&
			_IsBalance(root->_left)&& 
			_IsBalance(root->_right);
	}
	bool IsBalance()
	{
		return _IsBalance(_root);
	}
	Node* findNode(const K& key)
	{
		
	}
	V& operator[](const K& key)
	{

	}
	bool Erase(const K& key)
	{

	}
	~AVLTree()
	{
		
	}
};