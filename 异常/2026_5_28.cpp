#include <iostream>
#include <vector>
#include <string>

using namespace std;


// 什么是异常：异常是面向对象语法处理错误一种方式
// C语言传统的处理错误的方式有哪些呢?
// 1、返回错误码，有些API接口都是把错误码放到errno中
// 2、终止程序，比如发生越界等严重问题时，我们也可以主动调用exit(xx)、assert;

// 传统的处理错误的缺陷：
// a、拿到错误码，需要查找错误码表，才知道是什么错误
// b、如果一个函数是用过返回值拿数据，发生错误时很难处理
// c、如果调用的函数栈很深，一层层返回错误码，整个处理很难受
// 
// T& operator[](int index)
// {
//      如果index超出的容器范围，如何返回?
// }

/* 
int main()
{

    vector<int> vec = { 1,2,3,4,5,6};

    try
    {
        for (int i = 0;i <= vec.size();++i)
            cout << vec.at(i) << ' ';
        cout << endl;
    }

    catch (exception& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
*/

/*
int divc(int& n, int& m)
{
    if (m == 0)
        // 1、throw后直接往有watch的地方走，并且是和catch匹配的地方
        // 2、throw可以抛出任意类型的对象
        throw string("发生除零错误");
        //throw "发生除零错误";

    return n / m;
}

int main()
{
    int n, m;
    cin >> n >> m;
    try
    {
        cout << divc(n, m) << endl;
    }

    catch (const int& e)
    {
        cout << e;
    }

    catch (const string& e)
    {
        cout<<__LINE__ << e;
    }

    catch (...)
    {
        cout << __LINE__ << "：未知异常"<<endl;
    }
    return 0;
}
*/

class Excption
{

public:
    Excption(int errorId, string errorMsg)
        :_errorId(errorId)
        ,_errorMsg(errorMsg)
    {}

    virtual string what() = 0;

protected:
    int _errorId;
    string _errorMsg;
};

class SqlException : public Excption
{

public:
    SqlException(int errorId, string errorMsg)
        :Excption(errorId, errorMsg)
    {}

    virtual string what()
    {
        return "SQL异常：" + _errorMsg;
    }
};

class NetWorkException : public Excption
{

public:
    NetWorkException(int errorId, string errorMsg)
        :Excption(errorId, errorMsg)
    {}

    virtual string what()
    {
        return "网络异常：" + _errorMsg;
    }
};


void ServerStart()
{
    if (rand() % 2 == 0)
    {
        throw SqlException(2,"连接数据库失败");
    }

    if (rand() % 5 == 0)
    {
        throw NetWorkException(5, "网络连接失败");
    }

    cout << "服务器正常启动..." << endl;
}


int main()
{

    for (int i = 0;i < 10000;++i)
    {
        try
        {
            ServerStart();
        }

        catch (Excption& e)
        {
            cout << e.what() << endl;
        }

        catch (...)
        {
            cout << "未知异常" << endl;
        }
     }

    return 0;

}

// 异常总结：

// 优点:
// 1、清晰的包含错误信息
// 2、面对T operator[](int i)这样函数越界错误，异常可以很好的解决
// 3、多层调用时，里面发生错误，不再需要层层处理，最外层直接捕获即可
// 4、很多第三方库都是用异常，我们也使用异常可以更好的使用他们。比如 : boost、gtest、gmock

// 缺点:
// 1、异常会导致执行流乱跳。会给我调试分析程序bug带来一些困难。
// 2、C++没有GC，异常可能导致资源泄露等异常安全问题，需要学会使用RAII来解决。
// 3、C++的库里面的异常体系定义不太好用，很多公司都会选择自己定义。
// 4、C++的异常语言可以抛任意类型的异常，如果项目中没有做很好规范管理，那么会非常的混乱，所以一般需要定义出继承体系的异常规范。

// 异常整体而言还是一个利大于弊的东西，所以实际日常练习或者小项目，不太使用
// 公司一般还是会选择异常来处理错误