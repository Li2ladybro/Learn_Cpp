#pragma once
#include <iostream>
#include <vector>

namespace MyHashTable
{

    template <class K>
    // 可以取到key的仿函数
    struct SetKeyOfT
    {
        const K& operator()(const K& key)
        {
            return key;
        }
    };

    // 关键字状态
    // 设置的意义：防止同义词截断查找路径
    enum State
    {
        EMPTY,       // 空
        EXIT,        // 存在
        DELETE       // 逻辑删除
    };

    template<class T>
    // 闭散列数据结构
    struct HashData
    {
        T _data;
        State _state;
    };

    // unordered_set<K>     ->ClosedHashing<K, K>
    // unordered_map<K,V>   ->ClosedHashing<K, Pair<K,V>>
    template<class K,class T,class KOfT>
    class ClosedHashing
    {
        typedef typename HashData<T> HashData;
    public:
        bool Insert(const T& d)
        {

            KOfT koft;

            // 负载因子 = 表中存放的数据个数/表的总体大小-》衡量哈希表满的程度
            // 表越满，插入数据，越容易冲突，效率越低
            // 因此哈希表并不是满了才增容，在开放定址法中，一般负载因子到0.7左右就要增容->以空间换时间的思路
            // 负载因子越小，冲突概率就越低，整体上效率越高，但是负载因子越小，带来的弊端就是浪费更多的空间
            // 所以负载因子需要取折中值
            if (_table.size() == 0 || _num * 10 / _table.size() >= 7)
            {
                // 增容
                // 增容会引起哈希函数发生变化
                // 1、开1.5、2倍的空间
                // 2、需要对旧的哈希表中的数据重新映射，映射到新表中
                // 3、释放旧空间

                //std::vector<HashData> newTable;
                //size_t newSize = _table.size() == 0 ? 10 : _table.size() * 2;
                //// 开一个新表2倍空间
                //newTable.resize(newSize);
                //for (size_t i = 0;i < _table.size();++i)
                //{
                //    if (_table[i]._state == EXIT)
                //    {
                //        // 对旧表中的已存在的数据重新映射，浪费了时间，映射到新表中，删除的数据不需要映射，空的数据也不需要映射
                //        size_t index = koft(_table[i]._data) % newTable.size();
                //        while (newTable[index]._state == EXIT)
                //        {
                //            // 发生冲突了，按照开放定址法继续往后找
                //            ++index;
                //            if (index == _table.size())
                //            {
                //                index = 0;
                //            }
                //         }
                //        // 将旧表中的数据放到新表中
                //        newTable[index] = _table[i];
                //    }
                //}
                //// 不用自己析构旧表，交换后将旧表的空间交给新表，新表是局部变量，离开作用域会自动析构
                //_table.swap(newTable);

                ClosedHashing<K,T, KOfT> newHT;
                size_t newSize = _table.size() == 0 ? 10 : _table.size() * 2;
                // 开一个新表2倍空间
                newHT._table.resize(newSize);
                for (size_t i = 0;i < _table.size();++i)
                {
                    newHT.Insert(_table[i]._data);
                }
                // 不用自己析构旧表，交换后将旧表的空间交给新表，新表是局部变量，离开作用域会自动析构
                _table.swap(newHT._table);
            }

            //// 线性探测
            //// 计算d在散列表中映射的位置
            //size_t index = koft(d) % _table.size();
            //while (_table[index]._state == EXIT)
            //{
            //    if (koft(_table[index]._data) == koft(d))
            //    {
            //        return false;
            //    }

            //    ++index;

            //    if (index == _table.size())
            //    {
            //        index = 0;
            //    }
            // }
            //_table[index]._data = d;
            //_table[index]._state = EXIT;
            //_num++;

            // 二次（平方）探测
            // 计算d在散列表中映射的位置
            size_t index = koft(d) % _table.size();
            size_t start = index;
            size_t i = 1;
            while (_table[index]._state == EXIT)
            {
                if (koft(_table[index]._data) == koft(d))
                {
                    return false;
                }

                index = start + i * i;
                ++i;
                index %= _table.size();
            }
            _table[index]._data = d;
            _table[index]._state = EXIT;
            _num++;
            return true;
        }

        HashData* Find(const K& key)
        {
            KOfT koft;
            size_t index = key % _table.size();
            while (_table[index]._state != EMPTY)
            {
                if (koft(_table[index]._data) == key)
                {
                    if (_table[index]._state == EXIT)
                    {
                        // 数据存在
                        return &_table[index];
                    }
                    else if (_table[index]._state == DELETE)
                    {
                        // 数据已经被删了
                        return nullptr;
                    }
                }

                ++index;

                if (index == _table.size())
                {
                    // 找到末尾没找到，重新从头开始找
                    index = 0;
                }
            }
            return nullptr;
        }

        bool Erase(const K& key)
        {
            HashData* ret = Find(key);
            if (ret)
            {
                ret->_state = DELETE;
                _num--;
                return true;
            }
            return false;
        }

    private:
        std::vector<HashData> _table;
        size_t    _num = 0;        // 存储了几个有效数据
    };


    template<class T>
    // 开散列数据结构
    struct HashNode
    {
        T _data;
        HashNode<T>* _next;
    };

    template<class K,class T,class KOfT>
    // 哈希桶
    class OpenHashing
    {
        typedef typename HashNode<T>* Node;
    public:
        bool Insert(const T& data)
        {
            KOfT koft;

            // 增容会引起哈希函数发生变化
            // 1、开1.5、2倍的空间
            // 2、需要对旧的哈希表中的数据重新映射，映射到新表中
            // 3、释放旧空间

            // 负载因子等于1，就增容，避免大量哈希冲突
            if (_table.size() == _num)
            {
                std::vector<Node*> newTable;
                // 不一定开2倍空间
                size_t newSize = _table.size() == 0 ? 10 : _table.size() * 2;
                newTable.resize(newSize);
                for (size_t i = 0;i < _table.size();++i)
                {
                    // 依次取出每一个桶
                    Node* cur = _table[i];
                    while (cur)
                    {
                        Node* next = cur->_next;
                        // 再对桶里的数据重新映射，进行头插法
                        size_t index = koft(cur->_data) % newTable.size();
                        cur->_next = newTable[index];
                        newTable[index] = cur;
                        cur = next;
                     }
                    _table[i] = nullptr;
                }
                _table.swap(newTable);
           }


            // 计算数据在表中的映射位置
            size_t index = koft(data) % _table.size();

            // 1、检查该数据是否在开散列中
            Node* cur = _table[index];
            while (cur)
            {
                if (koft(cur->_data) == koft(data)
                {
                    return false;
                }
                else
                {
                     cur=cur->_next;
                }
            }

            // 2、头插挂到同义词链表中（尾差也是可以的）
            Node* newNode = new Node(data);
            newNode->_next = _table[index];
            _table[index] = newNode;
            ++num;
            return true;
        }

    private:
        // 存的是结点的指针
        std::vector<Node*> _table;
        size_t _num=0;
    };


   

    void TestHashTable()
    {

        ClosedHashing<int, int, SetKeyOfT<int>> ht;
        ht.Insert(1);
        ht.Insert(2);
        ht.Insert(3);
        ht.Insert(4);
        ht.Insert(34);
        ht.Insert(6);
        ht.Insert(13);
        ht.Insert(2);
        ht.Insert(11);
        ht.Insert(25);
        ht.Insert(21);

        //HashData* ret = ht.Find(5);
        //if (ret)
        //{
        //    std::cout << ret->_data << std::endl;
        //}
    }

}