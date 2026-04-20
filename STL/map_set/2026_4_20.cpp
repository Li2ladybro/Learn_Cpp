#include <iostream>
#include <map>
#include <set>
#include <string>




int main()
{
    // 第一种计数方法
    //std::string arr[] = { "西瓜","蓝莓", "哈密瓜", "香蕉", "苹果", "西瓜", "西瓜", "西瓜" };
    //std::map<std::string, int> m;
    //for (auto& e : arr)
    //{
    //    std::map<std::string,int>::iterator it = m.find(e);
    //    if (it != m.end())
    //        it->second++;
    //    else
    //        m.insert(make_pair(e,1));
    //   // m[e]++;
    //}
    //for (auto& e : m)
    //    std::cout << e.first << ":" << e.second << std::endl;

    // 第二种计数方法
    //std::string arr[]= { "西瓜","蓝莓", "哈密瓜", "香蕉", "苹果", "西瓜", "西瓜", "西瓜"};
    //std::map<std::string, int> countMap;
    //for (auto& e : arr)
    //{
    //    std::pair<std::map<std::string,int>::iterator,bool> ret = countMap.insert(make_pair(e, 1));
    //    if (!ret.second)
    //        ret.first->second++;
    // }

    //for (auto& e : countMap)
    //    std::cout << e.first << ":" << e.second << std::endl;

    // 第三种计数方法
    //std::string arr[] = { "西瓜","蓝莓", "哈密瓜", "香蕉", "苹果", "西瓜", "西瓜", "西瓜" };
    //std::map<std::string, int> countMap;
    //for (auto& e : arr)
    //{
    //    // 1、如果水果不在map中，则operator[]会插入pair<str,0>，并返回映射对象（次数）的引用，再对它++
    //    // 2、如果水果在map中，则operator[]会返回映射对象（次数）的引用，再对它++
    //    countMap[e]++;
    //   /* (*
    //            (
    //                    (
    //                          this->insert(
    //                                        make_pair(k, mapped_type())
    //                                       )
    //                     ).first
    //             )
    //         ).*/
    //}
    //countMap["草莓"];         // 直接插入新的键（一般不会折磨用）
    //countMap["西瓜"] = 1;     // 修改对应的键的值
    //countMap["火龙果"] = 9;   // 插入+修改
    //for (auto& e : countMap)
    //    std::cout << e.first << ":" << e.second << std::endl;
    std::multiset<int> ms;
    ms.insert(1);
    ms.insert(2);
    ms.insert(3);
    ms.insert(4);
    ms.insert(5);
    ms.insert(6);
    ms.insert(6);
    ms.insert(6);
    ms.insert(7);
    for(auto& e:ms)
        std::cout<<e<<" "<<std::endl;

    
    std::cout << std::endl;

    auto pos = ms.find(6);
    std::cout << *pos << std::endl;
    ++pos;
    std::cout << *pos << std::endl;
    ++pos; 
    std::cout << *pos << std::endl;
    ++pos;
    std::cout << *pos << std::endl;
    ++pos;
    std::cout << *pos << std::endl;

    std::cout << std::endl;

    std::set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    s.insert(6);
    s.insert(6);
    s.insert(7);
    for (auto& e : s)
        std::cout << e << " " << std::endl;

    return 0;
}