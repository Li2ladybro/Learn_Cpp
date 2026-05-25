#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;


//mutex mut;
//
//size_t x = 0;
//
//void add(int n)
//{
//    // 串行化访问共享资源，一个线程结束后另一个线程才能开始
//    /*
//    mut.lock();
//    for (int i = 0;i < n;++i)
//    {
//        ++x;
//    }
//    mut.unlock();
//    */
//
//    // 并行化访问共享资源
//    for (int i = 0;i < n;++i)
//    {
//        mut.lock();
//        ++x;
//        mut.unlock();
//    }
//
//    // 思考为啥这里串行的效率高？
//    // 因为这里锁的力度太小了，时间主要花在了切换上下文上面了
//}



//atomic<size_t> x = 0;         // 对++,--进行原子操作
//
//void add(int n)
//{
//    for (int i = 0;i < n;++i)
//        ++x;
//}
//int main()
//{
//    thread t1(add,2000000000);
//    thread t2(add,2000000000);
//
//    t1.join();
//    t2.join();
//
//    cout << x;
//
//    return 0;
//}


/*
// 匿名对象
atomic<size_t> x = 0;         // 对++,--进行原子操作
struct Add
{
    void operator()(int n)
    {
        for (int i = 0;i < n;++i)
            ++x;
    }
};

int main()
{
    Add add;
    thread t1(add, 10000);
    thread t2(Add(), 10000);

    cout << t1.get_id() << endl;
    cout << t2.get_id() << endl;

    t1.join();
    t2.join();

    cout << x;
    return 0;
}
*/


/*
// lambda表达式
int main()
{

    atomic<size_t> x = 0;             // 对++,--进行原子操作

    auto add = [&x](size_t n) {
        for (int i = 0;i < n;++i)
            ++x;};

    thread t1(add, 10000);
    thread t2(add, 10000);

    cout << t1.get_id() << endl;
    cout << t2.get_id() << endl;

    t1.join();
    t2.join();

    cout << x;
    return 0;
}
*/


int main()
{

    atomic<size_t> x = 0;

    int m, n;
    cin >> m >> n;

    //vector<thread> vthreads;
    //for (int i = 0;i < m;++i)
    //{
    //    vthreads.push_back(
    //        // 创建进程
    //        thread([&x](int n) {
    //            for (int i = 0;i < n;++i)
    //                ++x;
    //            }, n)
    //    );

    //    cout << x << endl;
    //}

    vector<thread> vthreads(m);
    for (int i = 0;i < m;++i)
    {
        //// 创建进程
        //// =右边为匿名对象，移动赋值
        //vthreads[i]=thread([&x](int n) {
        //        for (int i = 0;i < n;++i)
        //            ++x;
        //        }, n);

        // 创建进程
        // t为左值
        thread t = thread([&x](int n) {
            for (int i = 0;i < n;++i)
                ++x;
            }, n);
        vthreads[i] = move(t);
        cout << x << endl;
    }

    for (auto& e : vthreads)
    {
        cout << e.get_id() << endl;

        e.join();
    }
    cout <<endl<<endl<< x<<endl;
    return 0;
}