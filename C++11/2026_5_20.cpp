//#define _CRT_SECURE_NO_WARNINGS
//
//#include <iostream>
//#include <vector>
//#include <list>
//#include <string>
//#include <map>
//#include <set>
//#include <string.h>
//
//using namespace std;


/* class A
{
public:
    //C++11

    // 指定显示去生成默认构造函数A()
    A() = default;
    // 不用默认生成的
    A(const A& aa) = delete;
    A& operator=(const A& aa) = delete;

private:
    int a = 10;
}; */

/* int main()
{
    int x = 0;
    int y{ 1 };

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // C++11花括号列表初始化，其实在实际中并不常用，除非是初始化容器
    vector<int> v1 = { 1,3,4,5 };
    vector<int> v2{ 1,3,4,5 };

    list<int> l1{ 1,3,4,5 };
    list<int> l2 = { 1,3,4,5 };

    cout << typeid(l1).name() << endl;
    cout << typeid(v1).name() << endl;

    map<string, int> m1{ {"Sort",1},{"李白",1} };

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // final与override(了解)
    // 回忆一下这两个关键字分别的作用是什么 ?
    // final修饰类，类就变成了最终类，不能被继承
    // final还可以修饰虚函数，这个虚函数不能被重写override是子类重写虚函数，检查是否完成重写。不满足重写的条件，则报错。


    ///////////////////////////////////////////////////////////////////////////////////////////////////////
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

} */


/* template<class T>
void func(const T& u)
{
    cout << "void func(const T & u)" << endl;
}

template<class T>
void func(const T&& u)
{
    cout << "void func(const T&& u)" << endl;
}

int main()
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // 右值引用和移动语义(重点)
    // C++98 就提出了引用的概念，引用就给一个对象取别名。
    // C++98 左值引用
    // C++11 右值引用
    // 不管是左值引用，还是右值引用，他们都是给对象取别名。
    // 不过左值引用主要是给左值取别名，右值引用主要是给右值取别名。
    // 什么是左值?什么是右值?
    // =左边就是左值?右边的就是右值?注意这个是一个C语法就留下的坑，就像左移和右移一样
    // 这里左右不是方向。左边的值也不一定左值，右边的值不一定是右值
    // int xl=10;int x2=xl; 这里x1是左值，10是右值，x2是左值
    // 可以修改就可以认为是左值，左值通常是变量
    // 右值通常是常量，表达式或者函数返回值（临时对象)


    int x = 1, y = 2;

    // 左值引用的定义（为左值起别名，本质上是为一个一个变量起别名）
    int a = 0;int& b = a;

    // 左值引用不能直接引用右值，const左值引用可以
    // int& e= 10;
    // int& f = x+y;

    const int& e = 10;
    const int& f = x + y;


    // 右值引用的定义（为右值起别名，为一个常量起别名）
    int&& c = 10;
    int&& d = x + y;

    // 右值引用不能直接引用左值，但是可以引用move后的左值，左值被move后，会变成右值也就是一个将亡值
    // int&& m = a;
    int&& m = move(a);

    func(1);          // 调用右值引用
    func(a);          // 调用左值引用

    return 0;
} */


/*
 class String
{

public:

    String(const char* str = "")
    {
        _str = new char[strlen(str) + 1];
        strcpy(_str, str);
    }

    // s2(s1)
    // 传递左值用深拷贝
    String(const String& s)
    {
        cout << "String(const String& s)-深拷贝" << endl;
        _str = new char[strlen(s._str) + 1];
        strcpy(_str,s._str);
    }

    // 是一个(右值-将亡值)
    // 传递右值用浅拷贝
    // 移动拷贝，其实就是移动资源，将一个将亡值，直接把它的资源拿过来用就行了，不需要再去申请内存了，效率高
    String(String&& s)
        :_str(nullptr)
    {
        cout << "String(String&& s))-移动拷贝-代价小-高效" << endl;
        swap(_str, s._str);
    }

    ~String()
    {
        delete[] _str;
    }

    String& operator=(const String& s)
    {
        if (this != &s)
        {
            cout << "String& operator=(const String& s)-深拷贝" << endl;

            char* newstr = new char[strlen(s._str) + 1];
            strcpy(newstr, s._str);

            delete _str;
            _str = newstr;
        }
        return *this;
    }

    String& operator=(String&& s)
    {
        cout << "String& operator=(String&& s)-浅拷贝-移动赋值" << endl;
        swap(_str, s._str);
        return *this;
    }

    // s1+s2
    String operator+(const String& s)
    {
        String ret(*this);
        //ret.append(s._str);
        return ret;
    }

    // s1+=s2
    String& operator+=(const String& s)
    {
        //this->append(s._str);
        return *this;
    }

private:
    char* _str;
};

String f(const char* str)
{
    String tmp(str);
    return tmp;                            // 这里返回实际是拷贝tmp的临时对象
} */

// C++11又将右值区分为:纯右值和将亡值
// 纯右值:基本类型的常量或者临时对象
// 将亡值:自定义类型的临时对象
// 结论:所有深拷贝类(vector/list/map/set...)，都可以加两个右值引用做参数的移动拷贝和移动赋值
// 右值可以被别人掠夺资源

/*
int main()
{
    String s1("左值");
    String s2(s1);                         // 参数是左值
    String s3(f("右值-将亡值"));           // 参数是右值-将亡值(传递给你用，用完我就析构了)
    //String s4(move(s1));
    String s5("桌你才能");
    s5 = s2;
    s5 = f("ivbnbvvievnovvvvv");

    return 0;
} */


/* 
string f(const char* str)
{
    string tmp(str);
    return tmp;                            // 这里返回实际是拷贝tmp的临时对象
}

int main()
{
    string s1("左值");

    string s2(s1);

    string s3(f("临时对象"));

    return 0;
} */

//int main()
//{
//    String s1("s1");
//    String s2("s2");
//    String s3 = s2 += s1;     // 深拷贝
//    String s4 = s2 + s1;      // 移动拷贝
//
//
//    return 0;
//}