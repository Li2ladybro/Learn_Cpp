#include<iostream>
#include"AVLTree.h"

int main()
{
    int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };

    AVLTree<int, int> avl;
    for (auto& e : arr)
    {
        avl.Insert(std::make_pair(e, e));
    }

    std::cout << "ÖÐÐò±éÀúAVLÊ÷£º"<<std::endl;
    avl.InOrder();  
    std::cout << std::endl;
    std::cout << avl.IsBalance() << std::endl;
    return 0;
}
