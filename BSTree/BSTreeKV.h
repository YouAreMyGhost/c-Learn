#pragma once
#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class K, class V>
struct BSTNodeKV
{
	const K _key;//所存储的数据
	V _value;
	struct BSTNodeKV<K, V>* _left;
	struct BSTNodeKV<K, V>* _right;
	BSTNodeKV(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(nullptr)
		, _right(nullptr)
	{}
};

template<class K, class V>
class BSTreeKV
{
	typedef BSTNodeKV<K, V> Node;
private:
	Node* _root = nullptr;
public:
	//遍历
	void InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		//中序遍历
		InOrder(root->_left);
		cout << root->_key << ":"<<root->_value<<" ";
		InOrder(root->_right);
	}
	//重载一个无参函数，方便接口使用
	void InOrder()
	{
		InOrder(_root);
		cout << endl;
	}
	//插入
	bool Insert(const K& key, const V& value)
	{
		if (_root == nullptr)
		{
			_root = new Node(key, value);
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key, value);
		if (key > parent->_key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
	}
	//查找
	Node* Find(const K& key)
	{
		//cout << "WANT FIND:" << key << endl;
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		//cout << "NOT FIND" << endl;
		return nullptr;
	}
	//删除节点
	bool Erase(const K& key, const V& value)
	{
		cout << "ERASE:" << key << endl;
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//找到了，准备删除该节点
				//左为空||左右均为空结合讨论
				if (cur->_left == nullptr)
				{
					if (cur == _root)
						_root = cur->_right;
					else
					{
						if (cur == parent->_left)
							parent->_left = cur->_right;
						else
							parent->_right = cur->_right;
					}
					delete cur;
				}
				else if (cur->_right == nullptr)
				{
					if (cur == _root)
						_root = cur->_left;
					else
					{
						if (cur == parent->_left)
							parent->_left = cur->_left;
						else
							parent->_right = cur->_left;
					}
					delete cur;
				}
				else
				{
					//subMin的父亲节点
					Node* subMinParent = cur;
					//右子树中寻找中序下的第一个节点subMin
					Node* subMin = cur->_right;
					while (subMin->_left)
					{
						subMinParent = subMin;
						subMin = subMin->_right;
					}
					cur->_key = subMin->_key;
					//subMin左孩子一定为空
					//考虑subMinParent可能为要删除的节点
					if (subMin == subMinParent->_left)
					{
						subMinParent->_left = subMin->_right;
					}
					else
					{
						subMinParent->_right = subMin->_right;
					}
					delete subMin;
				}
				return true;
			}
		}
		cout << "ERASE ERROR" << endl;
		return false;
	}
	//通过key来找value
	V FindValue(const K& key)
	{
		cout << "WANT FIND:" << key <<":";
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur->_value;
			}
		}
		cout << "NOT FIND" << endl;
		exit(1);
	}
};