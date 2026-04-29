#include "RBtree.h"

int main()
{
    int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15};

    RBTree<int, int> rb;
    for (auto& e : arr)
    {
        bool flag = rb.Insert(std::make_pair(e, e));
        std::cout << flag<< std::endl;
    }


    std::cout << "ÖÐÐò±éÀúºìºÚÊ÷£º" << std::endl;
    rb.InOrder();
    std::cout<<rb.IsValidRBTree() << std::endl;

    return 0;
}

