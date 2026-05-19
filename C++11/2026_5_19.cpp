#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>

using namespace std;


class A
{
public:
    //C++11

    // 指定显示去生成默认构造函数A()
    A()=default;
    // 不用默认生成的
    A(const A& aa) = delete;
    A& operator=(const A& aa) = delete;

private:
    int a = 10;
};
int main()
{
    int x = 0;
    int y{ 1 };

    // C++11花括号列表初始化，其实在实际中并不常用，除非是初始化容器
    vector<int> v1 = {1,3,4,5};
    vector<int> v2{1,3,4,5};

    list<int> l1{1,3,4,5};
    list<int> l2 = {1,3,4,5};

    cout << typeid(l1).name() << endl;
    cout << typeid(v1).name() << endl;

    map<string, int> m1{{"Sort",1},{"李白",1}};

    // 类型推导，属于RTTI (run time type identification)运行时类型辨别
    // 也用的不多
    cout << typeid(x).name() << endl;

    // 推导出容器的类型，再创建与其一样的对象
    decltype(l1) e;
    decltype(v1) e1;

    cout << typeid(e).name() << endl;
    cout << typeid(e1).name() << endl;


    // 范围for循环，C++11引入的语法糖，简化了迭代器的使用
    // 以及auto类型推导，使用起来非常方便

    // auto不可以做形参和返回值
    // auto func(auto e)
    // { }

    // 1、auto和范围for的优势在于可以推导出复杂的类型，尤其是容器的迭代器类型，避免了冗长的代码
    // 2、但是影响了代码的可读性，尤其是对于初学者来说，可能不太清楚auto推导出的类型是什么
    // 3、所以在使用auto时要注意平衡代码的简洁性和可读性。
    // 4、当容器存在的对象比较大时，最好使用&和const，避免不必要的复制，提高效率
    // 5、范围for最终会被编译器转换成迭代器的形式，所以性能和传统的迭代器是一样的。
    std::map < std::string, std::string> dict = { {"inset","插入"},{"erase","删除"},{"find","查找"} };
    for (const auto& i : dict)
    {
        cout << i.first << ": " << i.second << " ";
    }

    cout << endl;

    std::map < std::string, std::string>::iterator it = dict.begin();

    while (it != dict.end())
    {
        cout << it->first << ": " << it->second << " ";
        it++;
    }

    // final与override(了解)
    // 回忆一下这两个关键字分别的作用是什么 ?
    // final修饰类，类就变成了最终类，不能被继承
    // final还可以修饰虚函数，这个虚函数不能被重写override是子类重写虚函数，检查是否完成重写。不满足重写的条件，则报错。

    // 新容器
    // C++98   容器：string（字符串）
    //               vector（可增容的顺序表）
    //               list（双向循环链表）
    //               deque（双端队列）
    //               map（图，红黑树）
    //               set（集合，红黑树）
    //               bitset（位图）
    //       适配器：stack（栈）
    //               queue（队列）
    //               priority_queue（优先级队列）
    // C++11 新容器：array（定长数组）：实际中用的很少，
    //               缺点:定长 + 存储数据的空间在栈上，栈的空间本来就不大。
    //               forword_list(单链表)：实际中用得少，想当于单链表
    //               缺点：不支持尾插尾删 + insert数据也是在当前位置的后面
    //               unordered_map / unordered_set：推荐使用，因为他们的效率高于map / set，底层为哈希表
    return 0;
}