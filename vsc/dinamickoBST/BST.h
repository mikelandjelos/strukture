#include <iostream>
#include <string>
#include <queue>
#include <stack>

template <typename T>
struct BSTNode {
public:
    T* info;
    BSTNode<T>* left;
    BSTNode<T>* right;

public:

    BSTNode(T info, BSTNode<T>* left = nullptr, BSTNode<T>* right = nullptr) 
        : info(new T(info)), left(left), right(right) {}
    BSTNode(T* info, BSTNode<T>* left = nullptr, BSTNode<T>* right = nullptr) 
        : info(info), left(left), right(right) {}
    virtual ~BSTNode() {
        if (info != nullptr)
            delete info;
        info = nullptr;
        left = nullptr;
        right = nullptr; 
    }

    template <typename K>
    friend bool operator==(const BSTNode<K>& ndl, const BSTNode<K>& ndr);
    template <typename K>
    friend bool operator>(const BSTNode<K>& ndl, const BSTNode<K>& ndr);
    template <typename K>
    friend bool operator>=(const BSTNode<K>& ndl, const BSTNode<K>& ndr);
    template <typename K>
    friend bool operator<(const BSTNode<K>& ndl, const BSTNode<K>& ndr);
    template <typename K>
    friend bool operator<=(const BSTNode<K>& ndl, const BSTNode<K>& ndr);

    template <typename K>
    friend bool operator==(const BSTNode<K>& ndl, const K& val);
    template <typename K>
    friend bool operator>(const BSTNode<K>& ndl, const K& val);
    template <typename K>
    friend bool operator>=(const BSTNode<K>& ndl, const K& val);
    template <typename K>
    friend bool operator<(const BSTNode<K>& ndl, const K& val);
    template <typename K>
    friend bool operator<=(const BSTNode<K>& ndl, const K& val);

    static void visit(BSTNode<T>* nd);
    static bool isInternal(BSTNode<T>* nd);
};

template <typename K>
bool operator==(const BSTNode<K>& ndl, const BSTNode<K>& ndr) {
    return *ndl.info == *ndr.info;
}

template <typename K>
bool operator>(const BSTNode<K>& ndl, const BSTNode<K>& ndr) {
    return *ndl.info > *ndr.info;
}

template <typename K>
bool operator>=(const BSTNode<K>& ndl, const BSTNode<K>& ndr) {
    return *ndl.info >= *ndr.info;
}

template <typename K>
bool operator<(const BSTNode<K>& ndl, const BSTNode<K>& ndr) {
    return *ndl.info < *ndr.info;
}

template <typename K>
bool operator<=(const BSTNode<K>& ndl, const BSTNode<K>& ndr) {
    return *ndl.info <= *ndr.info;
}

template <typename K>
bool operator==(const BSTNode<K>& ndl, const K& val) {
    return *ndl.info == val;
}

template <typename K>
bool operator>(const BSTNode<K>& ndl, const K& val) {
    return *ndl.info > val;
}

template <typename K>
bool operator>=(const BSTNode<K>& ndl, const K& val) {
    return *ndl.info >= val;
}

template <typename K>
bool operator<(const BSTNode<K>& ndl, const K& val) {
    return *ndl.info < val;
}

template <typename K>
bool operator<=(const BSTNode<K>& ndl, const K& val) {
    return *ndl.info <= val;
}

template <class T>
void BSTNode<T>::visit(BSTNode<T>* nd) {
    if (nd == nullptr)
        std::cout << "nullptr" << ' ';
    std::cout << *nd->info << ' ';
}

template <class T>
bool BSTNode<T>::isInternal(BSTNode<T>* nd) {
    if (nd == nullptr)
        return false;
    return 
        nd->left == nullptr && nd->right == nullptr;
} 

template <typename T>
class BSTree {
private:
    BSTNode<T>* root;
public:

    // destruktor, konstruktor
    BSTree(BSTNode<T>* root = nullptr) 
        : root(root) {}
    virtual ~BSTree();

    // osnovne operacije
    void addNode(T info);
    BSTNode<T>* findNode(T info);

    // traversal algoritmi
    int breadthTraversal();
    int preorder();
    int postorder();
    int inorder();
    static int iterativePreorder(BSTNode<T>* nd);
    static int iterativeInorder(BSTNode<T>* nd);

    // misc
    BSTNode<T>* getRoot() { return root; }
    BSTNode<T>* largestRightSubtree();

private:
    int deletion();
    void deletion(BSTNode<T>* nd, int& i);
    void preorder(BSTNode<T>* nd, int& i);
    void postorder(BSTNode<T>* nd, int& i);
    void inorder(BSTNode<T>* nd, int& i);
};

template <class T>
BSTNode<T>* BSTree<T>::largestRightSubtree() {
    BSTNode<T>* lrsnd = root, * ptr = root;
    int imax = 0;
    while (ptr != nullptr) {
        if (ptr->right == nullptr) {
            ptr = ptr->left;
            continue;
        }
        std::stack<BSTNode<T>*> stek;
        stek.push(ptr->right);
        BSTNode<T>* iptr = ptr->right;
        int i = 0;
        while (!stek.empty()) {
            i++; // visit
            iptr = stek.top();
            stek.pop();
            if (iptr->right != nullptr)
                stek.push(iptr->right);
            if (iptr->left != nullptr)
                stek.push(iptr->left);
        }
        if (i > imax) {
            lrsnd = ptr;
            imax = i;
        }
        ptr = ptr->left;
    }
    std::cout << "\n" << imax << "\n";
    return lrsnd;
}

