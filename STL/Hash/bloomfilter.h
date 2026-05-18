#pragma once
#include <iostream>
#include "bitset.h"
using namespace BitSet;


namespace BloomFilter
{
    // BKDRHash
    struct HashStr1
    {
        size_t operator()(const std::string& str)
        {
            size_t hash = 0;
            for (auto& e : str)
            {
                hash = hash * 131 + e;
            }
            return hash;
          }
    };

    // RSHash
    struct HashStr2
    {
        size_t operator()(const std::string& str)
        {
            size_t hash = 0;
            size_t magic = 63689;
            for (auto& e : str)
            {
                hash = hash * magic + e;
                magic *= 378551;
            }
            return hash;
        }
    };

    // SDBMHash
    struct HashStr3
    {
        size_t operator()(const std::string& str)
        {
            size_t hash = 0;
            for (auto& e : str)
            {
                hash = hash * 65599 + e;
            }
            return hash;
        }
    };


    template <class K=std::string
        , class Hash1= HashStr1
        , class Hash2= HashStr2
        , class Hash3= HashStr3>

    // 布隆过滤器
    // 优点：节省空间+高效，可以标记任意数据类型
    // 缺点：存在误判+不支持删除
    // 不在是真的不在，在有可能误判
    class bloomfilter
    {
        public:

        // n为插入元素的个数
        bloomfilter(size_t n)
            :_bs(5 * n)
            ,_len(5 * n)
        {}

        void Set(const K& key)
        {
            size_t index1 = Hash1()(key) % _len;
            size_t index2 = Hash2()(key) % _len;
            size_t index3 = Hash3()(key) % _len;

            _bs.set(index1);
            _bs.set(index2);
            _bs.set(index3);
        }

        //void ReSet(const K& key)
        //{
        //    size_t index1 = Hash1()(key) % _len;
        //    size_t index2 = Hash2()(key) % _len;
        //    size_t index3 = Hash3()(key) % _len;

        //    _bs.reset(index1);
        //    _bs.reset(index2);
        //    _bs.reset(index3);
        // 不支持，删除，可能存在误删，一般，布隆过滤器不支持删除
        //}

        // 返回真也不一定是真的存在，但是返回假是一定不在
        // 先测试是否存在，如果存在返回真，如果不存在返回假
        // 所以用布隆过滤器，推荐的内容一定是不存在的
        bool Test(const K& key)
        {
            size_t index1 = Hash1()(key) % _len;
            if (_bs.test(index1) == false)
            {
                return false;
            }

            size_t index2 = Hash2()(key) % _len;
            if (_bs.test(index2) == false)
            {
                return false;
            }

            size_t index3 = Hash3()(key) % _len;
            if (_bs.test(index3) == false)
            {
                return false;
            }
            return true;
        }

    private:
        bitset _bs;           // 位图
        size_t _len;
    };

    void test_bloomfilter()
    {
        bloomfilter<std::string> bf(100);
        bf.Set("abcd");
        bf.Set("aadd");
        bf.Set("bcad");

        std::cout << bf.Test("abcd") << std::endl;
        std::cout << bf.Test("aadd") << std::endl;
        std::cout << bf.Test("bcad") << std::endl;
    }
};