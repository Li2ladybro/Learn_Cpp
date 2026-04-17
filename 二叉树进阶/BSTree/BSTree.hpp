#pragma once

#include <iostream>
using namespace std;

//template <class K>
//struct BSTreeNode // Binary Search Tree
//{
//    BSTreeNode(const K& key)
//        : _left(nullptr)
//        ,_right(nullptr)
//        ,_key(key)
//    {}
//    BSTreeNode<K>* _left;
//    BSTreeNode<K>* _right;
//    K _key;
//};
//
//template <class K>
//class BSTree // Binary Search Tree
//{
//    typedef BSTreeNode<K> Node;
//
//public:
//    bool Insert(const K& key)
//    {
//        if (_root == nullptr)
//        {
//            _root = new Node(key);
//            return true;
//        }
//
//        Node* parent = nullptr;
//        Node* cur = _root;
//
//        while (cur)
//        {
//            parent = cur;
//
//            if (cur->_key < key)
//            {
//                cur = cur->_right;
//            }
//
//            else if (cur->_key > key)
//            {
//                cur = cur->_left;
//            }
//
//            else
//            {
//                return false;
//            }
//        }
//
//        cur = new Node(key);
//
//        if (parent->_key < key)
//        {
//            parent->_right = cur;
//        }
//
//        else if (parent->_key > key)
//        {
//            parent->_left = cur;
//        }
//        
//        return true;
//    }
//
//    bool Find(const K& key)
//    {
//        Node* cur = _root;
//
//        while (cur)
//        {
//            if (cur->_key < key)
//            {
//                cur = cur->_right;
//            }
//
//            else if (cur->_key > key)
//            {
//                cur = cur->_left;
//            }
//
//            else
//            {
//                return true;
//            }
//        }
//        return false;
//    }
//
//    bool Erase(const K& key)
//    {
//        Node* parent = nullptr;
//        Node* cur = _root;
//
//        while (cur)
//        {
//
//            if (cur->_key > key)
//            {             
//                parent = cur;
//                cur = cur->_left;
//            }
//
//            else if (cur->_key < key)
//            {
//                parent = cur;
//                cur = cur->_right;
//            }
//
//            else
//            {
//                // 找到待删除的节点
//                if (cur->_left == nullptr)
//                {
//                    if (cur == _root)
//                    {
//                        _root = cur->_right;
//                    }
//                    else
//                    {
//                        // 1、左节点为空，父亲指向被删除节点的右孩子
//                        if (parent->_left == cur)
//                        {
//                            parent->_left = cur->_right;
//                        }
//
//                        else
//                        {
//                            parent->_right = cur->_right;
//                        }    
//                    }
//                    delete cur;
//                }
//
//                else if (cur->_right == nullptr)
//                {
//                    if (cur == _root)
//                    {
//                        _root = cur->_left;
//                    }
//                    else 
//                    {
//                        // 2、右节点为空，父亲指向被删除节点的左孩子
//                        if (parent->_left == cur)
//                        {
//                            parent->_left = cur->_left;
//                        }
//
//                        else
//                        {
//                            parent->_right = cur->_left;
//                        }
//                    }
//                    delete cur;
//                }
//
//                else
//                {
//                    // 3、两边都不为空，用待删除节点的右子树的最左节点替换待删除的节点
//                    Node* rightMinParent= cur;
//                    Node* rightMin = cur->_right;  // 先往右边走
//                    while (rightMin->_left)
//                    {
//                        // 直到找到右树的最左节点
//                        rightMinParent = rightMin;
//                        rightMin = rightMin->_left;
//                    }
//                    // 代替法
//                    cur->_key = rightMin->_key;
//
//                    // rightMin为找到的待删除节点
//                   
//                    // 1、左节点为空，父亲指向被删除节点的右孩子
//                    if (rightMinParent->_left == rightMin)
//                    {
//                        rightMinParent->_left = rightMin->_right;
//                    }
//
//                    else
//                    {
//                        rightMinParent->_right = rightMin->_right;
//                    }
//                    delete rightMin;
//                }
//
//                return true;
//            }
//        }
//
//        return false;
//
//    }
//
//     void _InOrder(Node* root)
//     {
//         // 中序遍历
//         if (root == nullptr)
//             return;
//         _InOrder(root->_left);
//         cout << root->_key << ' ';
//         _InOrder(root->_right);
//     }
//
//     void InOrder()
//     {
//         _InOrder(_root);
//         cout << endl;
//     }
//private:
//    Node* _root = nullptr;
//
//};


