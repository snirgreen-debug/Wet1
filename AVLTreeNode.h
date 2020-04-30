//
// Created by snirg on 30/04/2020.
//

#ifndef WET1_AVLTREENODE_H
#define WET1_AVLTREENODE_H

template <class T>
class AVLTreeNode {
private:
    int key;
    T info;
    AVLTreeNode *left;
    AVLTreeNode *right;
    AVLTreeNode *parent;
public:
    AVLTreeNode(int k, T i, AVLTreeNode *p) : key(k), info(i), left(nullptr), right(nullptr), parent(p);

};


#endif //WET1_AVLTREENODE_H
