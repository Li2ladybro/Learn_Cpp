#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;


/*
struct Goods
{
    string _name;
    float  _price;
    int    _num;
};

struct CompareNameGreater
{
    bool operator() (const Goods& gl, const Goods& gr)
    {
        return gl._name > gr._name;
    }
};
// 其实还有小于的，大于等于和小于等于，会发现我们要写很多个仿函数

int main()
{

    Goods gds[] = {
            {"苹果",2.1,3},
            {"香蕉",3.0,5},
            {"橙子",2.2,9},
            {"菠萝",1.5,10}
};

    sort(gds, gds + sizeof(gds) / sizeof(gds[0]), [](const Goods& g1, const Goods& g2) {
        return g1._name > g2._name;});
    sort(gds, gds + sizeof(gds) / sizeof(gds[0]), [](const Goods& g1, const Goods& g2) {
        return g1._name < g2._name;});

    sort(gds, gds + sizeof(gds) / sizeof(gds[0]), [](const Goods& g1, const Goods& g2) {
        return g1._price > g2._price;});
    sort(gds, gds + sizeof(gds) / sizeof(gds[0]), [](const Goods& g1, const Goods& g2) {
        return g1._price < g2._price;});


    sort(gds, gds + sizeof(gds) / sizeof(gds[0]), [](const Goods& g1, const Goods& g2) {
        return g1._num > g2._num;});
    sort(gds, gds + sizeof(gds) / sizeof(gds[0]), [](const Goods& g1, const Goods& g2) {
        return g1._num < g2._num;});

    return 0;
} */


// lambda表达式实际是一个匿名函数
// lambda表达式书写格式：[capture - list](parameters) mutable -> return-type{ statement}
// [capture - list] : 捕捉列表，该列表总是出现在lambda函数的开始位置，编译器根据[]来
// 判断接下来的代码是否为lambda函数，捕捉列表能够捕捉上下文中的变量供lambda函数使用。
// (parameters)：参数列表。与普通函数的参数列表一致，如果不需要参数传递，则可以连同()一起省略
// mutable：默认情况下，lambda函数总是一个const函数，mutable可以取消其常量性。使用该修饰符时，参数列表不可省略(即使参数为空)。
// ->returntype：返回值类型。用追踪返回类型形式声明函数的返回值类型，没有返回值时此部分可省略。返回值类型明确情况下，也可省略，编译器对返回类型进行推导。
// { statement }：函数体。在该函数体内，除了可以使用其参数外，还可以使用所有捕获到的变量

/*
int main()
{
    // 最简单的lambda表达式, 该lambda表达式没有任何意义
    [] {};

    // 参数列表有值
    int a = 8, b = 10;
    auto add1 = [](int x1, int x2)->int {return x1 + x2;};
    add1(a, b);

    // 直接捕获a,b此时参数列表为空
    // auto add2 = [a, b]()->int {return a + b;};

    // 返回值可以省略不写，自动推
    auto add2 = [a, b]() {return a + b;};

    int ol=add2();

    auto swap1 = [](int& x1, int& x2) {
        int x = x1;
        x1 = x2;
        x2 = x;
    };
    swap1(a, b);
    return 0;
}
通过上述例子可以看出，lambda表达式实际上可以理解为无名函数，该函数无法直接调用，如果想要直接调用，可借助auto将其赋值给一个变量。
*/


/*
// lambda表达式其实定义函数内存的匿名函数函数
// 1、掌握lambda表达式写的格式
// 2、lambda表达式的使用场景(对比仿函数对象、函数指针)
// 3、lambda表达式的原理
// [捕捉列表](参数)->返回值类型{函数体}

int main()
{
    int a=0, b= 1;
    //实现一个a+b的lambda表达式
    auto add1 = [](int xl, int x2) ->int {
    return xl + x2;
    };
    cout << add1(a, b) << endl;

    // 捕捉列表就是捕捉跟我一个作用域的对象
    // 传值捕捉[a]捕捉a；[a,b]捕捉a，b；[=]捕捉同一作用域中的所有对象，传值补充的对象是不能被改变的。(加上mutable就可以改变了)
    // 传引用捕捉[&a]捕捉a；[&a,&b]捕捉a，b；[&]捕捉同一作用域中的所有对象

    auto add2 = [a, b]() ->int {
    return a + b;
    };
    add2();

    //实现a和b交换
    auto swap = [](int& a, int& b) {
        int c = a;
        a = b;
        b = c;
        };

    return 0;
} */


int main()
{
    int a = 1, b = 2;

    // 对象=对象(替换编译器生成的lamber_uuid仿函数的对象)
    auto add = [](int x, int y)->int{
        return x + y; };

    add(a, b); // call lamber_uuid仿函数的operator()

    // 底层还是依靠仿函数来实现，也就是说你定义了一个lamber表达式
    // 实际上编译器会全局域生成一个叫lamber_uuid类，仿函数的operator()的参数和实现
    // 就是我们写的1abmber表达式的参数和实现

    //003D27EE  mov         eax, dword ptr[b]
    //003D27F1  push        eax
    //003D27F2  mov         ecx, dword ptr[a]
    //003D27F5  push        ecx
    //003D27F6  lea         ecx, [add]
    //003D27F9  call        `main'::`2': : <lambda_1>::operator() (03D2410h)

    cout << typeid(add).name()<<endl;
    return 0;
}