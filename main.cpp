#include <iostream>
#include "AVLTree.h"
#include "AVLTreeImp.h"
#include "MusicManager.h"

//#include "LinkedList.h"

//typedef struct AVLNode<int*> t;
//    int x = 0;
//    treeTests();
//    listTests();
//auto *tree = new AVLTree<AVLTree<Song *> *>();
//auto *subTree = new AVLTree<Song*>(9);
//tree->root = tree->insertNode(tree->root, 2, subTree);
////    Song * a = new Song();
////    subTree->insertNode(subTree->root, 1, a);
//    subTree->root = subTree->completeTree(3);
//    x = 3;
//    subTree->cleanCompleteTree(x, subTree->root);
//    x = 0;
//    subTree->fillAVLTreeKeys(subTree->root, x);

//subTree->root = subTree->insertNode(subTree->root, 10, new Song);
//subTree->printInOrder(subTree->root);
//std::cout << subTree->smallestNode->key << std::endl;
//auto *removedNode = subTree->removeNode(0);
//subTree->printInOrder(subTree->root);
//std::cout << subTree->smallestNode->key << std::endl;
//subTree->root = subTree->deleteNode(subTree->root, 5);

//    subTree->root = subTree->insertNode(subTree->root, 2, new Song);
//    subTree->root = subTree->insertNode(subTree->root, 3, new Song);
////    subTree->root = subTree->insertEmptyNode(subTree->root, 4);
////    AVLNode<int *> *s = subTree->root->left;
////
//struct a{
//    int x;
//};
//a *b;
//b->x = 0;
//delete b;
//std::cout<<b->x;
//    delete subTree;
//using namespace std;
//struct node{
//    int key;
//    int *info;
//    node *l;
//    node *r;
//    node *p;
//    ~node(){
//        std::cout<<"destroy tmp node"<<std::endl;
//        cout << endl;
//        cout<<"delete info of key " << key << endl;
//        delete info;
//        cout << endl;
//        std::cout << "deleted info" << std::endl;
//        delete l;
//        std::cout<<"deleted left"<<std::endl;
//        delete r;
//        std::cout<<"deleted right"<<std::endl;
//    }
//};
//
//auto *n1 = new node;
//n1->key = 3;
//n1->info = new int(3);
//
//auto *n2 = new node;
//n2->key = 2;
//n2->info = new int(2);
//
//auto *n3 = new node;
//n3->key = 1;
//n3->info = new int(3);
//n2->l = n2->r=n3->l=n3->r=nullptr;
//n2->p = n3->p = n1;
//
//n1->l = n3;
//n1->r = n2;
//n1->p = nullptr;
//
//
//delete n1;


