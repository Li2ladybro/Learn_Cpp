#pragma once
#include <iostream>
#include <assert.h>
#include <string>
using namespace std;

namespace vector_2026_1_27
{
	template <class T>

	class vector
	{
	public:

		void swap(vector<T>& v)
		{
			::swap(_start, v._start);
			::swap(_finish, v._finish);
			::swap(_end_of_storage, v._end_of_storage);
		}

		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin()  
		{
			return _start;
		}

		iterator end()  
		{
			return _finish;
		}

		const_iterator begin() const
		{
			return _start;
		}

		const_iterator end() const
		{
			return _finish;
		}

		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_end_of_storage(nullptr)
		{}

		vector (const vector<T>& v)
			:_start(nullptr)
			,_finish(nullptr)
			,_end_of_storage(nullptr)
		{
			reserve(v.capacity());
			for (auto& e : v)
				push_back(e);
		}

		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _end_of_storage - _start;
		}

		// 改变容量
		void reserve(const size_t& newcapacity) 
		{
			if (newcapacity > capacity())
			{
				size_t sz = size();
				T* tmp = new T[newcapacity];
				if (_start)
				{
					// 按字节序浅拷贝
					// memcpy(tmp, _start, sizeof(T) * size());
					for (size_t i = 0; i < sz; ++i)
						// 利用string的赋值做深拷贝
						tmp[i] = _start[i];
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + newcapacity;
			}
			
		}

		void resize(size_t n,const T& e=T())
		{
			if (n <size())
			_finish = _start + n;
			
			if (n>size())
			{
				if(n>capacity())
				reserve(n);
				int cut = n - size();
				while (cut--)
				push_back(e);
			}
		}

		// 删除
		iterator erase(iterator pos)
		{
			assert(pos < _finish);

			iterator bg = pos;

			while (bg < _finish-1)
			{
				*bg = *(bg + 1);
				++bg;
			}
			--_finish;
			return pos;
		}

		// 尾删
		void pop_back()
		{
			//assert(_start < _finish);
			//	--_finish;
			erase(_finish-1);
		}

		// 插入
		void insert(iterator pos,const T& e)
		{
			assert(pos <= _finish);
			if (_finish == _end_of_storage)
			{
				size_t gap = pos - _start;
				size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
				reserve(newcapacity);

				// 迭代器重定位
				pos = _start + gap;
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}

			*pos = e;
			++_finish;
		}

		// 尾插
		void push_back(const T& e)
		{
			//if (_finish == _end_of_storage)
			//{
			//	size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			//	reserve(newcapacity);
			//}
			//*_finish = e;
			//_finish++;

			insert(_finish, e);
		}

		T& operator[](const size_t& i)
		{
			assert(i < size());
			return _start[i];
		}

		const T& operator[](const size_t& i) const
		{
			assert(i < size());
			return _start[i];
		}

		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}


	private:
		T* _start;				// 起始指针
		T* _finish;				// 已存储有效元素的下一位置
		T* _end_of_storage;		// 最大有效元素的下一位置，但仍在已分配内存范围内的位置
	};
}