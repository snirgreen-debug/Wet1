#include <iostream>
#include "AVLTree.h"
#include "LinkedList.h"

typedef struct AVLNode<int> t;

void treeTests() {
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

    tree->root = tree->insertPointerNode(tree->root, root);
    tree->root = tree->insertEmptyNode(tree->root, 5);
    tree->root = tree->insertEmptyNode(tree->root, 8);
    tree->root = tree->insertPointerNode(tree->root, left);
    tree->root = tree->insertEmptyNode(tree->root, 4);
    tree->root = tree->insertPointerNode(tree->root, more_left);
    tree->root = tree->insertEmptyNode(tree->root, 9);

    tree->root = tree->deleteNode(tree->root, 4);
    tree->root = tree->deleteNode(tree->root, 3);
    tree->root = tree->deleteNode(tree->root, 2);
    tree->root = tree->deleteNode(tree->root, 1);

//    AVLNode<int> *testNode;
//    testNode = tree->getNodeByKey(3);
//    testNode = tree->getNodeByKey(8);
}

void listTests(){

///test 1 - constructor.
    auto *l = new LinkedList<int>();

///test 2 - insert nodes.
    l->insertLast(1, 2);
    l->insertFirst(2, 3);
    l->insertFirst(3, 4);
//    l->insertFirst(4, 5);
//    l->insertFirst(5, 6);
//    l->insertLast(6, 7);

///test 3.1 - getNodeByIndex.
    Node<int> *t;
    t = l->getNodeByIndex(0);
    t = l->getNodeByIndex(4);
    t = l->getNodeByIndex(2);

///test 3.2 - delete node.
    l->deleteNodeByPointer(t);
}

int main() {
    int x = 0;
//    treeTests();
//    listTests();


    std::cout << "node height = " << x << std::endl;
    return 0;

}