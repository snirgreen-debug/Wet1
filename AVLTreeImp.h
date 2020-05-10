//
// Created by snirg on 06/05/2020.
//
#ifndef WET1_AVLTREEIMP_H
#define WET1_AVLTREEIMP_H

#include "AVLTree.h"

template<typename T>
AVLNode<T>::AVLNode(int k, int h, AVLNode<T> *p) : key(k), height(h), info(nullptr),
                                                   left(nullptr), right(nullptr), parent(p) {}

template<typename T>
AVLNode<T>::AVLNode(int k, T i, AVLNode<T> *p) : key(k), height(0), info(i),
                                                 left(nullptr), right(nullptr), parent(p) {}

template<typename T>
AVLNode<T>::AVLNode(AVLNode<T> const &node) {
    this->key = node.key;
    this->height = 0;
    this->info = new T(node.info);
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

template<typename T>
AVLNode<T>::~AVLNode() {
    delete info;
    delete left;
    delete right;
    left = right = parent = nullptr;
    info = nullptr;
}

template<typename T>
AVLTree<T>::AVLTree(int size) {
    int total = 1;
    int h = 0;
    while (total <= size) {
        total *= 2;
        ++h;
    }

    auto *node = completeTree(h);
    int toDelete = total - 1 - size;
    cleanCompleteTree(toDelete, node);
    int starterKey = 0;
    fillAVLTreeKeys(node, starterKey);

    this->root = node;
    this->smallestNode = findSmallest(this->root);
}

template<typename T>
AVLNode<T> *AVLTree<T>::findSmallest(AVLNode<T> *subRoot) {
    if (!subRoot->left) { return subRoot; }
    return findSmallest(subRoot->left);
}

template<typename T>
AVLTree<T>::AVLTree(AVLNode<T> *node) : root(node), smallestNode(node) {}

template<typename T>
AVLTree<T>::AVLTree() : root(nullptr), smallestNode(nullptr) {}

template<typename T>
AVLTree<T>::~AVLTree() {
    delete root;
    root = smallestNode = nullptr;
}

template<typename T>
int AVLTree<T>::max(int h1, int h2) {
    return (h1 >= h2 ? h1 : h2);
}

template<typename T>
int AVLTree<T>::getHeight(AVLNode<T> *node) {
    if (!node) { return -1; }
    return node->height;
}

template<typename T>
int AVLTree<T>::calcHeight(AVLNode<T> *node) {
    return 1 + max(getHeight(node->left), getHeight(node->right));
}

template<typename T>
int AVLTree<T>::pwr(int base, int exp) {
    int pwr = 1;
    for (int i = 0; i < exp; i++) {
        pwr = pwr * base;
    }
    return pwr;
}

template<typename T>
int AVLTree<T>::calcBalance(AVLNode<T> *node) {
    if (!node) { return 0; }
    return (getHeight(node->left) - getHeight(node->right));
}

template<typename T>
bool AVLTree<T>::isLeaf(AVLNode<T> *node) {
    return ((!node->left) && (!node->right));
}

template<typename T>
AVLNode<T> *AVLTree<T>::completeTree(int h, AVLNode<T> *p) {
    if (h == 0) { return nullptr; }
    auto *node = new AVLNode<T>(0, h - 1, p);
    node->left = (completeTree(h - 1, node));
    node->right = (completeTree(h - 1, node));
    return node;
}

template<typename T>
void AVLTree<T>::cleanCompleteTree(int &toDelete, AVLNode<T> *node) {
    if (node == nullptr || toDelete == 0) return;
    cleanCompleteTree(toDelete, node->right);
    if (isLeaf(node)) {
        if (!node->parent->right) {
            node->parent->left = nullptr;
        }
        node->parent->right = nullptr;
        delete node;
        toDelete--;
    } else {
        cleanCompleteTree(toDelete, node->left);
        node->height = calcHeight(node);
    }
}

template<typename T>
void AVLTree<T>::fillAVLTreeKeys(AVLNode<T> *node, int &starterKey) {
    if (node == nullptr) return;
    fillAVLTreeKeys(node->left, starterKey);
    node->key = starterKey;
    starterKey++;
    fillAVLTreeKeys(node->right, starterKey);
}

template<typename T>
AVLNode<T> *AVLTree<T>::LL(AVLNode<T> *B) {
    AVLNode<T> *A = B->left;
    B->left = A->right;
    A->right = B;

    if (B->left) { B->left->parent = B; }
    A->parent = B->parent;
    B->parent = A;

    A->height = max(getHeight(A->left), getHeight(A->right)) + 1;
    B->height = max(getHeight(B->left), getHeight(B->right)) + 1;

    return A;
}

template<typename T>
AVLNode<T> *AVLTree<T>::RR(AVLNode<T> *B) {
    AVLNode<T> *A = B->right;
    B->right = A->left;
    A->left = B;

    if (B->right) { B->right->parent = B; }
    A->parent = B->parent;
    B->parent = A;

    A->height = max(getHeight(A->left), getHeight(A->right)) + 1;
    B->height = max(getHeight(B->left), getHeight(B->right)) + 1;

    return A;
}

template<typename T>
AVLNode<T> *AVLTree<T>::LR(AVLNode<T> *C) {
    AVLNode<T> *B = C->left;
    C->left = RR(B);
    return LL(C);
}

template<typename T>
AVLNode<T> *AVLTree<T>::RL(AVLNode<T> *C) {
    AVLNode<T> *B = C->right;
    C->right = LL(B);
    return RR(C);
}


template<typename T>
AVLNode<T> *AVLTree<T>::balanceNode(AVLNode<T> *node) {
    int nodeBalance = this->calcBalance(node);
    if (nodeBalance > 1) {
        int leftBalance = this->calcBalance(node->left);
        if (leftBalance >= 0) {//todo: in the videos >=0 but in the internet > 0
            node = LL(node);
        } else {
            node = LR(node);
        }
    } else if (nodeBalance < -1) {
        int rightBalance = this->calcBalance(node->right);
        if (rightBalance > 0) {
            node = RL(node);
        } else {
            node = RR(node);
        }
    }

    return node;
}

template<typename T>
AVLNode<T> *AVLTree<T>::insertNode(AVLNode<T> *currentNode, int key, T info, AVLNode<T> *parent) {
    if (!currentNode) {
        auto *newNode = new AVLNode<T>(key, info, parent);
        if (!this->smallestNode) {
            this->smallestNode = newNode;
        } else if (this->smallestNode->key >= key) {
            this->smallestNode = newNode;
        }
        return newNode;
    }
    if (key < currentNode->key) {
        currentNode->left = insertNode(currentNode->left, key, info, currentNode);
    }
    if (key > currentNode->key) {
        currentNode->right = insertNode(currentNode->right, key, info, currentNode);
    }
    if (key == currentNode->key) {
        return currentNode;
    }

    currentNode = balanceNode(currentNode);
    currentNode->height = max(getHeight(currentNode->left), getHeight(currentNode->right)) + 1;

    return currentNode;
}

template<typename T>
AVLNode<T> *AVLTree<T>::findFollowingNode_aux(AVLNode<T> *node) {
    if (!node->left) { return node; }
    return findFollowingNode_aux(node->left);
}

template<typename T>
AVLNode<T> *AVLTree<T>::findFollowingNode(AVLNode<T> *node) {
    if (!node) { return nullptr; }
    if (!node->right) { return nullptr; }
    return findFollowingNode_aux(node->right);
}

template<typename T>
AVLNode<T> *AVLTree<T>::deleteNode(AVLNode<T> *currentNode, int key, AVLNode<T> *parent) {
    this->root = deleteNode_aux(currentNode, key, parent);
    this->smallestNode = findSmallest(this->root);
    return this->root;
}

template<typename T>
AVLNode<T> *AVLTree<T>::deleteNode_aux(AVLNode<T> *currentNode, int key, AVLNode<T> *parent) {
    if (!currentNode) { return currentNode; }
    AVLNode<T> *retNode = nullptr;

    if (key < currentNode->key) {
        currentNode->left = deleteNode_aux(currentNode->left, key, currentNode);
    }
    if (key > currentNode->key) {
        currentNode->right = deleteNode_aux(currentNode->right, key, currentNode);
    }
    if (key == currentNode->key) {
        if (!currentNode->left && !currentNode->right) {
            delete currentNode;
            return nullptr;
        }
        if (!currentNode->left) {
            retNode = currentNode->right;
            delete currentNode;
            return retNode;
        }
        if (!currentNode->right) {
            retNode = currentNode->left;
            delete currentNode;
            return retNode;
        }
        if (currentNode->left && currentNode->right) {
            AVLNode<T> *followingNode = this->findFollowingNode(currentNode);
            int tmpKey = followingNode->key;
            T tmpInfo = followingNode->info;

            followingNode->key = currentNode->key;
            followingNode->info = currentNode->info;

            currentNode->key = tmpKey;
            currentNode->info = tmpInfo;

            currentNode->right = deleteNode_aux(currentNode->right, key, currentNode->parent);
        }
    }

    currentNode = balanceNode(currentNode);
    currentNode->height = max(getHeight(currentNode->left), getHeight(currentNode->right)) + 1;

    return currentNode;
}

template<typename T>
AVLNode<T> *AVLTree<T>::removeNode(int key) {
    AVLNode<T> *node = getNodeByKey(this->root, key);
    auto *retNode = new AVLNode<T>(node->key, node->info);
    deleteNode(this->root, key);
    return retNode;
}

template<typename T>
AVLNode<T> *AVLTree<T>::getNodeByKey(AVLNode<T> *currentNode, int key) {
    if (!currentNode) { return nullptr; }
    if (currentNode->key == key) { return currentNode; }
    AVLNode<T> *leftNode = getNodeByKey(currentNode->left, key);
    AVLNode<T> *rightNode = getNodeByKey(currentNode->right, key);
    if (leftNode) {
        return leftNode;
    }
    if (rightNode) {
        return rightNode;
    }

    return nullptr;
}


#endif //WET1_AVLTREEIMP_H