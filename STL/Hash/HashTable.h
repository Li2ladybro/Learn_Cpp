#pragma once
#include <iostream>
#include <vector>
#include <string>


namespace MyHashTable
{

    template <class K>
    // 哈希仿函数，可以取到key的仿函数
    struct _Hash
    {
        // 默认的可以直接取模的关键字(int)
        const K& operator()(const K& key)
        {
            return key;
        }
    };

    // string的特化(BKDR哈希算法)
    template <>
    // 哈希仿函数，可以取到key的仿函数
    struct _Hash<std::string>
    {
        // 显示不能直接取模的用这个仿函数，主要针对字符串
        // 这里如果选用第一个字符进行映射冲突的更厉害
        size_t operator()(const std::string& key)
        {
            size_t hash = 0;
            for (auto& e : key)
            {
                hash = hash * 131 + e;
            }
            return hash;
        }
    };

    //// 可以取到key的仿函数
    //struct _HashString
    //{
    //    // 显示不能直接取模的用这个仿函数，主要针对字符串
    //    // 这里如果选用第一个字符进行映射冲突的更厉害
    //    size_t operator()(const std::string& key)
    //    {
    //        size_t hash = 0;
    //        for (auto& e : key)
    //        {
    //            hash *= 131;
    //            hash += e;
    //        }
    //        return hash;
    //    }
    //};

    // 闭散列关键字状态
    // 设置的意义：防止同义词截断查找路径
    enum State
    {
        EMPTY,       // 空
        EXIST,       // 存在
        DELETE       // 逻辑删除
    };

    template<class T>
    // 闭散列数据结构
    struct HashData
    {
        T _data;
        State _state;
    };

    /* ==================== 闭散列（开放定址法） ==================== */
    // unordered_set<K>     ->ClosedHashing<K, K>
    // unordered_map<K,V>   ->ClosedHashing<K, Pair<K,V>>
    template<class K, class T, class KOfT>
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
                //    if (_table[i]._state == EXIST)
                //    {
                //        // 对旧表中的已存在的数据重新映射，浪费了时间，映射到新表中，删除的数据不需要映射，空的数据也不需要映射
                //        size_t index = koft(_table[i]._data) % newTable.size();
                //        while (newTable[index]._state == EXIST)
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

