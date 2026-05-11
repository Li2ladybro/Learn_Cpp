#pragma once
#include "HashTable.h"

using namespace MyHashTable;


template<class K, class Hash = _Hash<K>>
class UnOrderedSet
{
    // 可以取到key的仿函数
    struct SetKOfT
    {
        const K& operator()(const K& key)
        {
            return key;
        }
    };

public:
    typedef typename OpenHashing<K, K, SetKOfT, Hash>::iterator iterator;

    iterator begin()
    {
        return _ohs.begin();
    }

    iterator end()
    {
        return _ohs.end();
    }

    std::pair<iterator, bool> Insert(const K& k)
    {
        return _ohs.Insert(k);
    }

private:
    OpenHashing<K, K, SetKOfT, Hash> _ohs;
};

void TestUnOrderedSet()
{
    UnOrderedSet<int> us;
    //us.Insert(1);
    //us.Insert(10);
    //us.Insert(5);
    //us.Insert(6);
    //us.Insert(4);

    us.Insert(1);
    us.Insert(5);
    us.Insert(4);
    us.Insert(2);

    UnOrderedSet<int>::iterator it = us.begin();
    while (it != us.end())
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}