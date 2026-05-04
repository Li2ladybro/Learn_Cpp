#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <string>
using namespace std;

void test_unordered_set();
void test_set();
void test_unordered_map();
void test_map();
void unordered_set_VS_set();


int main()
{
    //test_unordered_set();
    //test_set();
    //test_unordered_map();
    //test_map();
    for (int i = 0;i < 10;++i)
    {
        unordered_set_VS_set();
    }
    return 0;
}

void test_unordered_set()
{
    // unordered_set£ºÂÒĞò+È¥ÖØ
    unordered_set<int> us;
    us.insert(1);
    us.insert(4);
    us.insert(5);
    us.insert(3);
    us.insert(2);
    us.insert(9);
    us.insert(2);

    unordered_set<int>::iterator itus = us.begin();
    while (itus != us.end())
    {
        // unordered_setÃ»·¨ĞŞ¸Ä
        // *itus = 4;
        cout << *itus << ' ';
        ++itus;
    }
    cout << endl;

}

void test_set()
{
    // set£ºÅÅĞò+È¥ÖØ
    set<int> s;
    s.insert(1);
    s.insert(4);
    s.insert(5);
    s.insert(3);
    s.insert(2);
    s.insert(9);
    s.insert(2);

    set<int>::iterator its = s.begin();
    while (its != s.end())
    {
        cout << *its << ' ';
        ++its;
    }
    cout << endl;
}

void test_unordered_map()
{
    // unordered_map£ºÂÒĞò+È¥ÖØ
    unordered_map<string, string> um;
    um.insert(make_pair("sort", "ÅÅĞò"));
    um.insert(make_pair("left", "×ó±ß"));
    um.insert(make_pair("right", "ÓÒ±ß"));
    um.insert(make_pair("apple", "Æ»¹û"));
    um.insert(make_pair("orange", "³È×Ó"));
    um.insert(make_pair("fallow", "¸úËæ"));
    um.insert(make_pair("fallow", "¸úËæ"));
    um.insert(make_pair("satisfy", "ÂúÒâ"));
    um["read"] = "ÔÄ¶Á";

    unordered_map<string, string>::iterator itum = um.begin();
    while (itum != um.end())
    {
        // unordered_mapÃ»·¨ĞŞ¸Ä
        // *itup = 4;
        cout << itum->first << "£º" << itum->second << endl;
        ++itum;
    }
    cout << endl;
}

void test_map()
{
    // map£ºÅÅĞò+È¥ÖØ
    map<string, string> m;
    m.insert(make_pair("sort", "ÅÅĞò"));
    m.insert(make_pair("left", "×ó±ß"));
    m.insert(make_pair("right", "ÓÒ±ß"));
    m.insert(make_pair("apple", "Æ»¹û"));
    m.insert(make_pair("orange", "³È×Ó"));
    m.insert(make_pair("fallow", "¸úËæ"));
    m.insert(make_pair("fallow", "¸úËæ"));
    m.insert(make_pair("satisfy", "ÂúÒâ"));
    m["read"] = "ÔÄ¶Á";

    map<string, string>::iterator itm = m.begin();
    while (itm != m.end())
    {
        // mapÃ»·¨ĞŞ¸Ä
        // *itm = 4;
        cout << itm->first << "£º" << itm->second << endl;
        ++itm;
    }
    cout << endl;
}

void unordered_set_VS_set()
{
    unordered_set<int> us;
    set<int> s;

    const size_t n = 10000;
    vector<int> vec;
    vec.reserve(n);

    srand(time(0));
    for (size_t i = 0;i < n;++i)
    {
        vec.push_back(rand());
    }

    size_t begin1 = clock();
    for (auto& e:vec)
    {
        us.insert(e);
    }
    size_t end1 = clock();
    cout << "unordered_set£º" << end1 - begin1 << endl;

    size_t begin2 = clock();
    for (auto& e : vec)
    {
        s.insert(e);
    }
    size_t end2 = clock();
    cout << "set£º" << end2 - begin2 << endl;
}