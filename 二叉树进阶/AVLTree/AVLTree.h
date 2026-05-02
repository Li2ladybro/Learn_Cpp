#pragma once
#include<stdlib.h>

template <class K,class V>
struct AVLTreeNode
{
    AVLTreeNode(const std::pair<K,V>& kv)
        :_left(nullptr)
        ,_right(nullptr)
        ,_parent(nullptr)
        ,_kv(kv)
        ,_bf(0)
    {}                        
    // 三叉链 
    AVLTreeNode<K, V>* _left;
    AVLTreeNode<K, V>* _right;
    AVLTreeNode<K, V>* _parent;  // 为了方便更新平衡因子，引入父亲节点指针

    std::pair<K, V> _kv;

    int _bf;                     // balance factor 平衡因子
};

template <class K, class V>
class AVLTree
{
    typedef AVLTreeNode<K, V> Node;

public:
    // 插入
    bool Insert(const std::pair<K,V>& kv)
    {
        // AVLTree的插入
        if (_root == nullptr)
        {
            _root = new Node(kv);
            return true;
        }

        // 1、按照BST的方式插入节点
        Node* parent = nullptr;
        Node* cur = _root;
        
        // 找到插入位置
        while (cur)
        {
            parent = cur;

            if (cur->_kv.first > kv.first)
            {
                cur = cur->_left;
            }

            else if (cur->_kv.first < kv.first)
            {
                cur = cur->_right;
            }

            else
            {
                return false;
            }
        }

        // parent为待插入的位置
        cur = new Node(kv);

        if (parent->_kv.first < kv.first)
        {
            parent->_right = cur;
            cur->_parent = parent;
        }

        else if(parent->_kv.first>kv.first)
        {
            parent->_left = cur;
            cur->_parent = parent;
        }

        // 2、更新平衡因子
        //    平衡因子=右子树高度-左子树高度
        while (parent)
        {
            // 首先更新第一个父亲节点的平衡因子
            // 因为需要参考该节点确定其余祖先是否需要更新
            // 在这里未更新前parent的平衡因子只可能为-1,0,1
            // 如果cur为parent的左则_bf--，cur为parent的右则_bf++
            if (cur == parent->_left)
            {
                parent->_bf--;
             }
            else if (cur == parent->_right)
            {
                parent->_bf++;
            }

            // 3、旋转
            if (parent->_bf == 0)
            {
                // 情况一
                // 更新完parent的平衡因子发现为零
                // 说明parent的高度不变，更新结束，插入完成
                // 解释：说明以前的平衡因子为+-1
                //       新加入的节点把矮的一边填平了，此时parent所在子树的高度未发生变化
                //       对上层的高度也没有影响
                break;
            }
            else if (parent->_bf == 1 || parent->_bf == -1)
            {
                // 情况二
                // 更新完parent的平衡因子发现为+-1
                // 说明parent的高度变了，需要继续往上更新
                // 解释：说明以前的平衡因子为0
                //       新加入的节点把以前平的数调高了一节
                //       对上层的高度产生影响
                cur = parent;
                parent = parent->_parent;
            }
            else if (parent->_bf == 2 || parent->_bf == -2)
            {
                // 情况三
                // 更新完parent的平衡因子发现为+=-2
                // 说明parent的高度变了，不需要继续往上更新了
                // parent所在子树已经不平衡了，需要旋转处理调整
                // 解释：说明以前的平衡因子为+-1
                //       新加入的节点把以的树再调高了一节
                //       对上层的高度产生影响
                // 1、旋转的前提是依然保持是二叉搜索树
                // 2、旋转成平衡树 
                // 3、树的高度不变
                if (parent->_bf == 2)
                {
                    // parent的右子树比左子树高了两节
                    if (cur->_bf == 1)
                    {
                        // RR平衡旋转
                        // cur的右子树比左子树高了1节
                        // 需要左单旋调整
                        RotateL(parent);
                    }
                    else if (cur->_bf == -1)
                    {
                        // RL平衡旋转
                        // cur的左子树比右子树高了1节
                        // 需要右左双旋调整
                        RotateRL(parent);
                    }
                   
                }

                else if (parent->_bf == -2)
                {
                    if (cur->_bf == -1)
                    {
                        // parent的左子树比右子树高了两节
                        // cur的左子树比右子树高了1节
                        // 需要右单旋调整
                        RotateR(parent);
                    }

                    else if (cur->_bf == 1)
                    {
                        // LR平衡旋转
                        // cur的右子树比左子树高了1节
                        // 需要左右双旋调整
                        RotateLR(parent);
                    }
                }
                // 旋转完后，parent所在的树的高度恢复到了，插入节点前的高度
                break;
            }
        }
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
            subR ->_parent=nullptr;
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
        // ppparent的平衡因子不变，parent和subL的平衡因子都变为0
        parent->_bf = subR->_bf = 0;
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
        // ppparent的平衡因子不变，parent和subL的平衡因子都变为0 
        parent->_bf = subL->_bf = 0;  
    }

    //左右双旋
    void RotateLR(Node* parent)
    {
        // 左右双旋调整
        // parent为不平衡节点
        Node* subL = parent->_left;
        Node* subLR = subL->_right;
        int bf = subLR->_bf;

        if (bf == -1)
        {
            parent->_bf = 1;
            subL->_bf = 0;
            subLR->_bf = 0;
        }

        else if (bf == 1)
        {
            parent->_bf = 0;
            subL->_bf = -1;
            subLR->_bf = 0;
        }
        else if (bf == 0)
        {
            parent->_bf = 0;
            subL->_bf = 0;
            subL->_bf = 0;
        }
        RotateL(subL);
        RotateR(parent);
    }

    // 右左双旋
    void RotateRL(Node* parent)
    {
        // 右左双旋调整
        // parent为不平衡节点
        Node* subR = parent->_right;
        Node* subRL = subR->_left;

        int bf = subRL->_bf;

        if (bf == -1)
        {
            parent->_bf = 0;
            subR->_bf = 1;
            subRL->_bf = 0;
         }

        else if (bf == 1)
        {
            parent->_bf = -1;
            subR->_bf = 0;
            subRL->_bf = 0;
        }
        else if (bf == 0)
        {
            parent->_bf = 0;
            subR->_bf = 0;
            subRL->_bf = 0;
        }
        RotateR(subR);
        RotateL(parent);
    }

    void _InOrder(Node* root)
    {
        // 中序遍历
        if (root == nullptr)
            return;
        _InOrder(root->_left);
        std::cout << root->_kv.first << ":" << root->_kv.second << ' ';
        _InOrder(root->_right);
    }

    // 中序遍历
    void InOrder()
    {
        _InOrder(_root);
        std::cout << std::endl;
    }

    int _Height(Node* root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);
        return   leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
    }

    // 树高
    int Height()
    {
        return _Height(_root);
    }

    bool _IsBalance(Node* root)
    {
        // 判断是否平衡
        if (root == nullptr)
            return true;
        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);
        return abs(leftHeight - rightHeight) < 2
               && _IsBalance(root->_left)
               && _IsBalance(root->_right);
    }

    // 判定平衡
    bool IsBalance()
    {
        // 判断AVL树是否平衡
        return _IsBalance(_root);
    }

private:
    Node* _root= nullptr;
};