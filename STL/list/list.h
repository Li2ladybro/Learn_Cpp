#pragma once

namespace  list_2026_1_29
{

	template<class T>
	// 单元节点
	struct __list_node
	{
		__list_node(const T& e=T())
			:_prev(nullptr)
			,_next(nullptr)
			,_data(e)
		{ }

		__list_node<T>* _prev;
		__list_node<T>* _next;
		T _data;
	};

	template<class T>
	// 迭代器
	struct __list_iterator
	{
		typedef __list_node<T> Node; // 默认私有只有内部使用
		__list_iterator(Node* it)
			:_node(it)
		{}

		T& operator*()
		{
			return _node->_data;
		}

		__list_iterator<T>& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		
		__list_iterator<T>& operator++(int)
		{
			__list_iterator<T> tmp(_node);
			++(*this);
			return tmp;
		}

		__list_iterator<T>& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		__list_iterator<T>& operator--(int)
		{
			__list_iterator<T> tmp(_node);
			--(*this);
			return tmp;
		}

		bool operator !=(const __list_iterator<T>& it)
		{
			return _node != it._node;
		}

		bool operator ==(const __list_iterator<T>& it)
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

		typedef __list_iterator<T> iterator;

		iterator begin() 
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		list()
			:_head(new Node)
		{ 
			_head->_prev = _head;
			_head->_next = _head;
		}

		void push_back(const Node& e)
		{
			Node* newNode = new Node(e);
			Node* tail = _head->_prev;

			tail->_next = newNode;
			newNode->_prev = tail;
			newNode->_next = _head;
			_head->_prev = newNode;
		}

	private:
		// 头指针
		Node* _head;
	};
}