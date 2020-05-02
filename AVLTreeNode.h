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

public:
    AVLTreeNode(int k, T i, AVLTreeNode *p = nullptr) : key(k), info(i), left(nullptr), right(nullptr), parent(p) {}

    AVLTreeNode(AVLTreeNode const &node) {
        this->key = node.key;
        this->info = node.info;
        this->left = node.left;
        this->right = node.right;
        this->parent = node.parent;
    }

    ~AVLTreeNode() = default;

/// Get functions
    int getKey() {
        return this->key;
    }

    T getInfo() {
        return this->info;
    }

    AVLTreeNode *getLeftNode() {
        return this->left;
    }

    AVLTreeNode *getRightNode() {
        return this->right;
    }

    AVLTreeNode *getParent() {
        return this->parent;
    }

/// Rotations
    AVLTreeNode *RightRot() {
        AVLTreeNode *A = this->left, *B = this;
        B->left = A->right;
        A->right = B;

        A->parent = B->parent;
        B->parent = A;
        if (B->left) {
            B->left->parent = B;
        }
        return this->parent;
    }

    AVLTreeNode *LeftRot() {
        AVLTreeNode *A = this->right, *B = this;
        B->right = A->left;
        A->left = B;

        A->parent = B->parent;
        B->parent = A;
        if (B->right) {
            B->right->parent = B;
        }
        return this->parent;
    }

    AVLTreeNode *LL() {
        return this->RightRot();
    }

    AVLTreeNode *RR() {
        return this->LeftRot();
    }

    AVLTreeNode *LR() {
        this->left = this->left->LeftRot();
        return this->RightRot();
    }

    AVLTreeNode *RL() {
        this->right = this->right->RightRot();
        return this->LeftRot();
    }

/// Adding Nodes
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

/// Calculations
    int calcHeight() {
        if (!this) { return -1; }
        int h_l = this->left->calcHeight();
        int h_r = this->right->calcHeight();
        int h_max = (h_l >= h_r) ? h_l : h_r;
        return (1 + h_max);
    }

    int calcBalance() {
        if (!this) { return 0; }
        int leftHeight = this->left->calcHeight();
        int rightHeight = this->right->calcHeight();
        return (leftHeight - rightHeight);
    }

/// Iteration section
    void preOrderIteration(void (*do_something)(AVLTreeNode *)) {
        if (!this) { return; }
        do_something(this);
        this->left->preOrderIteration(do_something);
        this->right->preOrderIteration(do_something);
    }

    void inOrderIteration(void (*do_something)(AVLTreeNode *)) {
        if (!this) { return; }
        this->left->inOrderIteration(do_something);
        do_something(this);
        this->right->inOrderIteration(do_something);
    }

    void postOrderIteration(void (*do_something)(AVLTreeNode *)) {
        if (!this) { return; }
        this->left->postOrderIteration(do_something);
        this->right->postOrderIteration(do_something);
        do_something(this);
    }

/// Fix nodes

    //todo: is there a better way to return the root?
    AVLTreeNode *fixNodes() {
        int rootBalance = this->calcBalance();
        int leftBalance = this->left->calcBalance();
        int rightBalance = this->right->calcBalance();

        if (rootBalance == 2) {
            if (leftBalance >= 0) { this->LL(); }
            else if (leftBalance == -1) { this->LR(); }
        } else if (rootBalance == -2) {
            if (rightBalance == 1) { this->RL(); }
            else if (rightBalance <= 0) { this->RR(); }
        }

        if (!this->parent) {
            return this;
        }
        return this->parent->fixNodes();
    }
};

#endif //WET1_AVLTREENODE_H
