#ifndef __RBTREE_H
#define __RBTREE_H

#include <iostream>

enum Colour
{
    // 黑0 红1
    BLACK,
    RED
};

template<class T>
struct BRTreeNode
{
    BRTreeNode(const T& data)
        :_left(nullptr)
        , _right(nullptr)
        , _parent(nullptr)
        , _data(data)
        , _col(RED)
    {}

    BRTreeNode<T>* _left;
    BRTreeNode<T>* _right;
    BRTreeNode<T>* _parent;

    T _data;                         // 关键字

    Colour _col;                     // 节点颜色
};

// 当为set时T是Value
// 当为map时T是Pair
template<class T>
struct __TreeIterator
{
    typedef RBTreeNode<T> Node;
    typedef __TreeIterator<T> Self;

    __TreeIterator()
        :
    {}

    T& operator*()
    {
        return _node->_data;
    }

    T* operator->()
    {
        return &_node->_data;
    }

    Self& operator++()
    {
        // 1、如果右子树不为空，中序的下一个结点就是右子树的最左结点
        if (_node->_right)
        {
            Node* subLeft = _node->_right;
            while (subLeft->_left)
            {
                subLeft = subLeft->_left;
            }
            _node = subLeft;
          }
        // 如果右边为空，表示_node所在的子树已经访问完毕
        else
        {
            // 右子树为空
            Node* cur = _node;
            Node* parent = cur->_parent;
            while (parent && cur == parent->_right)
            {
                cur = cur->_parent;
                parent = parent->_parent;
            }
            _node = parent;
        }

        return *this;
    }

    Self& operator--()
    {
        return *this;
    }

    bool operator!=(const Self& cur)

    {
        return _node != cur._node;
    }

    Node* _node;
};

// K：键
// T：是V或者是pair
// 当为set时T是Value
// 当为map时T是Pair
// KOfT：本质是个结构体为了获取map or set不同类型的T
template <class K, class T, class KOfT>
class RBTree
{
    // a.根叶黑
    // b.不红红
    // c.黑路同
    typedef BRTreeNode<T> Node;

public:
    typedef __TreeIterator<T> iterator;

    iterator begin()
    {
        // 返回中序遍历的第一个节点
        Node* cur = _root;
        while (cur && cur->_left)
        {
            cur = cur->_left;
        }
        return iterator(cur);
    }

    iterator end()
    {
        return nullptr;
    }

    bool Insert(const T& data)
    {
        // 按搜索树的规则进行插入
        if (_root == nullptr)
        {
            // 空树，直接插入
            _root = new Node(data);
            _root->_col = BLACK;    // 根节点是黑的
            return true;
        }

        KOfT koft;
        Node* parent = nullptr;
        Node* cur = _root;
        while (cur)
        {
            if (koft(cur->_data) > koft(data))
            {
                parent = cur;
                cur = cur->_left;
            }

            else if (koft(cur->_data) < koft(data))
            {
                parent = cur;
                cur = cur->_right;
            }
            else
            {
                return false;
            }
        }
        // parent为待插入节点的父亲
        cur = new Node(data);

        if (koft(parent->_data) > koft(data))
        {
            parent->_left = cur;
        }

        else if (koft(parent->_data) < koft(data))
        {
            parent->_right = cur;
        }
        cur->_parent = parent;


        // 新增节点要给黑的还是红的？一定是会破坏一个规则的
        // cur->_col = RED;         // 可能破坏规则b
        // cur->_col = BLACK;       // 一定破坏规则c，并且每条路径都影响不好调整

        // 新增红节点
        cur->_col = RED;            // 可能破坏规则b
        while (parent && parent->_col == RED)
        {

            Node* grandFather = parent->_parent;
            if (grandFather->_left == parent)
            {
                // 父亲在左边，叔叔在右边
                Node* uncle = grandFather->_right;
                // 情况1：uncle存在，且为红色
                // 处理方式：变色
                if (uncle && uncle->_col == RED)
                {

                    parent->_col = uncle->_col = BLACK;     // 上一代全部改为黑色的
                    grandFather->_col = RED;                // 祖父改为红

                    // 继续往上处理
                    cur = grandFather;
                    parent = cur->_parent;
                }

                else
                {
                    // 情况2 or 情况3：uncle不存在或者为黑
                    // 处理方式：旋转+变色
                    if (cur == parent->_right)
                    {
                        // 情况3：双旋转
                        RotateL(parent);
                        std::swap(cur, parent);
                    }

                    // 情况2（有可能是上面情况三变过来的）
                    RotateR(grandFather);
                    grandFather->_col = RED;
                    parent->_col = BLACK;
                    break;
                }
            }

            else
            {
                if (grandFather->_right == parent)
                {
                    // 父亲在右边，叔叔在左边
                    Node* uncle = grandFather->_left;
                    // 情况1：uncle存在，且为红色
                    // 处理方式：变色
                    if (uncle && uncle->_col == RED)
                    {

                        parent->_col = uncle->_col = BLACK;     // 上一代全部改为黑色的
                        grandFather->_col = RED;                // 祖父改为红

                        // 继续往上处理
                        cur = grandFather;
                        parent = cur->_parent;
                    }

                    else
                    {
                        // 情况2 or 情况3：uncle不存在或者为黑
                        // 处理方式：旋转+变色
                        if (parent->_left == cur)
                        {
                            // 情况3：是折线需要双旋转
                            // 通过旋转将该情况化为情况2
                            RotateR(parent);
                            std::swap(cur, parent);
                        }

                        // 情况2是一种斜线（有可能是上面情况3变过来的）
                        // 处理方式：单旋
                        RotateL(grandFather);
                        grandFather->_col = RED;
                        parent->_col = BLACK;
                        break;
                    }
                }
            }
        }
 
        // 根永远保持黑色
        _root->_col = BLACK;
        return true;
    }

