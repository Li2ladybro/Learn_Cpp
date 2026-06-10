#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;


/*
* 懒汉模式
* 第一次使用才创建实例
*/
namespace lazy_man
{
    /*
    * 之前已经学过一些设计模式：
    * 迭代器模式——基于面向对象三大特性之一的封装设计出来的，用一个迭代器类封装以后，不暴露容器的结构的情况下，有统一的方式访问修改容器中的数据。
    * 适配器模——体现的是一种复用思想。
    * 还有一些常见的设计模式如：工厂模式、装饰器模式、观察者模式、单例模式...
    * 单例模式：一个类只能在全局(进程中)只有一个实例对象。
    * 什么场景下使用?比如一个进程中有一个内存池，进程中的多线程需要的内存都要到这个内存池中取，那么这个内存池的类就可以设计单例模式。
    */

    // 类的名称是随着你的场景给的，比如你的是内存池，那么你就定义成 Memorypool

    class SingLeton
    {
    public:
        // 删除拷贝构造
        SingLeton(const SingLeton& sl) = delete;

        // 获取实例
        static SingLeton* GetInstance()
        {
            //_mux.lock();
            // 双检查，可以避免后面的线程加锁
            if (_pinst == nullptr)
            {
                unique_lock<mutex> lock(_mux);
                if (_pinst == nullptr)
                {
                    _pinst = new SingLeton;
                }
            }
            //_mux.unlock();
            return _pinst;
        }

        // 释放
        static void DeleteInstance()
        {
            unique_lock<mutex> lock(_mux);
            delete _pinst;
            _pinst = nullptr;
        }


    private:
        SingLeton()
        {
        }
        // 静态成员函数在类中声明
        static SingLeton* _pinst;
        static mutex _mux;
    };

    /* 1、如果要手动释放单例对象，可以手动调用DeleteInstance */
    /* 2、如果需要在程序结束时，自动释放单例对象，可以添加GC类 */

    class GC
    {
    public:
        ~GC()
        {
            SingLeton::DeleteInstance();
        }
    };

    /* 定义成静态的只在当前文件可见，并且程序结束时会自动调用其析构函数 */
    static GC gc;

    // 类外定义
    SingLeton* SingLeton::_pinst = nullptr;
    mutex SingLeton::_mux;


    int x()
    {
        int n = 1000;
        vector<thread> vthread;
        for (int i = 0;i < n;++i)
        {
            vthread.push_back(thread([]() {
                cout << SingLeton::GetInstance() << endl;
                }));
        }

        for (int i = 0;i < n;++i)
        {
            vthread[i].join();
        }

        cout << SingLeton::GetInstance() << endl;
        cout << SingLeton::GetInstance() << endl;
        cout << SingLeton::GetInstance() << endl;

        return 0;
    }
}

/*
* 饿汉模式
* 在main函数之前就创建对象
*/
namespace hungry_man
{
    class SingLeton
    {

    public:
        SingLeton(const SingLeton& s) = delete;

       static SingLeton& GetInstance()
        {
            return _pinst;
        }
    private:
        SingLeton()
        { }
        static SingLeton _pinst;

    };

    SingLeton SingLeton::_pinst;

    int x()
    {
        int n = 1000;
        vector<thread> vthread;
        for (int i = 0;i < n;++i)
        {
            vthread.push_back(thread([]() {
               // cout << SingLeton::GetInstance() << endl;
                }));
        }

        for (int i = 0;i < n;++i)
        {
            vthread[i].join();
        }

        //cout << SingLeton::GetInstance() << endl;
        //cout << SingLeton::GetInstance() << endl;
        //cout << SingLeton::GetInstance() << endl;

        return 0;
    }


}

int main()
{
    hungry_man::x();
    return 0;
}


/*
* 总结对比一下饿汉和懒汉的区别
* 1、懒汉模式需要考虑线程安全和释放的问题，实现相对更复杂，饿汉模式不存在以上问题，实现简单。
* 2、懒汉是一种懒加载模式需要时在初始化创建对象，不会影响程序的启动。饿汉模式则相反，程序启动阶段就创建初始化实力对象，会导致程序启动慢，影响体验。
* 3、如果有多个单例类，假设有依赖关系(B依赖A)，要求A单例先创建初始化，B单例再创建初始化，那么就不能饿汉，因为无法保证创建初始化顺序，这时用懒汉我们就可以手动控制。
* 总结一下：实际中懒汉模式还是更实用一些
*/