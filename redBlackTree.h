#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
enum color
{
	RED,
	BLACK
};

template <class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	pair<K, V> _kv;
	enum color _col;

	RBTreeNode(const pair<K, V>& kv)
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _col(RED)
	{}
};
template <class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
private:
	Node* _root = nullptr;
public:
	pair<Node*, bool> Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);

			_root->_col = BLACK;
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

		cur = new Node(kv); // RED
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
		while (parent && parent->_col == RED)
		{
			Node* grandpa = parent->_parent;
			if (grandpa->_left == parent)
			{
				Node* uncle = grandpa->_right;
				/*  情况一：uncle存在且为红
							 b
						   /   \
						  r     r
						/ \    / \
					   b   b   b  b
					  / \
					 r   r
					/
				   n(r)

				 */
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandpa->_col = RED;
					//继续向上处理
					cur = grandpa;
					parent = cur->_parent;
				}
				/*  情况二：uncel不存在或存在为黑
							 b
						   /   \
						  r     b
						 / \   / \
					    b  b  b   b
						  / \
						 r   r
						/
					   n(r)

				 */
				else if (!uncle || (uncle && uncle->_col == BLACK))
				{

					if (cur == parent->_left)
					{
						rotateRight(grandpa);
						parent->_col = BLACK;
						grandpa->_col = RED;
					}
					else
					{
						rotateLeft(parent);
						rotateRight(grandpa);
						cur->_col = BLACK;
						grandpa->_col = RED;
					}
					break;
				}
			}
			else if (grandpa->_right == parent)
			{
				Node* uncle = grandpa->_left;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandpa->_col = RED;

					cur = grandpa;
					parent = cur->_parent;
				}
				else if (!uncle || (uncle && uncle->_col == BLACK))
				{
					if (cur == parent->_right)
					{
						rotateLeft(grandpa);
						grandpa->_col = RED;
						parent->_col = BLACK;
					}
					else
					{
						rotateRight(parent);
						rotateLeft(grandpa);
						cur->_col = BLACK;
						grandpa->_col = RED;
					}
					break;
				}
			}
		}
		_root->_col = BLACK;
		return make_pair(newnode, true);
	}
	void rotateRight(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* parentParent = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (parent == _root)
		{
			_root = subL;
			_root->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}

			subL->_parent = parentParent;
		};
	}

	void rotateLeft(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}

		subR->_left = parent;

		Node* parentParent = parent->_parent;
		parent->_parent = subR;

		if (_root == parent)
		{
			_root = subR;
		}
		else
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}
		}

		subR->_parent = parentParent;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		cout << root->_kv.first << " ";
		_InOrder(root->_right);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	bool _CheckRedCol(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}

		if (root->_col == RED)
		{
			Node* parent = root->_parent;
			if (parent->_col == RED)
			{
				cout << "违反规则2：存在连续的红色节点" << endl;
				return false;
			}
		}

		return _CheckRedCol(root->_left) && _CheckRedCol(root->_right);
	}

	bool _CheckBlackNum(Node* root, int blackNum, int trueNum)
	{
		if (root == nullptr)
		{
			// 当走到NULL时， blackNum 这条路径黑色节点的数量
			return trueNum == blackNum;
		}

		if (root->_col == BLACK)
		{
			blackNum++;
		}

		return  _CheckBlackNum(root->_left, blackNum, trueNum)
			&& _CheckBlackNum(root->_right, blackNum, trueNum);
	}

	bool IsBalance()
	{
		if (_root && _root->_col == RED)
		{
			cout << "违反规则1：根节点是红色的" << endl;
			return false;
		}

		int trueNum = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				++trueNum;
			}
			cur = cur->_left;
		}

		int blackNum = 0;
		return _CheckRedCol(_root)
			&& _CheckBlackNum(_root, blackNum, trueNum);
	} 
};