    // 左单旋
    // 左旋示意图：
    //     parent             subR
    //        \                /
    //       subR     ==>    parent
    //        /                \
    //      subRL             subRL
    void RotateL(Node* parent)
    {
        // 左单旋调整
        // parent为不平衡节点
        // Node* subR = parent->_right;
        // Node* subRL = subR->_left;

        // parent->_right = subRL;

        // subR->_left = parent;
        // 问题：引入了父亲指针后，没有处理每个节点的父亲指针
        // 修正
        Node* pparent = parent->_parent;
        Node* subR = parent->_right;
        Node* subRL = subR->_left;

        parent->_right = subRL;

        if (subRL)
        {
            subRL->_parent = parent;
        }

        subR->_left = parent;
        parent->_parent = subR;


        if (parent == _root)
        {
            // 1、如果 parent 是这棵树的根，则换成 subR 作为根
            _root = subR;
            subR->_parent = nullptr;
        }
        else
        {
            // 2、parent不是整棵树的根，也是一颗子树
            if (pparent->_left == parent)
            {
                pparent->_left = subR;
            }

            else if (pparent->_right == parent)
            {
                pparent->_right = subR;
            }

            subR->_parent = pparent;
        }
    }

    // 右单旋
    // 右旋示意图：
    //      parent            subL
    //        /                 \
    //      subL     ==>      parent
    //        \                /
    //       subLR           subLR
    void RotateR(Node* parent)
    {
        // 右单旋调整
        // parent为不平衡节点
        Node* pparent = parent->_parent;
        Node* subL = parent->_left;
        Node* subLR = subL->_right;

        parent->_left = subLR;

        if (subLR)
        {
            subLR->_parent = parent;
        }

        subL->_right = parent;
        parent->_parent = subL;


        if (parent == _root)
        {
            // 1、如果 parent 是这棵树的根，则换成 subL 作为根
            _root = subL;
            subL->_parent = nullptr;
        }
        else
        {
            // 2、parent不是整棵树的根，也是一颗子树
            if (pparent->_left == parent)
            {
                pparent->_left = subL;
            }

            else if (pparent->_right == parent)
            {
                pparent->_right = subL;
            }

            subL->_parent = pparent;
        }
    }

    void _InOrder(Node* root)
    {
        // 中序遍历
        if (root == nullptr)
            return;
        _InOrder(root->_left);
        std::cout << root->_data.first << ":" << root->_kv.second << ' ';
        _InOrder(root->_right);
    }

    // 中序遍历
    void InOrder()
    {
        _InOrder(_root);
        std::cout << std::endl;
    }

