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
    std::cout << "IPostorder: ";
    br = BSTree<int>::iterativePostorder(t.getRoot());
    std::cout << "(" << br << ")\n";
    std::cout << "Inorder: ";
    br = t.inorder();
    std::cout << "(" << br << ")\n";
    std::cout << "IInorder: ";
    br = BSTree<int>::iterativeInorder(t.getRoot());
    std::cout << "(" << br << ")\n";
    std::cout << "Breadth: ";
    br = t.breadthTraversal();
    std::cout << "(" << br << ")\n";

    Trunk<int>* null = nullptr;

    printTree(t.getRoot(), null, false);
    BSTNode<int>* ptr;
    

    //ptr = t.findNode(n);
    // if (ptr != nullptr)
    //     *ptr->info = 1024;

    // printTree(t.getRoot(), null, false);

    std::cout << "\nNajvece desno podstablo (broj cvorova & njegov koren):";
    ptr = t.largestRightSubtree();
    BSTNode<int>::visit(ptr);

    std::cout << "\nVisina: " << t.height() << "\n";
brisanje:
    // t.incrementWhole();
    // std::cout << "\nInkrementirano:\n";
    // printTree(t.getRoot(), null, false);
    // std::vector<int> inStr;
    // auto iter = inStr.begin();
    // for (; iter < inStr.end(); iter++)
    //     std::cout << *iter << " ";
    // std::cout << "\n";
    // t.nodeDepths();
    // std::cout << "Cvorova obrisano: " << t.deleteAllLeftLeafs() << "\n";
    // printTree(t.getRoot(), null, false);
    BSTNode<int>* bifNode = t.bifurcationNode();
    if (bifNode)
        std::cout << *bifNode->info << "\n";
    else
        std::cout << "bifNode not found\n";

    br = 0;
    int* arr = new int[t.nodeCount()];
    BSTree<int>::getSortedArray(t.getRoot(), arr, br);
    for (int i = 0; i < t.nodeCount(); ++i)
        std::cout <<  arr[i] << " ";

    std::cout << "\n";
    t.balance();
    printTree(t.getRoot(), null, false);
    // std::cout << "\nKoji cvor zelite da obrisete: ";
    // std::cin >> n;
    // std::cout << t.deleteNode(n) << "\n";

    // printTree(t.getRoot(), null, false);
    // std::cout << "IInorder: ";
    // br = BSTree<int>::iterativeInorder(t.getRoot());
    // std::cout << "(" << br << ")\n";

    // char ans;

    // std::cout << "Da li zelite da brisete jos cvorova(y/n): ";
    // std::cin >> ans;

    // if (ans == 'y')
    //     goto brisanje;

    return 0;
}