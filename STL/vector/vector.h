#pragma once
#include<iostream>
using namespace std;

namespace vector_2026_1_27
{
	template <class T>

	class vector
	{
		typedef T* iterator;

	public:

		iterator begin() const
		{
			return _start;
		}

		iterator end() const
		{
			return _finish;
		}

		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_end_of_storage(nullptr)
		{}

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _end_of_storage - _start;
		}

		// 改变容量
		void reserve(const size_t newcapacity) 
		{
			if (newcapacity > capacity())
			{
				size_t sz = size();
				T* tmp = new T[newcapacity];
				if (_start)
				{
					memcpy(tmp, _start, sizeof(T) * size());
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + newcapacity;
			}
			
		}

		// 尾插
		void push_back(const T e)
		{
			if (_finish == _end_of_storage)
			{
				size_t newcapacity = size() == 0 ? 2 : capacity() * 2;
				reserve(newcapacity);
			}
			*_finish = e;
			_finish++;
		}

	private:
		T* _start;				// 起始指针
		T* _finish;				// 有效元素的下一位置
		T* _end_of_storage;		// 最大元素的位置
	};
}