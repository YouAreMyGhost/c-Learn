#pragma once
#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class K, class V>
struct BSTNodeKV
{
	const K _key;//���洢������
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
	//����
	void InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		//�������
		InOrder(root->_left);
		cout << root->_key << ":"<<root->_value<<" ";
		InOrder(root->_right);
	}
	//����һ���޲κ���������ӿ�ʹ��
	void InOrder()
	{
		InOrder(_root);
		cout << endl;
	}
	//����
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
	//����
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
	//ɾ���ڵ�
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
				//�ҵ��ˣ�׼��ɾ���ýڵ�
				//��Ϊ��||���Ҿ�Ϊ�ս������
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
					//subMin�ĸ��׽ڵ�
					Node* subMinParent = cur;
					//��������Ѱ�������µĵ�һ���ڵ�subMin
					Node* subMin = cur->_right;
					while (subMin->_left)
					{
						subMinParent = subMin;
						subMin = subMin->_right;
					}
					cur->_key = subMin->_key;
					//subMin����һ��Ϊ��
					//����subMinParent����ΪҪɾ���Ľڵ�
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
	//ͨ��key����value
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