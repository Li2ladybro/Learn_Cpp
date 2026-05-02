//#include "RBTree.h"
//#include "AVLTree.h"
//#include <vector>
//#include <time.h>

//int main()
//{
//    const int cp = 10000000;
//    std::vector<int> arr;
//    arr.reserve(cp);
//
//    // 植入种子
//    srand(time(0));
//    for (size_t i = 0;i < cp;++i)
//    {
//        arr.push_back(rand());
//    }
//
//
//    AVLTree<int, int> avlt;
//    RBTree<int, int> rbt;
//
//    size_t begin1 = clock();
//
//    int avltf = 0;
//    int _avltf = 0;
//    for (auto& e : arr)
//    {
//        if (avlt.Insert(std::make_pair(e, e)) == true)
//        {
//            avltf += 1;
//        }
//        else
//        {
//            _avltf += 1;
//            //std::cout<<avlt.Find(std::make_pair(e, e))->_kv.first<<":";
//
//            //std::cout << e << ' ';
//        }
//    }
//    //avlt.InOrder();
//    std::cout << "AVLTree" << "_" << cp << "个随机节点插入成功数量" << avltf;
//    std::cout << "；插入失败节点：" << _avltf << std::endl;
//    size_t end1 = clock();
//
//    std::cout << "AVLTree_" << "总耗时:" << end1 - begin1<<"       平衡二叉树高度:"<<avlt.Height()<< std::endl;
//
//    size_t begin2 = clock();
//    int rbtf = 0;
//    int _rbtf = 0;
//    for (auto& e : arr)
//    {
//        if (rbt.Insert(std::make_pair(e, e)) == true)
//        {
//            rbtf += 1;
//        }
//        else
//        {
//            _rbtf += 1;
//           /* std::cout << rbt.Find(std::make_pair(e, e))->_kv.first << ":";
//
//            std::cout << e << ' ';*/
//        }
//    }
//
//    //rbt.InOrder();
//    std::cout << "RBTRee" << "_" << cp << "个随机节点_插入成功数量" << rbtf;
//    std::cout << "；插入失败节点：" << _rbtf << std::endl;
//    size_t end2 = clock();
//
//    std::cout << "RBTRee_" << "总耗时:" << end2 - begin2 <<"       红黑树高度:"<<rbt.Height()<< std::endl;
//    return 0;
//}


#include "MyMap.h"
#include "MySet.h"


int main()
{
    MyMap::test_map();
    MySet::test_set();
    return 0;
}