template <class T>
int BSTree<T>::iterativePreorder(BSTNode<T>* nd) {
    int i = 0;
    if (nd == nullptr)
        return i;
    std::stack<BSTNode<T>*> stek;
    BSTNode<T>* ptr = nd;
    stek.push(ptr);
    while (!stek.empty()) {
        ptr = stek.top();
        stek.pop();
        BSTNode<T>::visit(ptr), i++;
        if (ptr->right != nullptr)
            stek.push(ptr->right);
        if (ptr->left != nullptr)
            stek.push(ptr->left);
    }
    return i;
}

template <class T>
int BSTree<T>::iterativeInorder(BSTNode<T>* nd) {
    int i = 0;
    BSTNode<T>* ptr = nd;
    std::stack<BSTNode<T>*> stek;
    while (ptr != nullptr) {
        // kretanje po krajnjem levom delu podstabla
        // koje trenutno obradjujemo i upisivanje
        // nd->right i nd na stek radi kasnije obrade
        while (ptr != nullptr) {
            if (ptr->right != nullptr)
                stek.push(ptr->right);
            stek.push(ptr);
            ptr = ptr->left;
        }
        // kada dodjemo do kraja naseg krajnjen levog puta
        // popujemo element sa vrha
        ptr = stek.top();
        stek.pop();
        while (!stek.empty() && ptr->right == nullptr) {
            // obradi element i iskoci iz petlje
            // ukoliko ima desno podstablo
            BSTNode<int>::visit(ptr), i++;
            ptr = stek.top();
            stek.pop();
        }
        BSTNode<int>::visit(ptr), i++;
        if (!stek.empty()) {
            ptr = stek.top();
            stek.pop();
        }
        else ptr = nullptr;
    } 
    return i;
}

template <class T>
void BSTree<T>::addNode(T info) {

    if (root == nullptr) {
        root = new BSTNode<T>(info);
        return;
    }

    BSTNode<T>* cnd = root, *pnd = nullptr;

    while (cnd != nullptr) {
        pnd = cnd;
        if (*cnd < info)
            cnd = cnd->right;
        else
            cnd = cnd->left;
    }

    if (*pnd < info)
        pnd->right = new BSTNode<T>(info);
    else
        pnd->left = new BSTNode<T>(info);

}

template <class T>
BSTNode<T>* BSTree<T>::findNode(T info) {

    BSTNode<T>* pok = root;

    while (pok != nullptr) {
        if (*pok == info)
            return pok;
        if (*pok < info)
            pok = pok->right;
        if (*pok > info)
            pok = pok->left;
    }

    return nullptr;
}

template <class T>
int BSTree<T>::breadthTraversal() {
    std::queue<BSTNode<T>*> q;
    int i = 0;
    BSTNode<T>* ptr = root;
    while (ptr != nullptr) {
        BSTNode<T>::visit(ptr);
        i++;
        if (ptr->left != nullptr)
            q.push(ptr->left);
        if (ptr->right != nullptr)
            q.push(ptr->right);
        if (!q.empty()) {
            ptr = q.front();
            q.pop();
        }
        else ptr = nullptr;
    }
    while (!q.empty()) {
        ptr = q.front();
        q.pop();
        if (ptr != nullptr) {
            BSTNode<T>::visit(ptr);
            i++;
        }
    }
    return i;
}

template <class T>
BSTree<T>::~BSTree() {
    std::clog << "Destruktor: " 
        << deletion() << "\n";
}

template <class T>
int BSTree<T>::deletion() {
    int i = 0;
    deletion(root, i);
    return i;
}

template <class T>
void BSTree<T>::deletion(BSTNode<T>* nd, int& i) {
    if (nd == nullptr)
        return;
    deletion(nd->left, i);
    deletion(nd->right, i);
    delete nd, i++;
}

template <class T>
int BSTree<T>::preorder() {
    int i = 0;
    preorder(root, i);
    return i;
}

template <class T>
void BSTree<T>::preorder(BSTNode<T>* nd, int& i) {
    if (nd == nullptr)
        return;
    BSTNode<T>::visit(nd), i++;
    preorder(nd->left, i);
    preorder(nd->right, i);
}

template <class T>
int BSTree<T>::postorder() {
    int i = 0;
    postorder(root, i);
    return i;
}

template <class T>
void BSTree<T>::postorder(BSTNode<T>* nd, int& i) {
    if (nd == nullptr)
        return;
    postorder(nd->left, i);
    postorder(nd->right, i);
    BSTNode<T>::visit(nd), i++;
}

template <class T>
int BSTree<T>::inorder() {
    int i = 0;
    inorder(root, i);
    return i;
}

template <class T>
void BSTree<T>::inorder(BSTNode<T>* nd, int& i) {
    if (nd == nullptr)
        return;
    inorder(nd->left, i);
    BSTNode<T>::visit(nd), i++;
    inorder(nd->right, i);
}

template <class T>
struct Trunk
{
    Trunk *prev;
    std::string str;
 
    Trunk(Trunk *prev, std::string str)
    {
        this->prev = prev;
        this->str = str;
    }
};
 
// Helper function to print branches of the binary tree
template <class T>
void showTrunks(Trunk<T> *p)
{
    if (p == nullptr) {
        return;
    }
 
    showTrunks(p->prev);
    std::cout << p->str;
}

template <class T>
void printTree(BSTNode<T>* root, Trunk<T> *prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }
 
    std::string prev_str = "    ";
    Trunk<T> *trunk = new Trunk<T>(prev, prev_str);
 
    printTree(root->right, trunk, true);
 
    if (!prev) {
        trunk->str = "———";
    }
    else if (isLeft)
    {
        trunk->str = ".———";
        prev_str = "   |";
    }
    else {
        trunk->str = "`———";
        prev->str = prev_str;
    }
 
    showTrunks(trunk);
    std::cout << " " << *root->info << std::endl;
 
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";
 
    printTree(root->left, trunk, false);
}