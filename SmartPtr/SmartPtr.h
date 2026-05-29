#pragma once
#include <iostream>

using namespace std;


namespace MySmartPtr
{

    // RAII（Resource Acquisition Is Initialization）是一种利用对象生命周期来控制程序资源（如内存、文件句柄、网络连接、互斥量等等）的简单技术。
    // 智能指针只是用到RALL思想的一种，还有别的

    // RAII+像指针一样
    template <class T>
    class SmartPtr
    {

    public:
        // 构造函数托管资源
        SmartPtr(T* ptr)
            :_ptr(ptr)
        {}

        // 析构函数释放资源
        ~SmartPtr()
        {
            if (_ptr)
            {
                cout << "delete：" << _ptr << endl;
                delete _ptr;
            }
        }

        T& operator*()
        {
            return *_ptr;
        }

        T* operator->()
        {
            return _ptr;
        }

    private:
        T* _ptr;
    };


    template <class T>
    // C++98 auto_ptr
    // 1、管理权限转移，早期的设计缺陷，一般是禁止使用的
    // 缺点：ap2=ap1场景下ap1就悬空了，再访问就越界访问呢，如果不熟悉特性，就会被坑
    class auto_ptr
    {
    public:
        auto_ptr(T* ptr)
            :_ptr(ptr)
        {}

        // 让只有一个指针托管
        auto_ptr(auto_ptr<T>& ap)
            :_ptr(ap._ptr)
        {
            ap._ptr = nullptr;
        }

        ~auto_ptr()
        {
            if (_ptr)
            {
                cout << "delete：" << _ptr << endl;
                delete _ptr;
                _ptr = nullptr;
            }
        }

        auto_ptr& operator=(auto_ptr<T>& ap)
        {
            if (this != &ap)
            {
                if (_ptr)
                {
                    delete _ptr;
                    _ptr = nullptr;
                }
                ::swap(_ptr, ap._ptr);
                return *this;
            }
        }

    private:
        T* _ptr;
    };

    template <class T>
    // C++11 unique_ptr
    // 2、防拷贝，简单粗暴，相对推荐使用
    // 缺陷：如果涉及到拷贝场景，就没法用
    class unique_ptr
    {

    public:
        unique_ptr(T* ptr)
            :_ptr(ptr)
        {}

        unique_ptr(unique_ptr<T>& ap) = delete;

        ~unique_ptr()
        {
            if (_ptr)
            {
                cout << "delete：" << _ptr << endl;
                delete _ptr;
                _ptr = nullptr;
            }
        }

        // 赋值
        unique_ptr& operator=(const unique_ptr<T>& ap) = delete;

        T& operator*()
        {
            return *_ptr;
        }

        T* operator->()
        {
            return _ptr;
        }

    private:
        T* _ptr;
    };

    //template <class T>
    //// C++11 shared_ptr
    //// 3、防拷贝，简单粗暴，相对推荐使用
    //// 缺陷：如果涉及到拷贝场景，就没法用
    //class shared_ptr
    //{

    //public:
    //    shared_ptr(T* ptr)
    //        :_ptr(ptr)
    //        ,_count(1)
    //    {}

    //    shared_ptr(shared_ptr<T>& ap)
    //        :_ptr(ap._ptr)
    //        ,_count(ap._count)
    //    {
    //        _count++;
    //        ap._count++;
    //    }

    //    ~shared_ptr()
    //    {
    //        if (--_count==0&&_ptr)
    //        {
    //            cout << "delete：" << _ptr << endl;
    //            delete _ptr;
    //            _ptr = nullptr;
    //        }
    //    }

    //    // 赋值
    //    //unique_ptr& operator=(const unique_ptr<T>& ap) = delete;

    //    T& operator*()
    //    {
    //        return *_ptr;
    //    }

    //    T* operator->()
    //    {
    //        return _ptr;
    //    }

    //private:
    //    T* _ptr;
    //    int _count;
    //};

    template <class T>
    // C++11 shared_ptr
    // 3、防拷贝，简单粗暴，相对推荐使用
    // 缺陷：如果涉及到拷贝场景，就没法用
    class shared_ptr
    {

    public:
        shared_ptr(T* ptr)
            :_ptr(ptr)
            //, _count(1)
        {
            _count = 1;
        }

        shared_ptr(shared_ptr<T>& ap)
            :_ptr(ap._ptr)
            //, _count(ap._count)
        {
            _count++;
        }

        ~shared_ptr()
        {
            if (--_count == 0 && _ptr)
            {
                cout << "delete：" << _ptr << endl;
                delete _ptr;
                _ptr = nullptr;
            }
        }

        // 赋值
        //unique_ptr& operator=(const unique_ptr<T>& ap) = delete;

        T& operator*()
        {
            return *_ptr;
        }

        T* operator->()
        {
            return _ptr;
        }

    private:
        T* _ptr;
        static int _count;
    };
    template <class T>
    int shared_ptr<T>::_count = 0;

    void test_unique_ptr()
    {
        unique_ptr<int> up(new int);
    }

    void test_shared_ptr()
    {
        shared_ptr<int> sp(new int);
        shared_ptr<int> sp1(sp);
    }
}