#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include <assert.h>
using namespace std;

namespace L
{
	template<class T>
	struct ListNode
	{
		T _data;
		ListNode<T>* _next;
		ListNode<T>* _prev;
		//构造函数:初始化节点
		ListNode(const T& x = T())
			: _data(x)
			, _next(nullptr)
			, _prev(nullptr)
		{}
	};
	//template<class T>
	//迭代器iterator实现
	//用struct实现：定义为公有，不必用友元函数进行调用
	//Ref传T&（引用），Ptr传T*（指针）
	template<class T, class Ref, class Ptr>
	struct List_iterator
	{
		typedef ListNode<T> node;
		typedef List_iterator<T, Ref, Ptr> self;
		node* _node;

		List_iterator(node* node)
			:_node(node)
		{}

		// 拷贝构造 赋值重载 析构都不用实现，默认就可以

		bool operator!=(const self& s) const
		{
			return _node != s._node;
		}
		bool operator==(const self& s) const
		{
			return !(*this != s);
		}
		//T*
		Ptr operator->() const
		{
			return &_node->_data;    
		}
		//T&
		Ref operator*() const
		{
			return _node->_data;
		}
		// it++  it.operator(&it, 0)
		self operator++(int)
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		// ++it it.operator(&it)
		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		//it--
		self operator--(int)
		{
			self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}
		//--it;
		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
	};
	
	template<class T>
	class list
	{
		typedef ListNode<T> node;
	private:
		//双向带头循环list
		node* _head;
	public:
		typedef List_iterator<T, T&, T*> iterator;
		typedef List_iterator<T, const T&, const T*> const_iterator;
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}
		iterator begin()
		{
			return _head->_next;
		}
		iterator end()
		{
			return _head;
		}
		const_iterator begin() const
		{
			return _head->_next;
		}
		const_iterator end() const
		{
			return _head;
		}
		template<class InputIterator>
		//拷贝构造函数   
		list(InputIterator first, InputIterator last)
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		list(const list<T>& lt)
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
			list<T> tmp(lt.begin(), lt.end());
			std::swap(_head, tmp._head);
		}
		//lt1 = lt2:赋值
		list<T>& operator=(list<T> lt)
		{
			std::swap(_head, lt._head);
			return *this;
		}
		/*list(const list<T>& lt)
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
			const_iterator it = lt.begin();
			while (it != lt.end())
			{
				push_back(*it);
				++it;
			}
		} */
		//构造函数：初始化list
		list()
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		
		//插入  
		iterator insert(iterator pos, const T& x)
		{
			node* newnode = new node(x);
			node* cur = pos._node;
			node* prev = cur->_prev;
			//顺序：prev newnode cur
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
			return iterator(newnode);
		}
		//删除
		iterator erase(iterator pos)
		{
			assert(pos!=end());
			node* cur = pos._node;
			node* prev = cur->_prev;
			node* next = cur->_next;
			prev->_next = cur;
			cur->_prev = prev;
			delete cur;
			return iterator(next);
		}
		//尾插
		void push_back(const T& x)
		{
			/*node* newnode = new node(x);
			node* tail = _head->_prev;

			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next=_head;
			_head->_prev = newnode;*/
			//insert实现尾插
			insert(end(), x);
		}
		//头插
		void push_front(const T& x)
		{
			insert(begin(), x);
		}
		//头删
		void pop_front()
		{
			erase(begin());
		}
		//尾删
		void pop_back()
		{
			erase(end());
		}
	};
}