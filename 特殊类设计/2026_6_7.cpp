//#include <iostream>
//
//using namespace std;
//
//
///* 写出一个类只能在堆上面创建 */
///* 思路：每次创建处象一定会调用构造函数 */
//
//class HeapOnly
//{
//
//public:
//
//    // C++11的保护
//    HeapOnly(HeapOnly& ho) = delete;
//
//    static HeapOnly* GetObj()
//    {
//        return new HeapOnly;
//    }
//
//private:
//    HeapOnly()
//    {}
//
//    /*
//    // C++98的保护
//    HeapOnly(HeapOnly& ho)
//    {}
//    */
//};
//
//int x1()
//{
//    shared_ptr<HeapOnly> sp1(HeapOnly::GetObj());
//    // HeapOnly copy(*sp1);
//    return 0;
//}
//
///* 只能在栈上 */
//class StackOnly
//{
//public:
//    // 但是这种方式不完美，可以定义静态区的对象
//    // void* operator new(size_t num) = delete;
//    // void operator delete(void* p) = delete;
//
//    static StackOnly GetObj()
//    {
//        return StackOnly();
//    }
//
//private:
//    StackOnly()
//    { }
//
//};
//
//int x2()
//{
//    StackOnly so= StackOnly::GetObj();
//    return 0;
//}
//
//
///*
//之前已经学过一些设计模式：
//迭代器模式——基于面向对象三大特性之一的封装设计出来的，用一个迭代器类封装以后，不暴露容器的结构的情况下，有统一的方式访问修改容器中的数据。
//适配器模——体现的是一种复用思想。
//还有一些常见的设计模式如：工厂模式、装饰器模式、观察者模式、单例模式...
//单例模式：一个类只能在全局(进程中)只有一个实例对象。
//什么场景下使用?比如一个进程中有一个内存池，进程中的多线程需要的内存都要到这个内存池中取，那么这个内存池的类就可以设计单例模式。
//*/
//
//// 类的名称是随着你的场景给的，比如你的是内存池，那么你就定义成 Memorypool
//
//class SingLeton
//{
//public:
//    // 删除拷贝构造
//    SingLeton(const SingLeton& sl) = delete;
//
//    // 获取实例
//    static SingLeton* GetInstance()
//    {
//        if (_pinst == nullptr)
//        {
//            _pinst = new SingLeton;
//        }
//        return _pinst;
//    }
//
//private:
//    SingLeton()
//    { }
//    static SingLeton* _pinst;
//};
//
//SingLeton* SingLeton::_pinst = nullptr;
//
//#include <thread>
//#include <vector>
//
//int main()
//{
//    int n = 1000;
//    vector<thread> vthread;
//    for (int i = 0;i < n;++i)
//    {
//        vthread.push_back(thread([]() {
//            cout << SingLeton::GetInstance() << endl;
//        }));
//    }
//
//    for (int i = 0;i < n;++i)
//    {
//        vthread[i].join();
//    }
//
//    cout << SingLeton::GetInstance() << endl;
//    cout << SingLeton::GetInstance() << endl;
//    cout << SingLeton::GetInstance() << endl;
//
//    return 0;
//}