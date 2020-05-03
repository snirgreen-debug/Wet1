//
// Created by snirg on 02/05/2020.
//

#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

template<typename T>
struct Node {
    int key;
    int height;
    T info;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

enum status {
    ERROR_ALLOCATION,
    INVALID_INPUT,
    FAILURE,
    SUCCESS
};

template<class T>
class AVLTree {
private:
public:
    Node<T> *root;

    explicit AVLTree(Node<T> *node = nullptr) : root(node) {}

    AVLTree(AVLTree<T> const &tree) {
        this->root = tree.root;
    }

    ~AVLTree() = default;

    int calcBalance(Node<T> *node) {
        if (!node) return 0;
        return (getHeight(node->left) - getHeight(node->right));
    }

    int max(int h1, int h2) {
        return (h1 >= h2 ? h1 : h2);
    }

    int getHeight(Node<T> *node) {
        if (!node) { return -1; }
        return node->height;
    }

    Node<T> *LL(Node<T> *B) {
        Node<T> *A = B->left;
        B->left = A->right;
        A->right = B;

        if (B->left) { B->left->parent = B; }
        A->parent = B->parent;
        B->parent = A;

        A->height = max(getHeight(A->left), getHeight(A->right)) + 1;
        B->height = max(getHeight(B->left), getHeight(B->right)) + 1;

        return A;
    }

    Node<T> *RR(Node<T> *B) {
        Node<T> *A = B->right;
        B->right = A->left;
        A->left = B;

        if (B->right) { B->right->parent = B; }
        A->parent = B->parent;
        B->parent = A;

        A->height = max(getHeight(A->left), getHeight(A->right)) + 1;
        B->height = max(getHeight(B->left), getHeight(B->right)) + 1;

        return A;
    }

    Node<T> *LR(Node<T> *C) {
        Node<T> *B = C->left;
        C->left = RR(B);
        return LL(C);
    }

    Node<T> *RL(Node<T> *C) {
        Node<T> *B = C->right;
        C->right = LL(B);
        return RR(C);
    }

    Node<T> *balanceNode(Node<T> *node) {
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

    Node<T> *createNewNode(int key, Node<T> *parent) {
        auto *newNode = new Node<T>;
        newNode->key = key;
        newNode->height = 0;
        newNode->info = 0;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->parent = parent;
    }

    Node<T> *insertEmptyNode(Node<T> *currentNode, int key, Node<T> *parent = nullptr) {
        if (!currentNode) {
            Node<T> *newNode = this->createNewNode(key, parent);
            return newNode;
        }
        if (key < currentNode->key) {
            currentNode->left = insertEmptyNode(currentNode->left, key, currentNode);
        }
        if (key > currentNode->key) {
            currentNode->right = insertEmptyNode(currentNode->right, key, currentNode);
        }
        if (key == currentNode->key) {
            return currentNode;
        }

        currentNode = balanceNode(currentNode);
        currentNode->height = max(getHeight(currentNode->left), getHeight(currentNode->right)) + 1;

        return currentNode;
    }

    Node<T> *insertNode(Node<T> *currentNode, Node<T> *newNode, Node<T> *parent = nullptr) {
        if (!currentNode) {
            return newNode;
        }
        if (newNode->key < currentNode->key) {
            currentNode->left = insertEmptyNode(currentNode->left, newNode->key, currentNode);
        }
        if (newNode->key > currentNode->key) {
            currentNode->right = insertEmptyNode(currentNode->right, newNode->key, currentNode);
        }
        if (newNode->key == currentNode->key) {
            return currentNode;
        }

        currentNode = balanceNode(currentNode);
        currentNode->height = max(getHeight(currentNode->left), getHeight(currentNode->right)) + 1;

        return currentNode;
    }

    Node<T> *getNodeByKey_aux(Node<T> *node, int key) {
        if (!node) { return nullptr; }
        if (node->key == key) { return node; }
        Node<T> *leftNode = getNodeByKey_aux(node->left, key);
        Node<T> *rightNode = getNodeByKey_aux(node->right, key);
        if (leftNode) {
            return leftNode;
        }
        if (rightNode) {
            return rightNode;
        }

        return nullptr;
    }

    Node<T> *getNodeByKey(int key) {
        return this->getNodeByKey_aux(this->root, key);
    }

    Node<T> *findFollowingNode_aux(Node<T> *node) {
        if (!node->left) { return node; }
        return findFollowingNode_aux(node->left);
    }

    Node<T> *findFollowingNode(Node<T> *node) {
        if (!node) { return nullptr; }
        if (!node->right) { return nullptr; }
        return findFollowingNode_aux(node->right);
    }

    Node<T> *deleteNode(Node<T> *currentNode, int key, Node<T> *parent = nullptr) {
        if (!currentNode) { return currentNode; }
        Node<T> *retNode = nullptr;

        if (key < currentNode->key) {
            currentNode->left = deleteNode(currentNode->left, key, currentNode);
        }
        if (key > currentNode->key) {
            currentNode->right = deleteNode(currentNode->right, key, currentNode);
        }
        if (key == currentNode->key) {
            if (!currentNode->left && !currentNode->right) {
//                delete currentNode->info;
                delete currentNode;
                return nullptr;
            }
            if (!currentNode->left) {
                retNode = currentNode->right;
//                delete currentNode->info;
                delete currentNode;
                return retNode;
            }
            if (!currentNode->right) {
                retNode = currentNode->left;
//                delete currentNode->info;
                delete currentNode;
                return retNode;
            }
            if (currentNode->left && currentNode->right) {
                Node<T> *followingNode = this->findFollowingNode(currentNode);
                Node<T> *p = followingNode->parent;
                Node<T> *r = followingNode->right;

                followingNode->parent = currentNode->parent;
                followingNode->right = currentNode->right;
                followingNode->left = currentNode->left;

                currentNode->parent = p;
                currentNode->right = r;
                currentNode->left = nullptr;

                p->left = currentNode;
                followingNode->left->parent = followingNode;
                followingNode->right->parent = followingNode;

                currentNode = followingNode;

                currentNode->right = deleteNode(currentNode->right, key, currentNode->parent);
            }
        }

        currentNode = balanceNode(currentNode);
        currentNode->height = max(getHeight(currentNode->left), getHeight(currentNode->right)) + 1;

        return currentNode;
    }

    void preOrderIteration(Node<T> *subRoot, void (*do_something)(Node<T> *)) {
        if (!subRoot) { return; }
        do_something(subRoot);
        preOrderIteration(subRoot->left, do_something);
        preOrderIteration(subRoot->right, do_something);
    }

    void inOrderIteration(Node<T> *subRoot, void (*do_something)(Node<T> *)) {
        if (!subRoot) { return; }
        inOrderIteration(subRoot->left, do_something);
        do_something(subRoot);
        inOrderIteration(subRoot->right, do_something);
    }

    void postOrderIteration(Node<T> *subRoot, void (*do_something)(Node<T> *)) {
        if (!subRoot) { return; }
        postOrderIteration(subRoot->left, do_something);
        postOrderIteration(subRoot->right, do_something);
        do_something(subRoot);
    }
};


#endif //WET1_AVLTREE_H
