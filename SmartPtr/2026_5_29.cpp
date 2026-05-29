#include <iostream>
#include <string>

#include "SmartPtr.h"

using namespace std;
using namespace MySmartPtr;



//int vivc()
//{
//    int m, n;
//    cin >> m >> n;
//    if (n == 0)
//    {
//        throw invalid_argument("除零错误");
//    }
//    return m / n;
//}
//
//void fcn()
//{            
//    //int* p = new int;
//    //SmartPtr<int> sp(new int);
//    //*sp = 100;
//
//    //SmartPtr<pair<int,string>> sp1(new pair<int,string>);
//    //sp1->first= 100;
//    //sp1->second = "fbenvmk";
//    //try
//    //{
//    //    vivc();
//    //}
//
//    //catch (...)
//    //{
//    //    delete p;
//    //    throw;
//    //}
//    //delete p;
//
//    /*    
//    SmartPtr<int> sp(new int);
//    SmartPtr<int> sp1 = sp;
//
//    // C++98 auto_ptr 管理权转移
//    // C++11 unique_ptr 防拷贝
//    // C++11 shared_ptr 引用计数的共享拷贝
//    // 循环引用的问题，又需要weak_ptr来解决 
//    */
//     
//    auto_ptr<int> sp(new int);  
//    auto_ptr<int> sp1 = sp;
//    cout << vivc() << endl;  
//}
//
//int main()
//{
//
//    try
//    {
//        fcn();
//    }
//    catch (exception& e)
//    {
//        cout << e.what();
//    }
//
//    return 0;
//
//}


int main()
{
    //test_unique_ptr();
    MySmartPtr::
    test_shared_ptr();
    return 0;
}