// 二叉搜索树使用场景：
// 1、key模型-》判断在不在：比如查学生是否属于本校学生
// 2、key/value的模型-》通过key找对应的value
// 比如：中英字典互译-》通过单词查汉语意思；统计水果个数
template <class K ,class V>
struct BSTreeNode // Binary Search Tree
{
    BSTreeNode(const K& key,const V& value)
        : _left(nullptr)
        , _right(nullptr)
        , _key(key)
        , _value(value)
    {}
    BSTreeNode<K,V>* _left;
    BSTreeNode<K,V>* _right;
    K _key;
    V _value;
};

template <class K, class V>     
class BSTree // Binary Search Tree
{
    typedef BSTreeNode<K,V> Node;
        
public:
    bool Insert(const K& key,const V& value)
    {
        if (_root == nullptr)
        {
            _root = new Node(key,value);
            return true;
        }

        Node* parent = nullptr;
        Node* cur = _root;

        while (cur)
        {
            parent = cur;

            if (cur->_key < key)
            {
                cur = cur->_right;
            }

            else if (cur->_key > key)
            {
                cur = cur->_left;
            }

            else
            {
                return false;
            }
        }

        cur = new Node(key, value);

        if (parent->_key < key)
        {
            parent->_right = cur;
        }

        else if (parent->_key > key)
        {
            parent->_left = cur;
        }

        return true;
    }

    Node* Find(const K& key)
    {
        Node* cur = _root;

        while (cur)
        {
            if (cur->_key < key)
            {
                cur = cur->_right;
            }

            else if (cur->_key > key)
            {
                cur = cur->_left;
            }

            else
            {
                return cur;
            }
        }
        return nullptr;
    }

    bool Erase(const K& key)
    {
        Node* parent = nullptr;
        Node* cur = _root;

        while (cur)
        {

            if (cur->_key > key)
            {
                parent = cur;
                cur = cur->_left;
            }

            else if (cur->_key < key)
            {
                parent = cur;
                cur = cur->_right;
            }

            else
            {
                // 找到待删除的节点
                if (cur->_left == nullptr)
                {
                    if (cur == _root)
                    {
                        _root = cur->_right;
                    }
                    else
                    {
                        // 1、左节点为空，父亲指向被删除节点的右孩子
                        if (parent->_left == cur)
                        {
                            parent->_left = cur->_right;
                        }

                        else
                        {
                            parent->_right = cur->_right;
                        }
                    }
                    delete cur;
                }

                else if (cur->_right == nullptr)
                {
                    if (cur == _root)
                    {
                        _root = cur->_left;
                    }
                    else
                    {
                        // 2、右节点为空，父亲指向被删除节点的左孩子
                        if (parent->_left == cur)
                        {
                            parent->_left = cur->_left;
                        }

                        else
                        {
                            parent->_right = cur->_left;
                        }
                    }
                    delete cur;
                }

                else
                {
                    // 3、两边都不为空，用待删除节点的右子树的最左节点替换待删除的节点
                    Node* rightMinParent = cur;
                    Node* rightMin = cur->_right;  // 先往右边走
                    while (rightMin->_left)
                    {
                        // 直到找到右树的最左节点
                        rightMinParent = rightMin;
                        rightMin = rightMin->_left;
                    }
                    // 代替法
                    cur->_key = rightMin->_key;

                    // rightMin为找到的待删除节点

                    // 1、左节点为空，父亲指向被删除节点的右孩子
                    if (rightMinParent->_left == rightMin)
                    {
                        rightMinParent->_left = rightMin->_right;
                    }

                    else
                    {
                        rightMinParent->_right = rightMin->_right;
                    }
                    delete rightMin;
                }

                return true;
            }
        }

        return false;

    }

    void _InOrder(Node* root)
    {
        // 中序遍历
        if (root == nullptr)
            return;
        _InOrder(root->_left);
        cout << root->_key << ":" << root->_value << ' ';
        _InOrder(root->_right);
    }

    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }
private:
    Node* _root = nullptr;

};