                ClosedHashing<K, T, KOfT> newHT;
                size_t newSize = _table.size() == 0 ? 10 : _table.size() * 2;
                // 开一个新表2倍空间
                newHT._table.resize(newSize);
                for (size_t i = 0;i < _table.size();++i)
                {
                    if (_table[i]._state == EXIST)
                    {
                        newHT.Insert(_table[i]._data);
                    }
                }
                // 不用自己析构旧表，交换后将旧表的空间交给新表，新表是局部变量，离开作用域会自动析构
                _table.swap(newHT._table);
            }

            //// 线性探测
            //// 计算d在散列表中映射的位置
            //size_t index = koft(d) % _table.size();
            //while (_table[index]._state == EXIST)
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
            //_table[index]._state = EXIST;
            //_num++;

            // 二次（平方）探测
            // 计算d在散列表中映射的位置
            size_t index = koft(d) % _table.size();
            size_t start = index;
            size_t i = 1;
            while (_table[index]._state == EXIST)
            {
                // 如果发生哈希冲突
                if (koft(_table[index]._data) == koft(d))
                {
                    return false;
                }
                index = (start + i * i) % _table.size();
                ++i;
            }
            _table[index]._data = d;
            _table[index]._state = EXIST;
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
                    if (_table[index]._state == EXIST)
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


    /* ==================== 开散列（哈希桶） ==================== */
    template<class T>
    // 开散列数据结构
    struct HashNode
    {
        HashNode(const T& data)
            :_data(data)
            , _next(nullptr)
        {}

        T _data;
        HashNode<T>* _next;           // 用来挂桶的
        // HashNode<T>* _linknext;    // 保证可以按插入的顺序依次访问，迭代器相对更容易实现
        // HashNode<T>* _linkprev;    // 可以用来删除结点
    };

    // 相当于是一个前置声明
    template<class K, class T, class KOfT, class Hash>
    // 哈希桶
    class OpenHashing;

    /* ==================== 开散列迭代器 ==================== */
    // 此迭代器会用到后面的哈希桶
    template<class K, class T, class KOfT, class Hash>
    struct __OpenHashingIterator
    {
        // 哈希表迭代器是正向迭代器，不能往回走
        typedef typename __OpenHashingIterator<K, T, KOfT, Hash> Self;
        typedef typename OpenHashing <K, T, KOfT, Hash> OH;
        typedef typename HashNode<T> Node;

        __OpenHashingIterator(Node* node, OH* oh)
            :_node(node)
            ,__oh(oh)
        {}

        T& operator *()
        {
            return _node->_data;
        }

        T* operator ->()
        {
            return &_node->_data;
        }

        Self& operator ++()
        {
            if (_node->_next)
            {
                _node = _node->_next;
            }
            else
            {
                // 如果一个桶走完了，找下一个桶
                KOfT koft;
                size_t index = __oh->HashFunc(koft(_node->_data)) % __oh->_table.size();
                ++index;
                for (;index < __oh->_table.size();++index)
                {
                    if (__oh->_table[index])
                    {
                        _node = __oh->_table[index];
                        return *this;
                    }
                }
                // 后面没桶了
                _node = nullptr;
                return *this;
            }
        }

        bool operator !=(const Self& s) const
        {
            return _node != s._node;
        }

        bool operator ==(const Self& s) const
        {
            return s._node == _node;
        }

        Node* _node;
        OH* __oh;
    };

    template<class K,class T,class KOfT,class Hash>
    // 哈希桶
    class OpenHashing
    {
        typedef typename HashNode<T> Node;

    public:
        // 添加友元让迭代器可以访问哈希类中的私有成员
        template<class, class, class, class>
        friend struct __OpenHashingIterator;
        typedef typename __OpenHashingIterator<K, T, KOfT,Hash> iterator;

        iterator begin()
        {
            for (auto& e: _table)
            {
                if (e)
                {
                    return iterator(e,this);
                }
            }
            return end();
        }

        iterator end()
        {
            return iterator(nullptr, this);
        }

        // 析构
        ~OpenHashing()
        {
            // 自定义类型自己会析构
            Clear();
        }

        void Clear()
        {
            // 彻底清空哈希表
            // 清空每个桶
            for (size_t i = 0;i < _table.size();++i)
            {
                Node* cur = _table[i];
                while (cur)
                {
                    Node* next = cur->_next;
                    delete cur;
                    cur = next;
                }
                _table[i] = nullptr;
            }
            _num = 0;
        }

        // 计算关键字映射的整形
        size_t HashFunc(const K& key)
        {
            // 本质是调用外部的仿函数，关键字类型不同仿函数不同
            Hash hash;
            return hash(key);
        }

        // 获取素数
        size_t GetNextPrime(size_t num)
        {
            const int PRIMECOUNT = 28;
            // ul表示无符号长整型，选用素数的空间，经统计选素数冲突的概率小
            const static size_t primeList[PRIMECOUNT] = { 53ul, 97ul, 193ul, 389ul, 769ul, 1543ul, 3079ul, 6151ul, 12289ul, 24593ul, 49157ul, 98317ul, 196613ul, 393241ul, 786433ul, 1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul, 50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul, 1610612741ul, 3221225473ul, 4294967291ul };

            for (auto& e : primeList)
            {
                if (e > num)
                {
                    return e;
                }
            }
            return primeList[PRIMECOUNT-1];
        }

        // 插入
        std::pair<iterator,bool> Insert(const T& data)
        {
            KOfT koft;

            // 增容会引起哈希函数发生变化
            // 1、开1.5、2倍的空间
            // 2、需要对旧的哈希表中的数据重新映射，映射到新表中
            // 3、释放旧空间

            // 负载因子等于1，就增容，避免大量哈希冲突
            // 等于一理想上来看，就是平均每个每个位置挂一个值，所以查找的时间为O(1)
            if (_table.size() == _num)
            {
                // 不一定开2倍空间
                // size_t newSize = _table.empty() ? 10 : _table.size() * 2;

                // 获取素数的空间，经统计选素数冲突的概率小
                size_t newSize = GetNextPrime(_table.size());
                std::vector<Node*> newTable;
                newTable.resize(newSize);

                // 旧结点重新映射到新表中
                for (size_t i = 0;i < _table.size();++i)
                {
                    // 依次取出每一个桶
                    Node* cur = _table[i];
                    while (cur)
                    {
                        Node* next = cur->_next;
                        // 再对桶里的数据重新映射，进行头插法
                        // size_t index = HashFunc(koft(cur->_data)) % newTable.size();
                        size_t index = HashFunc(koft(cur->_data)) % newSize;
                        cur->_next = newTable[index];
                        newTable[index] = cur;
                        cur = next;
                     }
                    _table[i] = nullptr;
                }
                _table.swap(newTable);
           }

            // 计算数据在表中的映射位置
            size_t index = HashFunc(koft(data)) % _table.size();

            // 1、检查该数据是否在开散列中
            Node* cur = _table[index];
            while (cur)
            {
                if (koft(cur->_data) == koft(data))
                {
                    return std::make_pair(iterator(cur,this),false);
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
            ++_num;
            return std::make_pair(iterator(newNode, this), true);;
        }

        // 查找
        Node* Find(const K& key)
        {
            if (_table.empty())
            {
                return nullptr;
            }
            KOfT koft;
            size_t index = HashFunc(key) % _table.size();
            Node* cur = _table[index];
            // 遍历桶
            while (cur)
            {
                if (koft(cur->_data) == key)
                {
                    return cur;
                }
                cur = cur->_next;
            }
            return cur;
        }

        // 删除
        bool Erase(const K& key)
        {
            if (_table.empty())
            {
                return false;
            }
            KOfT koft;
            size_t index = HashFunc(key) % _table.size();
            Node* pre = nullptr;
            Node* cur = _table[index];
            // 遍历桶
            while (cur)
            {
                if (koft(cur->_data) == key)
                {
                    // 执行删除操作
                    if (pre == nullptr)
                    {
                        // 表示删除的节点在第一个
                        _table[index] = cur->_next;
                    }
                    else
                    {
                        pre->_next = cur->_next;
                    }
                    delete cur;
                    --_num;
                    return true;
                }
                pre = cur;
                cur = cur->_next;
            }
            // 没找到删除失败
            return false;
        }
    private:
        // 存的是结点的指针
        std::vector<Node*> _table;
        size_t _num=0;
    };

    //void TestClosedHashing()
    //{
    //    ClosedHashing<int, int, SetKeyOfT<int>> ch;
    //    ch.Insert(1);
    //    ch.Insert(2);
    //    ch.Insert(3);
    //    ch.Insert(4);
    //    ch.Insert(34);
    //    ch.Insert(6);
    //    ch.Insert(13);
    //    ch.Insert(2);
    //    ch.Insert(11);
    //    ch.Insert(25);
    //    ch.Insert(21);
    //    ch.Insert(51);
    //    ch.Insert(65);
    //    ch.Insert(451);
    //    HashData* ret = ht.Find(5);
    //    if (ret)
    //    {
    //        std::cout << ret->_data << std::endl;
    //    }
    //}

    //void TestOpenHashing()
    //{
    //    OpenHashing<int, int, SetKeyOfT<int>> oh;
    //    oh.Insert(1);
    //    oh.Insert(2);
    //    oh.Insert(3);
    //    oh.Insert(4);
    //    oh.Insert(34);
    //    oh.Insert(6);
    //    oh.Insert(13);
    //    oh.Insert(2);
    //    oh.Insert(11);
    //    oh.Insert(25);
    //    oh.Insert(21);
    //    oh.Insert(2);
    //    oh.Insert(11);
    //    oh.Insert(25);
    //    oh.Insert(21);
    //    oh.Insert(51);
    //    oh.Insert(65);
    //    oh.Insert(451);
    //    oh.Erase(51);
    //    oh.Erase(451);
    //}

    //void TestOpenHashing1()
    //{
    //    OpenHashing<std::string, std::string, SetKeyOfT<std::string>> oh;
    //    oh.Insert("linux");
    //    oh.Insert("sort");
    //}

}