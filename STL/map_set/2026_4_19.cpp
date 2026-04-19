#include<iostream>
#include<map>
#include<set>

using namespace std;

int main()
{
    set<int> st;
    st.insert(1);
    st.insert(2);
    st.insert(3);
    st.insert(4);
    st.insert(5);
    st.insert(6); 
    st.insert(7);
    st.insert(8);
    st.erase(50);
   
    cout << st.erase(70)<< endl;
    for (auto& e : st)
    {
        cout << e << " ";
    }
    cout << endl;
    map<int, int> m;
    m.insert(pair<int, int>(1, 1));
    m.insert(pair<int, int>(2, 2));
    m.insert(pair<int, int>(3, 3));      // pair构造函数，构造出一个匿名对象
    m.insert(make_pair(3, 3));           // 函数模板，构造出一个匿名对象

    map<int, int>::iterator it = m.begin();
    while (it != m.end())
    {
        cout << (*it).first << ":" << (*it).second << endl;
        cout << it->first << ":" << it->second << endl;
        ++it;

    }
    return 0;
}