    bool _IsValidRBTree(Node* pRoot, size_t k, const size_t blackCount)
    {
        //走到null之后，判断k和black是否相等
        if (nullptr == pRoot)
        {
            if (k != blackCount)
            {
                std::cout << "违反性质四：每条路径中黑色节点的个数必须相同" << std::endl;
                return false;
            }
            return true;
        }
        // 统计黑色节点的个数
        if (BLACK == pRoot->_col)
            k++;
        // 检测当前节点与其双亲是否都为红色
        Node* pParent = pRoot->_parent;
        if (pParent && RED == pParent->_col && RED == pRoot->_col)
        {
            std::cout << "违反性质三：没有连在一起的红色节点" << std::endl;
            return false;
        }
        return _IsValidRBTree(pRoot->_left, k, blackCount) &&
            _IsValidRBTree(pRoot->_right, k, blackCount);
    }

    // 判定是否有效
    bool IsValidRBTree()
    {
        Node* pRoot = _root;
        // 空树也是红黑树
        if (nullptr == pRoot)
            return true;
        // 检测根节点是否满足情况
        if (BLACK != pRoot->_col)
        {
            std::cout << "违反红黑树性质二：根节点必须为黑色" << std::endl;
            return false;
        }
        // 获取任意一条路径中黑色节点的个数
        size_t blackCount = 0;
        Node* pCur = pRoot;
        while (pCur)
        {
            if (BLACK == pCur->_col)
                blackCount++;
            pCur = pCur->_left;
        }
        // 检测是否满足红黑树的性质，k用来记录路径中黑色节点的个数
        size_t k = 0;
        return _IsValidRBTree(pRoot, k, blackCount);
    }

    // 查找
    Node* Find(const K& key)
    {

        KOfT koft;
        Node* cur = this->_root;
        while (cur)
        {
            if (koft(cur->_data) > koft(key))
            {
                cur = cur->_left;
            }

            else if (koft(cur->_data) < koft(key))
            {
                cur = cur->_right;
            }

            else
            {
                return cur;
            }
        }
        return cur;
    }

    int _Height(Node* root)
    {
        if (root == nullptr)
            return 0;
        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);
        return   leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
    }

    // 树高
    int Height()
    {
        return _Height(_root);
    }

private:

    Node* _root = nullptr;
};
#endif


