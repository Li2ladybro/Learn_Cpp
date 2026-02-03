#pragma once
#include <vector>

/* template <class T>
* structure less
* {
* // 仿函数/函数对象
*		bool operator(const T& e1,const T& e2)
* 			return e1<e2;
* }
* struct less 
*{
*   _NODISCARD constexpr bool operator()(const _Ty& _Left, const _Ty& _Right) const
* {
*			return _Left < _Right;
*	}
*	};
struct greater {
	using _FIRST_ARGUMENT_TYPE_NAME _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS  = _Ty;
	using _SECOND_ARGUMENT_TYPE_NAME _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS = _Ty;
	using _RESULT_TYPE_NAME _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS          = bool;

	_NODISCARD constexpr bool operator()(const _Ty& _Left, const _Ty& _Right) const
	{
			return _Left > _Right;
	}
* 
*/
namespace priority_queue_2026_2_3
{
	template <class T, class Container = vector<T> ,class Compare =less<T>>
	class priority_queue
	{
		// 优先级队列，默认大数优先级高=大根堆
	public:

		void AdJustUp(int child)
		{
			Compare com;
			// 向上调整算法
			int parent = (child - 1) / 2;
			while (child)
			{
				// O(n) = logn;
				// if (_con[child] > _con[parent])
				if (com(_con[parent],_con[child]))
				{
					::swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
					break;

			}
		}

		void AdJustDown(int root)
		{
			// 向下调整算法
			Compare com;
			int parent = root;
			int child = parent * 2 + 1; // 默认左孩子大
			while (child < _con.size())
			{
				// O(n) = logn;
				// 获取较大孩子的下标

				// if (child + 1 < _con.size() && _con[child] < _con[child + 1])
				if (child + 1 < _con.size() && com(_con[child] , _con[child+1]))
					++child;

				// if (_con[child] > _con[parent])
				if (com(_con[parent], _con[child]))
				{
					::swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
					break;
			}
		}

		void push(const T& e)
		{
			// 默认就是一个堆
			_con.push_back(e);
			// 堆调整
			AdJustUp(_con.size() - 1);
		}

		void pop()
		{
			::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			AdJustDown(0);
		}

		T& top()
		{
			return _con[0];
		}

		size_t size() const
		{
			return _con.size();
		}

		bool empty() const
		{
			return _con.empty();
		}

	private:
		Container _con;
	};
}