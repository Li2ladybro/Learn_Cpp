#pragma once
#include "HashTable.h"

using namespace MyHashTable;


template<class K,class V, class Hash= _Hash<K>>
class UnOrderedMap
{
    struct MapKOfT
    {
        const K& operator()(const std::pair<K, V>& kv)
        {
            return kv.first;
        }
    };

public:
    typedef typename OpenHashing<K, std::pair<K,V>, MapKOfT, Hash>::iterator iterator;

    iterator begin()
    {
        return _ohm.begin();
    }

    iterator end()
    {
        return _ohm.end();
    }

    std::make_pair(iterator, bool) Insert(const std::pair<K, V>& kv)
    {
        return _ohm.Insert(kv);
    }

private:
    OpenHashing<K, std::pair<K, V>, MapKOfT, Hash> _ohm;
};

void TestUnOrderedMap()
{
    UnOrderedMap<std::string,std::string> um;
    um.Insert(std::make_pair("sort","ÅÅĞò"));
    um.Insert(std::make_pair("left", "×ó±ß"));
    um.Insert(std::make_pair("right", "ÓÒ±ß"));
    um.Insert(std::make_pair("fruit", "Ë®¹û"));

    UnOrderedMap<std::string, std::string>::iterator it = um.begin();
    while (it != um.end())
    {
        std::cout << it->first << "£º"<<it->second;
        ++it;
    }
    std::cout << std::endl;
}