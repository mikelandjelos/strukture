#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BST.h"

int main() {

    srand(time(NULL));

    int n;

    std::cout << "Koliko cvorova zelite u vasem BST-u: ";
    std::cin >> n;

    BSTree<int> t;

    std::cout << "\nDodavanje: ";
    for (int i  = 0; i < n; ++i) {
        int temp = rand() % 100 - 50;
        std::cout << temp << ' ';
        t.addNode(temp);
    }

    std::cout << "\nPreorder: ";
    int br = t.preorder();
    std::cout << "(" << br << ")\n";
    std::cout << "IPreorder: ";
    br = BSTree<int>::iterativePreorder(t.getRoot());
    std::cout << "(" << br << ")\n";
    std::cout << "Postorder: ";
    br = t.postorder();
    std::cout << "(" << br << ")\n";
    std::cout << "Inorder: ";
    br = t.inorder();
    std::cout << "(" << br << ")\n";
    std::cout << "Breadth: ";
    br = t.breadthTraversal();
    std::cout << "(" << br << ")\n";

    Trunk<int>* null = nullptr;

    printTree(t.getRoot(), null, false);

    std::cout << "\nKoji cvor zelite da izmenite: ";
    std::cin >> n;

    BSTNode<int>* ptr = t.findNode(n);
    *ptr->info = 1024;

    printTree(t.getRoot(), null, false);

    return 0;
}