//
// Created by snirg on 30/04/2020.
//

#ifndef WET1_AVLTREENODE_H
#define WET1_AVLTREENODE_H

enum status{
    ERROR_ALLOCATION,
    INVALID_INPUT,
    FAILURE,
    SUCCESS
};

template <class T>
class AVLTreeNode {
private:
    int key;
    T info;
    AVLTreeNode *left;
    AVLTreeNode *right;
    AVLTreeNode *parent;

//    void LL();
//    void RR();
//    void LR();
//    void RL();
public:
    AVLTreeNode(int k, T i, AVLTreeNode *p);
    ~AVLTreeNode();

//    status addLeftNode(int key, T info);
//    status addRightNode(int key, T info);
//    status deleteLeftNode(int key);
//    status deleteRightNode(int key);

    int calcHeight(AVLTreeNode node);
    int calcBalance(AVLTreeNode node);

//    status preOrderIteration();

};


#endif //WET1_AVLTREENODE_H
