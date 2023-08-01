//
// Created by 93539 on 2023/7/29.
//

#ifndef BSTREE_BSTREE_H
#define BSTREE_BSTREE_H

#include <iostream>

using namespace std;

template<class K>
struct BSTreeNode {
    BSTreeNode(const K &key)
            : _left(nullptr), _right(nullptr), _key(key) {

    }

    BSTreeNode<K> *_left;
    BSTreeNode<K> *_right;
    K _key;
};

template<class K>
class BSTree {
    typedef BSTreeNode<K> Node;
public:
    BSTree()
            : _root(nullptr) {

    }

    BSTree(const BSTree<K> &t) {
        _root = Copy(t._root);
    }

    BSTree<K> &operator=(BSTree<K> t) {
        swap(_root, t._root);
        return *this;
    }

    ~BSTree() {
        Destroy(_root);
        _root = nullptr;
    }

    bool Insert(const K &key) {
        if (_root == nullptr) {
            _root = new Node(key);
            return true;
        }
        Node *cur = _root;
        Node *parent = nullptr;
        while (cur) {
            if (cur->_key < key) {
                parent = cur;
                cur = cur->_right;
            } else if (cur->_key > key) {
                parent = cur;
                cur = cur->_left;
            } else {
                return false;
            }
        }
        cur = new Node(key);
        if (cur->_key > parent->_key) {
            parent->_right = cur;
        } else {
            parent->_left = cur;
        }
        return true;
    }

    void InOrder() {
        _InOrder(_root);
    }

    bool find(const K &key) {
        Node *cur = _root;
        while (cur) {
            if (key > _root->_key) {
                cur = cur->_right;
            } else if (key < _root->_key) {
                cur = cur->_left;
            } else {
                return true;
            }
        }
        return false;
    }

    bool Erase(const K &key) {
        Node *parent = nullptr;
        Node *cur = _root;
        while (cur) {
            if (cur->_key > key) {
                parent = cur;
                cur = cur->_left;
            } else if (cur->_key < key) {
                parent = cur;
                cur = cur->_right;
            } else {
                if (cur->_left == nullptr) {//1、左为空
                    if (cur == _root) {
                        _root = _root->_right;
                    } else {
                        if (parent->_left == cur) {
                            parent->_left = cur->_right;
                        } else {
                            parent->_right = cur->_right;
                        }
                    }
                    delete cur;
                } else if (cur->_right == nullptr) {//2、右为空
                    if (cur == _root) {
                        _root = _root->_left;
                    } else {
                        if (parent->_left == cur) {
                            parent->_left = cur->_left;
                        } else {
                            parent->_right = cur->_left;
                        }
                    }
                    delete cur;
                } else {//3、左右都不为空，替换删除
                    Node *minRight = cur->_right;
                    Node *Parent = cur;
                    while (minRight->_left) {//找到右子树的最小节点
                        Parent = Parent;
                        minRight = minRight->_left;
                    }
                    cur->_key = minRight->_key;
                    if (minRight == parent->_left) {
                        Parent->_left = minRight->_right;
                    } else {
                        Parent->_right = minRight->_right;
                    }
                    delete minRight;
                }
                return true;
            }
        }
        return false;
    }

    bool InsertR(const K &key) {
        _InsertR(_root, key);
    }

    bool FindR(const K &key) {
        _FindR(_root, key);
    }

    bool EraseR(const K &key) {
        _EraseR(_root, key);
    }

private:
    Node *Copy(Node *root) {
        if (root == nullptr) {
            return nullptr;
        }
        Node *newRoot = new Node(root->_key);
        newRoot->_left = Copy(root->_left);
        newRoot->_right = Copy(root->_right);
        return newRoot;
    }

    void Destroy(Node *root) {
        if (root == nullptr) {
            return;
        }
        Destroy(root->_left);
        Destroy(root->_right);
        delete root;
    }

    bool _InsertR(Node *&root, const K &key) {
        if (root == nullptr) {
            root = new Node(key);
            return true;
        }
        if (root->_key < key) {
            return _InsertR(root->_right, key);
        } else if (root->_key > key) {
            return _InsertR(root->_left, key);
        } else {
            return false;
        }
    }

    bool _FindR(Node *root, const K &key) {
        if (root == nullptr) {
            return false;
        }
        if (root->_key < key) {
            return _FindR(root->_right, key);
        } else if (root->_key > key) {
            return _FindR(root->_left, key);
        } else {
            return true;
        }
    }

    bool _EraseR(Node *&root, const K &key) {
        if (root == nullptr) {
            return false;
        }
        if (root->_key < key) {
            return _EraseR(root->_right, key);
        } else if (root->_key > key) {
            return _EraseR(root->_left, key);
        } else {
            Node *del = root;
            if (root->_right == nullptr) {
                root = root->_left;
            } else if (root->_left == nullptr) {
                root = root->_right;
            } else {
                Node *minRight = root->_right;
                while (minRight->_left) {
                    minRight = minRight->_left;
                }
                swap(root->_key, minRight->_key);
                return _EraseR(root->_right, key);
            }
            delete del;
        }
    }

    void _InOrder(Node *root) {
        if (root == nullptr) {
            return;
        }
        _InOrder(root->_left);
        cout << root->_key << " ";
        _InOrder(root->_right);
    }

private:
    Node *_root = nullptr;
};

#endif //BSTREE_BSTREE_H