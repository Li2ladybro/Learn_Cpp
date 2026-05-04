#pragma once
#include "RBTree.h"
#include <string>

namespace MyMap
{
    template <class K,class V>
    class map
    {
        struct MapKeyOfT
        {
            const K& operator()(const std::pair<K,V>& kv)
            {
                // 仿函数取到K
                return kv.first;
            }
        };

    public:
        typedef typename RBTree <K, std::pair<K,V>, MapKeyOfT>::iterator iterator;

        iterator begin()
        {
            return _t.begin();
        }

        iterator end()
        {
            return _t.end();
        }

        std::pair<iterator,bool> Insert(const std::pair<K,V>& kv)
        {
            return _t.Insert(kv);
        }


        V& operator[](const K& key)
        {
            // 1、如果插入的元素不在map中，则operator[]会插入pair<str,0>，其中0为默认构造函数生成的值，并返回映射对象的second；
            // 2、如果需要插入的元素已经在map中，调用operator[]依然会执行插入操作，此时必定会插入失败，但依然会返回映射对象的second；
            std::pair<iterator, bool> ret= _t.Insert(
                                                         std::make_pair(
                                                                         key,
                                                                         V()
                                                                        )
                                                     );
            // ret.first：为迭代器
            // 迭代器再运算符重载->取到T
            // 因为是map此时T为Pair
            return ret.first->second;
        }

    private:
        RBTree<K, std::pair<K,V>, MapKeyOfT> _t;
    };

    void test_map()
    {
        //map<int, int> m;
        //m.Insert(std::make_pair(1, 1));
        //m.Insert(std::make_pair(3, 3));
        //m.Insert(std::make_pair(4, 3));
        //m.Insert(std::make_pair(5, 6));
        //m.Insert(std::make_pair(7, 3));
        //map<int, int>::iterator it = m.begin();
        //while (it != m.end())
        //{
        //    std::cout << it->first << ":" << it->second << std::endl;
        //    ++it;
        //}

        //for (auto kv : m)
        //{
        //    std::cout << kv.first << ":" << kv.second << std::endl;
        //}

        //std::cout << std::endl;

        std::string arr[] = { "西瓜","蓝莓", "哈密瓜", "香蕉", "苹果", "西瓜", "西瓜", "西瓜" };
        map<std::string, int> countMap;
        for (auto& str : arr)
        {
            countMap[str]++;
        }

        for (auto& kv : countMap)
        {
            std::cout << kv.first << ":" << kv.second << std::endl;
        }
    }
}