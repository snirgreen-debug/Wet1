//
// Created by snirg on 30/04/2020.
//

#ifndef WET1_AVLTREENODE_H
#define WET1_AVLTREENODE_H

enum status {
    ERROR_ALLOCATION,
    INVALID_INPUT,
    FAILURE,
    SUCCESS
};

template<class T>
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
    AVLTreeNode(int k, T i, AVLTreeNode *p) : key(k), info(i), left(nullptr), right(nullptr), parent(p) {}

    ~AVLTreeNode() = default;

    status addLeftNode(int k, T i) {
        auto *newNode = new AVLTreeNode<T>(k, i, this);
        this->left = newNode;
        return status::SUCCESS;
    }

    status addRightNode(int k, T i) {
        auto *newNode = new AVLTreeNode<T>(k, i, this);
        this->right = newNode;
        return status::SUCCESS;
    }
//    status deleteLeftNode(int key);
//    status deleteRightNode(int key);

    int calcHeight() {
        if (!this) { return -1; }
        int h_l = this->left->calcHeight();
        int h_r = this->right->calcHeight();
        int h_max = (h_l >= h_r) ? h_l : h_r;
        return (1 + h_max);
    }

    int calcBalance() {
        if (!this) { return 0; }
        int left = this->left->calcHeight();
        int right = this->right->calcHeight();
        return (left - right);
    }

//    status preOrderIteration();

};

#endif //WET1_AVLTREENODE_H