//struct Shtut{
//    int x;
////    ~Shtut(){
//        std::cout<<"destroy shtut"<<std::endl;
//    }
//};
//    auto *a = new Shtut;
//    a->x = 15;
////    auto b = subTree->root->left;
//
//    x = a->x;
//    auto c = new Shtut;
//    c->x=14;
//    delete c;
//    auto tmp = new int(4);
//    delete tmp;
//    delete subTree->root;
//    delete a;
//    auto removedNode = subTree->removeNode(2);
//
//
//subTree->printInOrder(subTree->root);
//std::cout << subTree->smallestNode->key << std::endl;
//
//delete removedNode;
//delete subTree;
//s
//void treeTests() {
/////test 3 - avl insertion
//    auto *tree = new AVLTree_old<int *>();
////    t y(1, 2);
////    tree->insertHelper(tree->getRoot(), y);
//    auto *root = new t, *left = new t, *more_left = new t;
//
//    root->key = 1;
//    root->info = new int(1);
//    root->height = 2;
//    root->left = nullptr;
//    root->right = nullptr;
//    root->parent = nullptr;
//
//    left->key = 2;
//    left->info = new int(2);
//    left->height = 1;
//    left->left = nullptr;
//    left->right = nullptr;
//    left->parent = root;
//
//    more_left->key = 3;
//    more_left->info = new int(3);
//    more_left->height = 0;
//    more_left->left = nullptr;
//    more_left->right = nullptr;
//    more_left->parent = left;
//
////    root = tree->LL(root);
//
//    tree->root = tree->insertPointerNode(tree->root, root);
//    tree->root = tree->insertEmptyNode(tree->root, 5);
//    tree->root = tree->insertEmptyNode(tree->root, 8);
//    tree->root = tree->insertPointerNode(tree->root, left);
//    tree->root = tree->insertEmptyNode(tree->root, 4);
//    tree->root = tree->insertPointerNode(tree->root, more_left);
//    tree->root = tree->insertEmptyNode(tree->root, 9);
//
//    AVLNode<int *> *s;
//    s = tree->getNodeByKey(4);
//    tree->root = tree->deleteNode(tree->root, 4);
//    tree->root = tree->deleteNode(tree->root, 3);
//    tree->root = tree->deleteNode(tree->root, 2);
//    tree->root = tree->deleteNode(tree->root, 1);
//
////    AVLNode<int> *testNode;
////    testNode = tree->getNodeByKey(3);
////    testNode = tree->getNodeByKey(8);
//}
//
//void listTests(){
//
/////test 1 - constructor.
//    auto *l = new LinkedList<int *>();
//
/////test 2 - insert nodes.
//    l->insertLast(1, new int(2));
//    l->insertFirst(2, new int(3));
//    l->insertFirst(3, new int(4));
////    l->insertFirst(4, 5);
////    l->insertFirst(5, 6);
////    l->insertLast(6, 7);
//
/////test 3.1 - getNodeByIndex.
//    LLNode<int *> *t;
//    t = l->getNodeByIndex(0);
//    t = l->getNodeByIndex(4);
//    t = l->getNodeByIndex(2);
//
/////test 3.2 - delete node.
//    l->deleteNodeByPointer(t);
//}
using namespace std;

int main() {
    int x = 0;
    auto *DS = new MusicManager();
    DS->addArtist(3, 5);
    DS->addArtist(5, 2);

    DS->addToSongCount(3, 0);
    DS->addToSongCount(3, 1);
    DS->addToSongCount(3, 3);
    DS->addToSongCount(3, 4);
    DS->addToSongCount(3, 0);
    DS->addToSongCount(3, 2);
    DS->addToSongCount(3, 0);
    DS->addToSongCount(3, 1);
    DS->addToSongCount(3, 3);
    DS->addToSongCount(3, 4);
    DS->addToSongCount(3, 0);

    DS->addToSongCount(5, 0);
    DS->addToSongCount(5, 0);
    DS->addToSongCount(5, 0);
    DS->addToSongCount(5, 0);
    DS->addToSongCount(5, 1);
    DS->addToSongCount(5, 1);


//    DS->addArtist(3, 4);
//    DS->addArtist(5, 2);

//    DS->addToSongCount(3, 0);
//    DS->addToSongCount(3, 0);
//    DS->addToSongCount(3, 0);
//
//    DS->addToSongCount(5, 0);
//    DS->addToSongCount(5, 0);
//    DS->addToSongCount(5, 0);
//    DS->addToSongCount(5, 0);
//    DS->addToSongCount(5, 1);
//    DS->addToSongCount(5, 1);


//    DS->numberOfStreams(3, 4, &x);
//
//    int songs[6];
//    int artists[6];
//
//    DS->getRecommendedSongs(6, artists, songs);

    DS->removeArtist(3);
    DS->removeArtist(5);

//    auto *xa = new AVLTree<AVLTree<Song *>*>();


//    cout << DS->streams->head->key;
//    cout << DS->artists->root->key;
//    cout << DS->artists->root->info;
    std::cout << "x = " << x << std::endl;
    delete DS;
    return 0;

}