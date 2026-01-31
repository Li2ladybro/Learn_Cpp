#pragma once
#include <vector>
#include <list>
#include <deque>
namespace stack_2026_1_31
{
	// STL默认选用双端队列作为栈和队列的底层容器
	template <class T, class Container= deque<T>>
	// template <class T, class Container>
	class stack
	{
		// 栈实际是一种特殊的vector，使用vector完全可以模拟实现stack
		// 底层可以是vector/list...
		// 咩有迭代器
	public:
		// 压栈，尾插
		void push(const T& e){_con.push_back(e);}

		// 出栈，尾删
		void pop(){_con.pop_back();}

		// 获取栈顶元素，取尾元素
		T& top(){return _con.back();}

		// 返回栈的元素个数
		size_t size() const{return _con.size();}

		// 判空
		bool empty() const{return _con.empty();}

	private:
		Container _con;
	};
}