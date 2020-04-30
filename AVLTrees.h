//
// Created by Manors-PC on 4/29/2020.
//

#ifndef WET1_AVLTREES_H
#define WET1_AVLTREES_H
template <class T>
class node
{
    T *data;
    node *leftSon
    node *rightSon
};


class AVLTree
{
    T *data;

    public:
    AVLTree();
    AVLTree(const AVLTree&);
    ~AVLTree();
   bool insert(const T& element);
   T& find (const T& element);
   bool destroy (const T& element);

};

#endif //WET1_AVLTREES_H
