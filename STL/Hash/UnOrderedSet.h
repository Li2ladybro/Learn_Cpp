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

    std::make_pair(iterator, bool) Insert(const K& k)
    {
        return _ohs.Insert(k);
    }
private:
    OpenHashing<K, K, SetKOfT, Hash> _ohs;
};

void TestUnOrderedSet()
{
    UnOrderedSet<int> s;
    s.Insert(1);
    s.Insert(3);
    s.Insert(5);
    s.Insert(6);
    s.Insert(9);

    UnOrderedSet<int>::iterator it = s.begin();
    while (it != s.end())
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}