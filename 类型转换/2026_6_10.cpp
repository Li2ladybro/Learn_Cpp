#include<iostream>

using namespace std;


class A
{
public:
    virtual void func()
    {};
    int _a;
};

class B: public A
{
public:
    int _b;
};

//    * 
//    * int x()
//    * {
//    *     int a = 10;
//    *     double b = 20.99;
//    * 
//    *     int* c = nullptr;
//    * 
//    *     a = b;             // （相近类型转换）隐式类型转换，b的精度会被截断为整数部分，赋值给a
//    *     c = (int*)a;       // （不相近类型转换）强制类型转换，将a的值解释为一个指针地址，赋值给c
//    * 
//    * 
//    *     cout << "The value of a is: " << a << endl;
//    *     cout << "The value of b is: " << b << endl;
//    *     cout << "The value of c is: " << c << endl;
//    * 
//    * 
//    * 
//    *     /*
//    *     * C++ 兼容C语言留下来的隐式转换和显示转换，但是C++觉得C语言做得不规范，C++想规范一下标准C++为了加强类型转换的可视性，引入了四种命名的强制类型转换操作符
//    *     * static_cast, reinterpret_cast, const_cast, dynamic_cast
//    *     * cast：投射（光、影子等）
//    *     * reinterpret：重新解释
//    *     */
//    *     b = static_cast<double>(a);     // 使用static_cast进行类型转换（对标隐式/相近类型转换），将a转换为double类型赋值给b
//    *     c = reinterpret_cast<int*>(a);  // 使用reinterpret_cast进行类型转换（对标强制/不相近类型转换），将a的值解释为一个指针地址，赋值给c
//    * 
//    *     cout << "The value of a is: " << a << endl;
//    *     cout << "The value of b is: " << b << endl;
//    *     cout << "The value of c is: " << c << endl;
//    * 
//    *     cout << "The type of a is: " << typeid(a).name() << endl;
//    *     cout << "The type of b is: " << typeid(b).name() << endl;
//    *     cout << "The type of c is: " << typeid(c).name() << endl;
//    * 
//    * 
//    *     // 添加volatile关键字，告诉编译器这个变量的值可能会被外部因素改变，禁止编译器对其进行优化
//    *     // volatile const int e = 10;
//    * 
//    *     const int e = 10;
//    *     //int* p =(int*) & e;
//    * 
//    * 
//    *     /* 对标C语言中强制类型转换（去掉const属性的不相近类型），使用const_cast去掉e的const属性，使其成为一个普通的int指针 */
//    *     int* p = const_cast<int*>(&e);
//    * 
//    *     *p = 20;
//    *     cout << *p << endl;
//    * 
//    *     // 这里打印的是10，因为e是一个常量，编译器可能会将其优化为一个立即数（可能存在了寄存器），而不是存储在内存中的变量，
//    *     // 所以即使我们通过指针修改了内存中的值，e的值仍然被视为10。
//    *     cout << e << endl;
//    * 
//    *     cout << &e<<endl;
//    *     cout << p << endl;
//    * 
//    *     return 0;
//    * }
//    * 
//*/


void f_cast(A* pa)
{
    /*
    * 大给小/父类转换给子类/向下转换会失败
    * 此时pb会返回空
    */


    B* pb = dynamic_cast<B*>(pa);
    if (pb != nullptr)
    {
        cout<<"转换成功：pa指向子类对象"<<endl;
        pb->_a = 1;
        pb->_b = 2;
    }

    else
    {
        cout << "转换失败：pa指向父类对象" << endl;
    }


    /*
    * dynamic_cast向下转换只能针对继承中的多态类型（父类中需要包虚函数）
    * dynamic cast如何识别指针是指向父类对象还是子类对象的呢?
    * dynamic cast的原理是啥：
    * dynamic_cast通过去虚表的上方存储的标识信息，来判断指向父类对象还是子类对象
    */
}
int main()
{
    A a;
    B b;

    /*
    * C++中子类对象可以赋值给父类的对象、指针、引用，这个过程中会发生切片，这是语法天然支持的，这个叫向上转换（子类给父类），都可以成功。
    * 如果是父类的指针或者引用，传给子类的指针，这个过程叫向下转换，这个过程有可能失败
    * 要看具体情况
    */

    A* pa = &a;
    // 这里的pa指向父类
    f_cast(pa);

    pa = &b;
    // 这里的pa是由子类转换为父类得来的
    f_cast(pa);

    return 0;

}