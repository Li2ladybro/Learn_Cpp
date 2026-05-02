#pragma once
#include "RBTree.h"

namespace MyMap
{
    template <class K,class V>
    class map
    {
        struct MapKeyOfT
        {
            const K& operator()(const std::pair<K,V>& kv)
            {
                return kv.first;
            }
        };
    public:
        typedef typename RBTree < K, V, MapKeyOfT>::iterator iterator;

        bool Insert(const std::pair<K,V>& kv)
        {
            return _t.Insert(kv);
        }

    private:
        RBTree<K, std::pair<K,V>, MapKeyOfT> _t;
    };

    void test_map()
    {
        map<int, int> m;
        m.Insert(std::make_pair(1, 1));
        m.Insert(std::make_pair(3, 3));
    }
}