#pragma once
#include <vector>

// 关键字状态
// 设置的意义：防止同义词截断查找路径
enum State
{
    EMPTY,       // 空
    EXIT,        // 存在
    DELETE       // 逻辑删除
};

template<class T>
struct HashData
{
    typedef enum State State;
    T _data;
    State _state;
};

// unordered_set<K>     ->HashTable<K, K>
// unordered_map<K,V>   ->HashTable<K, Pair<K,V>>
template<class K,class T,class KOfT>
class HashTable
{
public:
    bool Insert(const T& d)
    {
        // 负载因子 = 表中存放的数据个数/表的总体大小-》衡量哈希表满的程度
        // 表越满，插入数据，越容易冲突，效率越低
        // 因此哈希表并不是满了才增容，在开放定址法中，一般负载因子到0.7左右就要增容->以空间换时间的思路
        // 负载因子越小，冲突概率就越低，整体上效率越高，但是负载因子越小，带来的弊端就是浪费更多的空间
        // 所以负载因子需要取折中值
        if (_num * 10/ _table.size() >= 7)
        {
            // 增容
            // 增容会引起哈希函数发生变化
            // 1、开1.5、2倍的空间
            // 2、需要对旧的哈希表中的数据重新映射，映射到新表中
            // 3、释放旧空间

            vector<HashData> newTable;
            newTable.resize(_table.size() * 2);
            for (size_t i = 0;i < _table.size();++i)
            {
                if (_table[i]._state == EXIT)
                {
                    size_t index = koft(_table[index]._data) % newTable.size();
                    while (newTable[index]._state == EXIT)
                    {
                        ++index;
                        if (index == _table.size())
                        {
                            index = 0;
                        }
                     }
                    newTable[index] = _table[i];
                }
            }
        }

        KOfT koft;
        // 计算d在散列表中映射的位置
        size_t index = koft(d) % _table.size();
        while (_table[index]._state == EXIT)
        {
            if (koft(_table[index]._data) == koft(d))
            {
                return false;
            }

            ++index;

            if (index == _table.size())
            {
                index = 0;
            }
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
        while (_table[index]._state != EMPRY)
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
                // 找到末尾没找到
                index = 0;
            }
        }
        return nullptr;
    }

    bool Erase(const K& key)
    {
        HashData* ret=Find(key)
        if(ret)
        {
            ret->_sate = DELETE;
            _num--；
            return true;
        }
        return false;
    }

private:
    vector<T> _table;
    size_t    _num=0;        // 存储了几个有效数据
};