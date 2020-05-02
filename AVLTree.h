//
// Created by snirg on 02/05/2020.
//

#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include "AVLTreeNode.h"

template<class T>
class AVLTree {
private:
    AVLTreeNode<T> *root;
public:
    explicit AVLTree(AVLTreeNode<T> const &node = nullptr) : root(node) {}

    AVLTree(AVLTree<T> const &tree) {
        this->root = tree.root;
    }

    ~AVLTree() = default;

    void fixTree(AVLTreeNode<T> *node){
        node->fixNodes();
    }

    status deleteNode(int key){

    }

    status deleteNode(AVLTreeNode<T> *node){}
};


#endif //WET1_AVLTREE_H
