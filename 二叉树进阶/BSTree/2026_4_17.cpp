#include "BSTree.hpp"


int main()
{
    //int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
    //BSTree<int> bst1;
    //for (auto& e : a)
    //{
    //    bst1.Insert(e);
    //}
    //bst1.InOrder();
    ////int r= bst1.Erase(1);
    //for (auto& e : a)
    //{
    //    int r= bst1.Erase(e);   
    //   // cout << r<<endl;
    //    bst1.InOrder();

    //   
    //}
    ////bst1.InOrder();
    //BSTree<string, string> dict;
    //dict.Insert("sort","ÅÅÐò");
    //dict.Insert("friend", "ÅóÓÑ");
    //dict.Insert("family", "¼ÒÍ¥");
    //dict.Insert("binary", "¶þ²æ");

    //string str;
    //while (cin>> str)
    //{
    //    BSTreeNode<string, string>* res = dict.Find(str);
    //    if (res)
    //        cout << res->_value << endl;
    //    else
    //        cout << "²éÎÞµ¥´Ê" << endl;
    //}

    BSTree<string,int> countFruit;
    string arr[] = { "Î÷¹Ï","Ïã½¶", "Æ»¹û", "¹þÃÜ¹Ï", "Ë®ÃÛÌÒ", "â¨ºïÌÒ", "Î÷¹Ï", "Î÷¹Ï", "Î÷¹Ï", };
    for (auto& e : arr)
    {
       auto res = countFruit.Find(e);
       if (res)
          res->_value++;
       else
           countFruit.Insert(e, 1);
    }

    countFruit.InOrder();
    return  0;           
}