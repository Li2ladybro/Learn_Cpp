/*
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <string.h>

using namespace std;


///////////////////////////////////////////////////////////////////////////////////////////////////////
// 4、右值引用去做函数的参数,减少拷贝

// std::vector::push_back
// void push_back(const value_type& val);
// void push_back(value type&& val);
//
// std::list::push back
// void push_back(const value_type& val);
// void push_back(value_type&& val);
//
// std::set::insert
// pair<iterator, bool>insert(const value_type& val);
// pair<iterator, bool> insert (value_type&& val);
//
// 其他容器的插入数据结构也基本都是两个重载实现，一个左值引用，一个右值引用

int main()
{
    vector<string> v;
    string s1("左值");
    int val = 2345;
    // 这里调用的是string的拷贝构造（深拷贝）
    v.push_back(s1);               // void push_back(const value_type& val);

    // 这个是调用string的移动构造
    v.push_back("右值");           // void push_back(value type&& val);
    v.push_back(to_string(val));   // void push_back(value type&& val);

    vector<pair<string, string>> vp;
    vp.push_back(make_pair("右值", "右值"));

    pair<string, string> kv("左值", "左值");
    vp.push_back(kv);



    vp.emplace_back(make_pair("右值", "右值"));
    vp.emplace_back(kv);

    // template <class... _Valty>
    // emplace_back(_Valty&&... _Val)
    vp.emplace_back("右值", "右值");         //体现emplace_back模板可变参数特点的地方

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// 总结
// 右值引用做参数和作返回值减少拷贝的本质是利用了移动构造和移动赋值
// 左值引用和右值引用本质的作用都是减少拷贝，右值引用本质可以认为是弥补左值引用不足的地方，他们两个相辅相成

// 左值引用：解决的是传参过程中和返回值过程中的拷贝
// 做参数：void push(T x) -> void push(const T& x) 解决的是传参过程中减少拷贝
// 做返回值：T f2() -> T & f2()解决的返回值过程中的拷贝
// ps：但是要注意这里有限制，如果返回对象出了作用域不在了就不能用传引用，这个左值引用无法解决，等待C++11右值引用解决

// 右值引用：解决的是传参后，push/insert函数内部将对象移动到容器空间上的问题
// +传值返回接收返回值的拷贝
// 做参数：void push(T&& x)解决的push内部不再使用拷贝构造x到容器空间上，而是移动构造过去
// 做返回值：T f2(); 解决的外面调用接收f2()返回对象的拷贝，T ret=f2()，这里会调用，右值引用的移动构造版本构造函数，减少了拷贝
*/