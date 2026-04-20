//#include<iostream>
//#include<map>
//#include<set>
//
//using namespace std;
//
//int main()
//{
//    //set<int> st;
//    //st.insert(1);
//    //st.insert(2);
//    //st.insert(3);
//    //st.insert(4);
//    //st.insert(5);
//    //st.insert(6); 
//    //st.insert(7);
//    //st.insert(8);
//    //st.erase(50);
//   
//    //cout << st.erase(70)<< endl;
//    //for (auto& e : st)
//    //{
//    //    cout << e << " ";
//    //}
//    //cout << endl;
//    //map<int, int> m;
//    //m.insert(pair<int, int>(1, 1));
//    //m.insert(pair<int, int>(2, 2));
//    //m.insert(pair<int, int>(3, 3));      // pairæ„é€ å‡½æ•°ï¼Œæ„é€ å‡ºä¸€ä¸ªåŒ¿åå¯¹è±?
//    //m.insert(make_pair(3, 3));           // å‡½æ•°æ¨¡æ¿ï¼Œæ„é€ å‡ºä¸€ä¸ªåŒ¿åå¯¹è±?
//
//    //map<int, int>::iterator it = m.begin();
//    //while (it != m.end())
//    //{
//    //    cout << (*it).first << ":" << (*it).second << endl;
//    //    cout << it->first << ":" << it->second << endl;
//    //    ++it;
//
//    //}
//
//    std::string arr[] = { "Î÷¹Ï","À¶İ®", "¹şÃÜ¹Ï", "Ïã½¶", "Æ»¹û", "Î÷¹Ï", "Î÷¹Ï", "Î÷¹Ï", };
//    std::map<std::string, int> m;
//    for (auto& e : arr)
//    {
//        //std::map<std::string,int>::iterator it = m.find(e);
//        //if (it != m.end())
//        //    it->second++;
//        //else
//        //    m.insert(make_pair(e,1));
//        m[e]++;
//    }
//    for (auto& e : m)
//        std::cout << e.first << ":" << e.second<<endl;
//    return 0;
//}