//
// Created by snirg on 06/05/2020.
//

#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include <iostream>

template<typename T>
class AVLNode {
public:
    int key;
    int height;
    T info;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;

    explicit AVLNode(int k, int h = 0, AVLNode<T> *p = nullptr);

    AVLNode(int k, T info, AVLNode<T> *p = nullptr);

    AVLNode(AVLNode<T> const &node);

    ~AVLNode();
};

template<typename T>
class AVLTree {
public:
    AVLNode<T> *root;
    AVLNode<T> *smallestNode;

    explicit AVLTree(int size);

    explicit AVLTree(AVLNode<T> *node);

    explicit AVLTree();

    ~AVLTree();

    AVLNode<T> *completeTree(int h, AVLNode<T> *p = nullptr);

    int calcBalance(AVLNode<T> *node);

    int max(int h1, int h2);

    int getHeight(AVLNode<T> *node);

    int calcHeight(AVLNode<T> *node);

    int pwr(int base, int exp);

    bool isLeaf(AVLNode<T> *node);

    void cleanCompleteTree(int &toDelete, AVLNode<T> *root);

    void fillAVLTreeKeys(AVLNode<T> *node, int &starterKey);

    AVLNode<T> *findSmallest(AVLNode<T> *subRoot);

    AVLNode<T> *LL(AVLNode<T> *B);

    AVLNode<T> *RR(AVLNode<T> *B);

    AVLNode<T> *LR(AVLNode<T> *C);

    AVLNode<T> *RL(AVLNode<T> *C);

    AVLNode<T> *balanceNode(AVLNode<T> *node);

    AVLNode<T> *insertNode(AVLNode<T> *currentNode, int key, T info, AVLNode<T> *parent = nullptr);

    AVLNode<T> *findFollowingNode_aux(AVLNode<T> *node);

    AVLNode<T> *findFollowingNode(AVLNode<T> *node);

    AVLNode<T> *removeNode(int key);

    AVLNode<T> *deleteNode_aux(AVLNode<T> *currentNode, int key, AVLNode<T> *parent);

    AVLNode<T> *deleteNode(AVLNode<T> *currentNode, int key, AVLNode<T> *parent = nullptr);

    AVLNode<T> *getNodeByKey(AVLNode<T> *currentNode, int key);

    void printInOrder(AVLNode<T> *node) {
        if (!node) { return; }
        printInOrder(node->left);
        std::cout << node->key << ", ";
        printInOrder(node->right);
    }
};


#endif //WET1_AVLTREE_H
