#pragma once
//#include <iostream>
#include <vector>

namespace BitSet
{

    class bitset
    {
    public:
        // N：需要几个位
        bitset(size_t N)
        {
            _bits.resize(N/32+1, 0);
            _num = 0;
        }

        void set(size_t x)
        {
            size_t index = x / 32;      // 计算出映射的位置在第几个整形
            size_t pos = x % 32;        // 计算出x在整形的第几位

            _bits[index] |= (1 << pos); // 将第x位置1
        }

        void reset(size_t x)
        {
            size_t index = x / 32;      // 计算出映射的位置在第几个整形
            size_t pos = x % 32;        // 计算出x在整形的第几位

            _bits[index] &= ~(1 << pos); // 将第x位置0
        }

    private:
        std::vector<int> _bits;
        size_t _num;            // 映射存储了多少数据
    };
}