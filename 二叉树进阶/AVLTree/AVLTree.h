#pragma once

template <class K,class V>
struct AVLTreeNode
{
    AVLTreeNode(const pair<K,V> kv)
        :_left(nullptr)
        ,_right(nullptr)
        ,_parent(nullptr)
        ,_kv(kv)
        ,_bf(0)
    {}                        
    // 三叉链 
    AVLTreeNode<K, V>* _left;
    AVLTreeNode<K, V>* _right;
    AVLTreeNode<K, V>* _parent;

    pair<K, V> _kv;

    int _bf;                     // balance factor 平衡因子
};

template <class K, class V>
class AVLTree
{
    typedef AVLTreeNode<K, V> Node;

    bool insert(const pair<K,V>& kv)
    {
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
            if (cur->_kv.first > kv.first)
            {
                parent = cur;
                cur = cur->_left;
            }

            else if (cur->_kv.first < kv.first)
            {
                parent = cur;
                cur = cur->_right;
            }

            else
                return false;
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

            }
        }
        return true;
    }

private:
    Node* _root;
};