#pragma once
#include <assert.h>

namespace  list_2026_1_29
{

	template<class T>
	// 单元节点
	struct __list_node
	{
		__list_node(const T& e = T())
			: _prev(nullptr)
			, _next(nullptr)
			, _data(e)
		{}

		__list_node<T>* _prev;
		__list_node<T>* _next;
		T _data;
	};

	// T：类型；Ref：引用；Ptr：指针
	// typedef __list_iterator<  T, T&, T*> iterator;
	// typedef __list_iterator<  T, const T&, const T*> const_iterator;
	template<class T,class Ref,class Ptr>
	// 迭代器：重载一些运算符，使得迭代器像指针一样使用
	struct __list_iterator
	{
		typedef __list_iterator< T,  Ref,  Ptr> Self;
		typedef __list_node<T> Node; // 默认私有只有内部使用

		__list_iterator(Node* it)
			:_node(it)
		{}

		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}

		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		
		Self& operator++(int)
		{
			Self tmp(_node);
			++(*this);
			return tmp;
		}

		Self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		Self& operator--(int)
		{
			Self tmp(_node);
			--(*this);
			return tmp;
		}

		bool operator !=(const Self& it) const
		{
			return _node != it._node;
		}

		bool operator ==(const Self& it) const
		{
			return _node == it._node;
		}

		Node* _node;  // 本质是指针
	};

	template<class T>
	class list
	{
		// 本质是双向循环链表
		typedef __list_node<T> Node; // 默认私有只有内部使用

	public:

		// 重命名迭代器
		typedef __list_iterator<  T,   T&,   T*> iterator;
		typedef __list_iterator<  T,   const T&, const T*> const_iterator;

		iterator begin() 
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			// 链表头是迭代器的尾巴（开区间）
			return iterator(_head);
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}

		list()
			:_head(new Node)
		{ 
			_head->_prev = _head;
			_head->_next = _head;
		}

		list(const list<T>& lt)
			:_head(new Node)
		{
			
			_head->_next = _head->_prev= _head;
			//const_iterator it = lt.begin();
			//while (it != lt.end())
			//{
			//	push_back(*it);
			//	++it;
			//}

			for (auto& e : lt)
				push_back(e);
		}

		list<T>& operator=(list<T> lt)
		{
			::swap(_head, lt._head);
			return *this;
		}

		// 清空
		void clear()
		{
			iterator it = begin();
			while (it != end())
				erase(it++);
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
		
		// 插入
		void insert(iterator pos,const T& e)
		{
			Node* cur = pos._node;		  // 当前节点
			Node* prev = cur->_prev;      // 前一节点
			Node* newNode = new Node(e);  // 新节点

			prev->_next = newNode;
			cur->_prev = newNode;
			newNode->_prev = prev;
			newNode->_next = cur;
		}

		// 头插
		void push_front(const T& e)
		{

			insert(begin(), e);
		}

		// 尾插
		void push_back(const T& e)
		{
			//Node* newNode = new Node(e);
			//Node* tail = _head->_prev;

			//tail->_next = newNode;
			//newNode->_prev = tail;
			//newNode->_next = _head;
			//_head->_prev = newNode;
			insert(end(), e);
		}

		// 删除
		void erase(iterator pos)
		{
			assert(pos != end());

			Node* cur = pos._node;			// 当前节点
			Node* prev = cur->_prev;		// 前驱
			Node* next = cur->_next;		// 后继

			// delete[] cur;
			delete cur;

			prev->_next = next;
			next->_prev = prev;
		}
	
		void pop_front()
		{
			erase(begin());
		}

		void pop_back()
		{
			erase(--end());
		}

	private:
		// 头指针
		Node* _head;
	};
}