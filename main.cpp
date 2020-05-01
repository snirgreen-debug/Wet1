#include <iostream>
#include "AVLTreeNode.h"

typedef AVLTreeNode<int> t;

int main() {
    int x = 0;
    t node(1, 2, nullptr);
    node.addLeftNode(0, 8);

    x = node.calcBalance();

    std::cout << "node balance = " << x << std::endl;
    return 0;
}