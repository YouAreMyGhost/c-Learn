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
		//���캯��:��ʼ���ڵ�
		ListNode(const T& x = T())
			: _data(x)
			, _next(nullptr)
			, _prev(nullptr)
		{}
	};
	//template<class T>
	//������iteratorʵ��
	//��structʵ�֣�����Ϊ���У���������Ԫ�������е���
	//Ref��T&�����ã���Ptr��T*��ָ�룩
	template<class T, class Ref, class Ptr>
	struct List_iterator
	{
		typedef ListNode<T> node;
		typedef List_iterator<T, Ref, Ptr> self;
		node* _node;

		List_iterator(node* node)
			:_node(node)
		{}

		// �������� ��ֵ���� ����������ʵ�֣�Ĭ�ϾͿ���

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
		//˫���ͷѭ��list
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
		//�������캯��   
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
		//lt1 = lt2:��ֵ
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
		//���캯������ʼ��list
		list()
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		
		//����  
		iterator insert(iterator pos, const T& x)
		{
			node* newnode = new node(x);
			node* cur = pos._node;
			node* prev = cur->_prev;
			//˳��prev newnode cur
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
			return iterator(newnode);
		}
		//ɾ��
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
		//β��
		void push_back(const T& x)
		{
			/*node* newnode = new node(x);
			node* tail = _head->_prev;

			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next=_head;
			_head->_prev = newnode;*/
			//insertʵ��β��
			insert(end(), x);
		}
		//ͷ��
		void push_front(const T& x)
		{
			insert(begin(), x);
		}
		//ͷɾ
		void pop_front()
		{
			erase(begin());
		}
		//βɾ
		void pop_back()
		{
			erase(end());
		}
	};
}