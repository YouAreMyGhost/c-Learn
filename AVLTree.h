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
	AVLTreeNode<K, V>* _parent;//非必须
	pair<K, V> _kv;
	int _bf;//balance factor平衡因子 左右高度差 非必须

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
	//AVLTree(const AVLTree<K, V>&t);
	//AVLTree<K, V>& operator=(AVLTree<K, V> t);
	//插入
	pair<Node*, bool> Insert(const pair<K, V>& kv)
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
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return make_pair(cur, false);
			}
		}

		cur = new Node(kv);
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		Node* newnode = cur;

		// 1、更新平衡因子
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
			else if (abs(parent->_bf) == 2)
			{
				// 旋转
				if (parent->_bf == -2)
				{
					if (cur->_bf == -1)
					{
						rotateRight(parent);
					}
					else // cur->_bf == 1
					{
						rotateLR(parent);
					}
				}
				else //parent->_bf == 2
				{
					if (cur->_bf == 1)
					{
						rotateLeft(parent);
					}
					else // cur->_bf == -1
					{
						rotateRL(parent);
					}
				}

				break;
			}
			else
			{
				assert(false);
			}
		}

		return make_pair(newnode, true);
	}
	//右单旋
	void rotateRight(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		
		//基础操作 
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		Node* parentParent = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;
		//如果parent为根节点的处理方式
		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		//如果parent为子树上节点的处理方式、
		else
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subL;
				subL->_parent = parentParent;
			}
			else if (parentParent->_right == parent)
			{
				parentParent->_right = subL;
				subL->_parent = parentParent;
			}
		}
		//更新平衡因子
		subL->_bf = parent->_bf = 0;
	}
	//左单旋
	void rotateLeft(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//基础操作 
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		Node* parentParent = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;
		//如果parent为根节点的处理方式
		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		//如果parent为子树上节点的处理方式、
		else
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subR;
			}
			else if (parentParent->_right == parent)
			{
				parentParent->_right = subR;
			}
		}
		subR->_parent = parentParent;
		//更新平衡因子
		subR->_bf = parent->_bf = 0;
	}
	//左右双旋
	void rotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		rotateLeft(parent->_left);
		rotateRight(parent);
		//subLR右树插入
		if (bf == 1)
		{
			parent->_bf = 0;
			subLR->_bf = 0;
			subL->_bf = -1;
		}
		//subLR左树插入
		else if (bf == -1)
		{
			parent->_bf = 1;
			subLR->_bf = 0;
			subL->_bf = 0;
		}
		//bf==0，说明subLR是新增节点
		else if (bf == 0)
		{
			subLR->_bf = parent->_bf = subL->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}
	//右左双旋
	void rotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		rotateRight(parent->_right);
		rotateLeft(parent);
		//subLR右树插入
		if (bf == 1)
		{
			parent->_bf = -1;
			subRL->_bf = 0;
			subR->_bf = 0;
		}
		//subRL左树插入
		else if (bf == -1)
		{
			parent->_bf = 0;
			subRL->_bf = 0;
			subR->_bf = 1;
		}
		//bf==0，说明subRL是新增节点
		else if (bf == 0)
		{
			subRL->_bf = parent->_bf = subR->_bf = 0;
		}
		else
		{
			assert(false);
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
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_kv.first << " ";
		_InOrder(root->_right);
	}
	void InOrder()
	{
		_InOrder(_root);
	}
	int Height(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		return max(Height(root->_left), Height(root->_right))+1;
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
	//~AVLTree();
};