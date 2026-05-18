#pragma once
#include <vector>

namespace BitSet
{
    // 节省空间+高效
    // 缺点：只能处理整形
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
            size_t index = x / 32;           // 计算出映射的位置在第几个整形
            size_t pos = x % 32;             // 计算出x在整形的第几位

            _bits[index] |= (1 << pos);      // 将第x位置1
            ++_num;
        }

        void reset(size_t x)
        {
            size_t index = x / 32;           // 计算出映射的位置在第几个整形
            size_t pos = x % 32;             // 计算出x在整形的第几位

            _bits[index] &= ~(1 << pos);     // 将第x位置0
            --_num;
        }

        // 判断x在不在
        bool test(size_t x)
        {
            return _bits[x / 32] & (1 << x % 32);
        }

    private:
        std::vector<int> _bits;
        size_t _num;                         // 映射存储了多少数据
    };

    void TestBitSet()
    {
        //bitset bs(100);
        //bs.set(5);

        //bs.set(99);
        //bs.set(98);
        //bs.set(97);
        //bs.set(95);
        //bs.reset(99);

        //for (size_t i = 0;i < 100;++i)
        //{
        //    printf("[%2d]：%d\n", i, bs.test(i));
        //}
        //bitset bs(-1);    // 42亿9千万
        bitset bs(0xffffffff);
    }


    class solution1
    {
    public:
        void set(size_t x)
        {
            if (_bt1.test(x) == false && _bt2.test(x) == false)   // 00
            {
                // 01
                _bt1.reset(x);
                _bt2.set(x);
            }

            if (_bt1.test(x) == false && _bt2.test(x) == true)   // 01
            {
                // 11
                _bt1.set(x);
                _bt2.set(x);
            }
        }

    private:
        bitset _bt1;
        bitset _bt2;
    };
}

