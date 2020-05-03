#include <iostream>
#include "AVLTreeNode.h"
#include "AVLTree.h"

typedef struct Node<int> t;

//void printKey(t *n){
//    std::cout << n->getKey() << ", ";
//}

int main() {
    int x = 0;
//    auto node = new t(1, 2, nullptr);
//    node->addLeftNode(2, 8);
//    node->getLeftNode()->addLeftNode(3, 35);
//    node->addRightNode(4, 76);
//    node->getRightNode()->addRightNode(7, 56);
//    node->getLeftNode()->addRightNode(5,2);
//    node->getLeftNode()->getRightNode()->addLeftNode(6,2);

//    node->postOrderIteration(printKey);

//    node = node->LR();
//    node = node->RightRot();
//    node = node->RL();
//
//    x = node->calcHeight();

////test 2 - copy ctor
//    t node(1, 2);
//    t node2(node);
//    node.setKey(3);

///test 3 - avl insertion
    auto *tree = new AVLTree<int>();
//    t y(1, 2);
//    tree->insertHelper(tree->getRoot(), y);
    auto *root = new t, *left = new t, *more_left = new t;

    root->key = 1;
    root->info = 1;
    root->height = 2;
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;

    left->key = 2;
    left->info = 2;
    left->height = 1;
    left->left = nullptr;
    left->right = nullptr;
    left->parent = root;

    more_left->key = 3;
    more_left->info = 3;
    more_left->height = 0;
    more_left->left = nullptr;
    more_left->right = nullptr;
    more_left->parent = left;





//    root = tree->LL(root);

//    tree->root = tree->insertEmptyNode(nullptr, 1);
//    tree->root = tree->insertEmptyNode(tree->root, 2);
//    tree->root = tree->insertEmptyNode(tree->root, 3);

    tree->root = tree->insertNode(tree->root, root);
    tree->root = tree->insertEmptyNode(tree->root, 5);
    tree->root = tree->insertEmptyNode(tree->root, 8);
    tree->root = tree->insertNode(tree->root, left);
    tree->root = tree->insertEmptyNode(tree->root, 4);
    tree->root = tree->insertNode(tree->root, more_left);
    tree->root = tree->insertEmptyNode(tree->root, 9);

    tree->root = tree->deleteNode(tree->root, 4);
    tree->root = tree->deleteNode(tree->root, 3);
    tree->root = tree->deleteNode(tree->root, 2);
    tree->root = tree->deleteNode(tree->root, 1);

//    Node<int> *testNode;
//    testNode = tree->getNodeByKey(3);
//    testNode = tree->getNodeByKey(8);


    std::cout << "node height = " << x << std::endl;
    return 0;

}