//// 键值对版本
//#ifndef __RBTREE_H
//#define __RBTREE_H
//
//#include <iostream>
//
//enum Colour
//{
//    // 黑0 红1
//    BLACK,
//    RED
//};
//
//template<class K, class V>
//struct BRTreeNode
//{
//    BRTreeNode(const std::pair<K, V>& kv)
//        :_left(nullptr)
//        , _right(nullptr)
//        , _parent(nullptr)
//        , _kv(kv)
//        , _col(RED)
//    {
//    }
//    BRTreeNode<K, V>* _left;
//    BRTreeNode<K, V>* _right;
//    BRTreeNode<K, V>* _parent;
//
//    std::pair<K, V> _kv;             // 关键字
//
//    Colour _col;                     // 节点颜色
//};
//
//template <class K, class V>
//class RBTree
//{
//    // a.根叶黑
//    // b.不红红
//    // c.黑路同
//    typedef BRTreeNode<K, V> Node;
//
//public:
//
//    bool Insert(const std::pair<K, V>& kv)
//    {
//        // 按搜索树的规则进行插入
//        if (_root == nullptr)
//        {
//            // 空树，直接插入
//            _root = new Node(kv);
//            _root->_col = BLACK;    // 根节点是黑的
//            return true;
//        }
//
//        Node* parent = nullptr;
//        Node* cur = _root;
//        while (cur)
//        {
//            if (cur->_kv.first > kv.first)
//            {
//                parent = cur;
//                cur = cur->_left;
//            }
//            else if (cur->_kv.first < kv.first)
//            {
//                parent = cur;
//                cur = cur->_right;
//            }
//            else
//            {
//                // 已经存在相同的key了，不允许插入
//                return false;
//            }
//        }
//
//        // parent为待插入节点的父亲
//        cur = new Node(kv);
//
//        if (parent->_kv.first > kv.first)
//        {
//            parent->_left = cur;
//        }
//
//        else if (parent->_kv.first < kv.first)
//        {
//            parent->_right = cur;
//        }
//        cur->_parent = parent;
//
//        // 红黑树调整
//        // 新增节点要给黑的还是红的？ 一定是会破坏一个规则的
//        // cur->_col = RED;         // 可能破坏规则b
//        // cur->_col = BLACK;       // 一定破坏规则c，并且每条路径都影响不好调整
//        // 新增红节点
//        cur->_col = RED;            // 可能破坏规则b
//        while (parent && parent->_col == RED)
//        {
//
//            Node* grandFather = parent->_parent;
//            if (grandFather->_left == parent)
//            {
//                // 父亲在左边，叔叔在右边
//                Node* uncle = grandFather->_right;
//                // 情况1：uncle存在，且为红色
//                // 处理方式：变色
//                if (uncle && uncle->_col == RED)
//                {
//
//                    parent->_col = uncle->_col = BLACK;     // 上一代全部改为黑色的
//                    grandFather->_col = RED;                // 祖父改为红
//
//                    // 继续往上处理
//                    cur = grandFather;
//                    parent = cur->_parent;
//                }
//
//                else
//                {
//                    // 情况2 or 情况3：uncle不存在或者为黑
//                    // 处理方式：旋转+变色
//                    if (cur == parent->_right)
//                    {
//                        // 情况3：双旋转
//                        RotateL(parent);
//                        std::swap(cur, parent);
//                    }
//
//                    // 情况二（有可能是上面情况三变过来的）
//                    RotateR(grandFather);
//                    grandFather->_col = RED;
//                    parent->_col = BLACK;
//                    break;
//                }
//            }
//
//            else
//            {
//                // 父亲在右边，叔叔在左边
//                Node* uncle = grandFather->_left;
//                // 情况1：uncle存在，且为红色
//                // 处理方式：变色
//                if (uncle && uncle->_col == RED)
//                {
//
//                    parent->_col = uncle->_col = BLACK;     // 上一代全部改为黑色的
//                    grandFather->_col = RED;                // 祖父改为红
//
//                    // 继续往上处理
//                    cur = grandFather;
//                    parent = cur->_parent;
//                }
//
//                else
//                {
//                    // 情况2 or 情况3：uncle不存在或者为黑
//                    // 处理方式：旋转+变色
//                    if (parent->_left == cur)
//                    {
//                        // 情况3：是折线需要双旋转
//                        // 通过旋转将该情况化为情况2
//                        RotateR(parent);
//                        std::swap(cur, parent);
//                    }
//
//                    // 情况2是一种斜线（有可能是上面情况3变过来的）
//                    // 处理方式：单旋
//                    RotateL(grandFather);
//                    grandFather->_col = RED;
//                    parent->_col = BLACK;
//                    break;
//                }
//            }
//        }
//
//        // 根永远保持黑色
//        _root->_col = BLACK;
//        return true;
//    }
//
//    // 左单旋
//    // 左旋示意图：
//    //     parent             subR
//    //        \                /
//    //       subR     ==>    parent
//    //        /                \
//    //      subRL             subRL
//    void RotateL(Node* parent)
//    {
//        // 左单旋调整
//        // parent为不平衡节点
//        // Node* subR = parent->_right;
//        // Node* subRL = subR->_left;
//
//        // parent->_right = subRL;
//
//        // subR->_left = parent;
//        // 问题：引入了父亲指针后，没有处理每个节点的父亲指针
//        // 修正
//        Node* pparent = parent->_parent;
//        Node* subR = parent->_right;
//        Node* subRL = subR->_left;
//
//        parent->_right = subRL;
//
//        if (subRL)
//        {
//            subRL->_parent = parent;
//        }
//
//        subR->_left = parent;
//        parent->_parent = subR;
//
//
//        if (parent == _root)
//        {
//            // 1、如果 parent 是这棵树的根，则换成 subR 作为根
//            _root = subR;
//            subR->_parent = nullptr;
//        }
//        else
//        {
//            // 2、parent不是整棵树的根，也是一颗子树
//            if (pparent->_left == parent)
//            {
//                pparent->_left = subR;
//            }
//
//            else if (pparent->_right == parent)
//            {
//                pparent->_right = subR;
//            }
//
//            subR->_parent = pparent;
//        }
//    }
//
//    // 右单旋
//    // 右旋示意图：
//    //      parent            subL
//    //        /                 \
//    //      subL     ==>      parent
//    //        \                /
//    //       subLR           subLR
//    void RotateR(Node* parent)
//    {
//        // 右单旋调整
//        // parent为不平衡节点
//        Node* pparent = parent->_parent;
//        Node* subL = parent->_left;
//        Node* subLR = subL->_right;
//
//        parent->_left = subLR;
//
//        if (subLR)
//        {
//            subLR->_parent = parent;
//        }
//
//        subL->_right = parent;
//        parent->_parent = subL;
//
//
//        if (parent == _root)
//        {
//            // 1、如果 parent 是这棵树的根，则换成 subL 作为根
//            _root = subL;
//            subL->_parent = nullptr;
//        }
//        else
//        {
//            // 2、parent不是整棵树的根，也是一颗子树
//            if (pparent->_left == parent)
//            {
//                pparent->_left = subL;
//            }
//
//            else if (pparent->_right == parent)
//            {
//                pparent->_right = subL;
//            }
//
//            subL->_parent = pparent;
//        }
//    }
//
//    // 查找
//    Node* Find(const std::pair<K,V>& kv)
//    {
//        Node* cur = this->_root;
//        while (cur)
//        {
//            if (cur->_kv.first > kv.first)
//            {
//                cur = cur->_left;
//            }
//            else if (cur->_kv.first < kv.first)
//            {
//                cur = cur->_right;
//            }
//            else
//            {
//                return cur;
//            }
//        }
//        return cur;
//    }
//
//    int _Height(Node* root)
//    {
//        if (root == nullptr)
//            return 0;
//        int leftHeight = _Height(root->_left);
//        int rightHeight = _Height(root->_right);
//        return   leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
//    }
//
//    // 树高
//    int Height()
//    {
//        return _Height(_root);
//    }
//
//    void _InOrder(Node* root)
//    {
//        // 中序遍历
//        if (root == nullptr)
//            return;
//        _InOrder(root->_left);
//        std::cout << root->_kv.first << ":" << root->_kv.second << ' ';
//        _InOrder(root->_right);
//    }
//
//    // 中序遍历
//    void InOrder()
//    {
//        _InOrder(_root);
//        std::cout << std::endl;
//    }
//
//    bool _IsValidRBTree(Node* pRoot, size_t k, const size_t blackCount)
//    {
//        //走到null之后，判断k和black是否相等
//        if (nullptr == pRoot)
//        {
//            if (k != blackCount)
//            {
//                std::cout << "违反性质四：每条路径中黑色节点的个数必须相同" << std::endl;
//                return false;
//            }
//            return true;
//        }
//        // 统计黑色节点的个数
//        if (BLACK == pRoot->_col)
//            k++;
//        // 检测当前节点与其双亲是否都为红色
//        Node* pParent = pRoot->_parent;
//        if (pParent && RED == pParent->_col && RED == pRoot->_col)
//        {
//            std::cout << "违反性质三：没有连在一起的红色节点" << std::endl;
//            return false;
//        }
//        return _IsValidRBTree(pRoot->_left, k, blackCount) &&
//            _IsValidRBTree(pRoot->_right, k, blackCount);
//    }
//
//    // 红黑树是否有效
//    bool IsValidRBTree()
//    {
//        Node* pRoot = _root;
//        // 空树也是红黑树
//        if (nullptr == pRoot)
//            return true;
//        // 检测根节点是否满足情况
//        if (BLACK != pRoot->_col)
//        {
//            std::cout << "违反红黑树性质二：根节点必须为黑色" << std::endl;
//            return false;
//        }
//        // 获取任意一条路径中黑色节点的个数
//        size_t blackCount = 0;
//        Node* pCur = pRoot;
//        while (pCur)
//        {
//            if (BLACK == pCur->_col)
//                blackCount++;
//            pCur = pCur->_left;
//        }
//        // 检测是否满足红黑树的性质，k用来记录路径中黑色节点的个数
//        size_t k = 0;
//        return _IsValidRBTree(pRoot, k, blackCount);
//    }
//
//private:
//
//    Node* _root = nullptr;
//};
//#endif