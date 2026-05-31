#pragma once
#include <iostream>
#include <thread>
#include <mutex>

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
    //        ,_pcount(1)
    //    {}

    //    shared_ptr(shared_ptr<T>& ap)
    //        :_ptr(ap._ptr)
    //        ,_pcount(ap._pcount)
    //    {
    //        _pcount++;
    //        ap._pcount++;
    //    }

    //    ~shared_ptr()
    //    {
    //        if (--_pcount==0&&_ptr)
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
    //    int _pcount;
    //};

    //template <class T>
    //// C++11 shared_ptr
    //// 3、防拷贝，简单粗暴，相对推荐使用
    //// 缺陷：如果涉及到拷贝场景，就没法用
    //class shared_ptr
    //{

    //public:
    //    shared_ptr(T* ptr)
    //        :_ptr(ptr)
    //        //, _pcount(1)
    //    {
    //        _pcount = 1;
    //    }

    //    shared_ptr(shared_ptr<T>& ap)
    //        :_ptr(ap._ptr)
    //        //, _pcount(ap._pcount)
    //    {
    //        _pcount++;
    //    }

    //    ~shared_ptr()
    //    {
    //        if (--_pcount == 0 && _ptr)
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
    //    static int _pcount;
    //};
    //template <class T>
    //int shared_ptr<T>::_pcount = 0;


    template <class T>
    // C++11 shared_ptr
    // 3、优点：改进了，unique_ptr无法拷贝的问题，
    //          线程安全，有锁，推荐使用
    // 缺陷：循环引用
    class shared_ptr
    {
    public:

        shared_ptr(T* ptr = nullptr)
            : _ptr(ptr)
            , _pcount(new int(1))
            , _mu(new mutex)
        {}

        shared_ptr(shared_ptr<T>& ap)
            : _ptr(ap._ptr)
            , _pcount(ap._pcount)
            , _mu(ap._mu)
        {
            //(*_pcount)++;
            add_ref_count();
        }

        ~shared_ptr()
        {
            release();
        }

        // 赋值
        // sp1 = sp2，sp1对之前的资源不再管理，现在要让sp1同sp2一起管理同一片空间
        shared_ptr& operator=(const shared_ptr<T>& ap)
        {
            if(this!=&ap)
            {
                //if (--(*_pcount) == 0)
                //{
                //    cout << "delete：" << _ptr << endl;

                //    delete _ptr;
                //    delete _pcount;

                //    _ptr = nullptr;
                //    _pcount = nullptr;

                //    //_ptr = ap._ptr;
                //    //_pcount = ap._pcount;
                //    //(*_pcount)++;
                //}
                //else
                //{
                //    (*_pcount)--;
                //}
                
                // 不再管理之前的资源
                release();
                if(_ptr==nullptr)
                {
                    _ptr = new T;
                    _pcount = new int;
                }

                _ptr = ap._ptr;
                _pcount = ap._pcount;
                //(*_pcount)++;
                add_ref_count();
            }
            return *this;
        }

        void add_ref_count()
        {
            _mu->lock();
            (*_pcount)++;
            _mu->unlock();
        }

        void release()
        {
            bool flag = false;
            _mu->lock();
            if (--(*_pcount) == 0&&_ptr)
            {
                cout << "delete：" << _ptr<<endl;
                delete _ptr;
                delete _pcount;

                _ptr = nullptr;
                _pcount = nullptr;

                flag = true;
            }
            _mu->unlock();

            if (flag)
            {
                delete _mu;
                _mu=nullptr;
            }
        }

        T* get_ptr()
        {
            return _ptr;
        }

        T& operator*()
        {
            return *_ptr;
        }

        T* operator->()
        {
            return _ptr;
        }

        int use_count()
        {
            return *_pcount;
        }

    private:
        T* _ptr;

        // 记录有多少对象一起共享管理资源，最后一个析构释放资源
        int* _pcount;

        // 锁保护
        mutex* _mu;

    };

    template <class T>
    // 严格来说weak_ptr不是智能指针，因为他没有RAII资源管理机制，用来解决shared_ptr的循环引用问题
    class weak_ptr
    {
    public:
        weak_ptr() = default;

        weak_ptr(const shared_ptr<T>& sp)
            :_wk(sp.get_ptr())
        {}

        weak ptr<T>& operator = (const shared_ptr<T>& sp)
        {
            _wk = sp.get_ptr();
            return *this;
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
        shared_ptr<T> _wk;
    };

    void test_unique_ptr()
    {
        unique_ptr<int> up(new int);
    }

    void test_shared_ptr()
    {
        shared_ptr<int> sp1(new int);
        shared_ptr<int> sp2(new int);
        shared_ptr<int> sp3(sp2);
        shared_ptr<int> sp4(sp2);

        sp4 = sp1;
    }

    void test_shared_ptr1()
    {

        shared_ptr<int> sp(new int);
        cout << sp.use_count() << endl;

        int n = 100000;

        thread t1([&]()
            {
                for(int i=0;i<n;++i)
                shared_ptr<int> sp1(sp);
            });

        thread t2([&]()
            {
                for (int i = 0;i < n;++i)
                shared_ptr<int> sp2(sp);
            });

        t1.join();
        t2.join();

        cout << sp.use_count()<<endl;
    }

    // 循环引用
    void test_shared_ptr2()
    {

        struct ListNode
        {
            int val;
            shared_ptr<ListNode> prev;
            shared_ptr<ListNode> next;
        };

        shared_ptr<ListNode> sp1(new ListNode);
        shared_ptr<ListNode> sp2(new ListNode);

        cout << sp1.use_count()<<endl;
        cout << sp2.use_count()<<endl;

        // 会导致循环引用
        sp1->next = sp2;
        sp2->prev = sp1;
        cout << sp1.use_count() << endl;
        cout << sp2.use_count() << endl;

    }

}