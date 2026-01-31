#pragma once
#include <list>
#include <vector>
#include <deque>

namespace queue_2026_1_31
{
	// queue和Queen，队列和女王
	// STL默认选用双端队列作为栈和队列的底层容器
	template <class T, class Container = deque<T>>
	//template <class T, class Container>
	class quequ
	{
		// queue的接口中存在头删（出队）和尾插（入队），因此使用vector来封装效率太低
		// 可借助list...来模拟实现queue
		// 咩有迭代器
	public :
		// 入队，队尾入队，链表尾插
		void push(const T& e) { _con.push_back(e); };

		// 出队，队头出队，链表的首元素删除
		void pop() { _con.pop_front(); }

		// 获取队头元素
		T& top() { return _con.front(); }

		// 返回栈的元素个数
		size_t size() const { return _con.size(); }

		// 判空
		bool empty() const { return _con.empty(); }

	private:
		Container _con;
	};
}