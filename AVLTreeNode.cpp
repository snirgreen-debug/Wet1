//
// Created by snirg on 30/04/2020.
//

#include "AVLTreeNode.h"

template<class T>
AVLTreeNode<T>::AVLTreeNode(int k, T i, AVLTreeNode *p) : key(k), info(i), left(nullptr), right(nullptr), parent(p) {}

template<class T>
int AVLTreeNode<T>::calcHeight(AVLTreeNode node) {
    if (!node) { return -1; }
    return (1 + AVLTreeNode<T>::calcHeight(node.left) + AVLTreeNode<T>::calcHeight(node.right));
}

template<class T>
int AVLTreeNode<T>::calcBalance(AVLTreeNode node) {
    if (!node) { return -1; }
    return (calcHeight(node.left) - calcHeight(node.right));
}