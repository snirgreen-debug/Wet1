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

    int getKey(){
        return this->key;
    }

    AVLTreeNode *getLeftNode(){
        return this->left;
    }

    AVLTreeNode *getRightNode(){
        return this->right;
    }

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

    void preOrderIteration(void (*do_something)(AVLTreeNode*)){
        if(!this){return;}
        do_something(this);
        this->left->preOrderIteration(do_something);
        this->right->preOrderIteration(do_something);
    }

    void inOrderIteration(void (*do_something)(AVLTreeNode*)){
        if(!this){return;}
        this->left->inOrderIteration(do_something);
        do_something(this);
        this->right->inOrderIteration(do_something);
    }

    void postOrderIteration(void (*do_something)(AVLTreeNode*)){
        if(!this){return;}
        this->left->postOrderIteration(do_something);
        this->right->postOrderIteration(do_something);
        do_something(this);
    }

};

#endif //WET1_AVLTREENODE_H
