#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>

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
    int numOfNodes;
public:

    // destruktor, konstruktor
    BSTree(BSTNode<T>* root = nullptr) 
        : root(root), numOfNodes(0) {}
    virtual ~BSTree();

    // osnovne operacije
    void addNode(T info);
    BSTNode<T>* findNode(T info);
    int height();
    int height(BSTNode<T>* nd);
    bool deleteNode(T info);
    void balance();
    void invertTree();

    // traversal algoritmi
    int breadthTraversal();
    void incrementWhole();
    int preorder();
    int postorder();
    int inorder();
    void nodeDepths();
    void nodeHeights();
    int massOfLeaves();
    int getDepth(T p);
    void getDepth(BSTNode<T>* nd, const T& val, bool& found, int& h, int i = 0);
    BSTNode<T>* getMinNode();
    void getMinNode(BSTNode<T>* nd, BSTNode<T>** minnd);
    BSTNode<T>* maxChildSum();
    int maxChildSum(BSTNode<T>* nd, BSTNode<T>** maxnd, int& maxsum);
    void xchgSpecificNodes(BSTNode<T>* nd);
    void rearrangeSpecificNodes(BSTNode<T>* nd, BSTNode<T>* parent);
    //void projectRight();
    static void balance(BSTree<T>& nd, T* arr, int left, int right);
    static int iterativePreorder(BSTNode<T>* nd);
    static int iterativeInorder(BSTNode<T>* nd);
    static int iterativePostorder(BSTNode<T>* nd);
    static void incrementTree(BSTNode<T>* nd);
    static void getSortedArray(BSTNode<T>* nd, T* arr = nullptr, int& i = 0);
    int deleteAllLeftLeafs();
    BSTNode<T>* bifurcationNode();
    static void deleteAllLeftLeaves(BSTNode<T>* root, BSTNode<T>* parent, int& i);
    static void bifurcationNode(BSTNode<T>* root, BSTNode<T>** bifNode, int& maxdiff);
    static void countNodes(BSTNode<T>* root, int& i);

    // misc
    BSTNode<T>* getRoot() { return root; }
    int nodeCount() { return numOfNodes; }
    BSTNode<T>* largestRightSubtree();

private:
    void invertTree(BSTNode<T>* nd);
    void massOfLeaves(BSTNode<T>* nd, int& m);
    void projectRight(BSTNode<T>* nd, int d);
    int deletion();
    void nodeDepths(BSTNode<T>* nd, int i);
    int nodeHeights(BSTNode<T>* nd);
    void deletion(BSTNode<T>* nd, int& i);
    void preorder(BSTNode<T>* nd, int& i);
    void postorder(BSTNode<T>* nd, int& i);
    void inorder(BSTNode<T>* nd, int& i);
};

// template <class T>
// void BSTree<T>::projectRight() {
//     int d = 0;
//     projectRight(nd)
// }

// template <class T>
// void BSTree<T>::projectRight(BSTNode<T>* nd, int d) {

// }

template <class T>
void BSTree<T>::xchgSpecificNodes(BSTNode<T>* nd) {
    rearrangeSpecificNodes(nd, nullptr);
}

template <class T>
void BSTree<T>::rearrangeSpecificNodes(BSTNode<T>* nd, BSTNode<T>* parent) {
    if (!nd) // ako smo stigli do dna
        return;
    // ako nd nema levo podstablo
    if (!nd->left)
        return;
    BSTNode<T>* lnd = nd->left;
    if (!lnd->right && !nd->right) {
        lnd->right = nd;
        nd->left = nullptr;
        if (!parent)
            root = lnd;
        else
            if (parent->left == nd)
                parent->left = lnd;
            else parent->right = lnd;
        rearrangeSpecificNodes(lnd->left, lnd);
        rearrangeSpecificNodes(lnd->right, lnd);
    }
    else {
        rearrangeSpecificNodes(nd->left, nd);
        rearrangeSpecificNodes(nd->right, nd);
    }
}

template <class T>
BSTNode<T>* BSTree<T>::getMinNode() {
    BSTNode<T>* minnd = nullptr;
    getMinNode(root, &minnd);
    return minnd;
}

template <class T>
void BSTree<T>::getMinNode(BSTNode<T>* nd, BSTNode<T>** minnd) {
    if (nd == nullptr)
        return;
    if (*minnd == nullptr || *nd->info < *(*minnd)->info)
        *minnd = nd;
    getMinNode(nd->left, minnd);
    getMinNode(nd->right, minnd);
}

template <class T>
BSTNode<T>* BSTree<T>::maxChildSum() {
    BSTNode<T>* maxnd = nullptr;
    int maxsum = 0;
    maxChildSum(root, &maxnd, maxsum);
    std::cout << "\nMaxsum = " << maxsum << "\n";
    return maxnd;
}

template <class T>
int BSTree<T>::maxChildSum(BSTNode<T>* nd, BSTNode<T>** maxnd, int& maxsum) {
    if (nd == nullptr)
        return 0;
    int childsum = 0;
    childsum += maxChildSum(nd->left, maxnd, maxsum);
    childsum += maxChildSum(nd->right, maxnd, maxsum);
    if (nd->left)
        childsum += *nd->left->info;
    if (nd->right)
        childsum += *nd->right->info;
    if (childsum > maxsum) {
        maxsum = childsum;
        *maxnd = nd;
    }
    return childsum;
}

template <class T>
int BSTree<T>::getDepth(T p) {
    bool found = false;
    int i = 1, h = -1;
    if (root == nullptr)
        return h;
    getDepth(root, p, found, h, 1);
    return h;
}

template <class T>
void BSTree<T>::getDepth(BSTNode<T>* nd, const T& val, bool& found, int& h, int i) {
    if (nd == nullptr || found)
        return;
    if (*nd->info == val) {
        h = i;
        found = true;
        return;
    }
    getDepth(nd->left, val, found, h, i + 1);
    getDepth(nd->right, val, found, h, i + 1);
}

template <class T>
void BSTree<T>::invertTree() {
    invertTree(root);
}

template <class T>
void BSTree<T>::invertTree(BSTNode<T>* nd) {
    if (nd == nullptr)
        return;
    BSTNode<T>* tmp = nd->left;
    nd->left = nd->right;
    nd->right = tmp;
    invertTree(nd->left);
    invertTree(nd->right);
}

template <class T>
int BSTree<T>::massOfLeaves() {
    int m = 0;
    BSTree<T>::massOfLeaves(root, m);
    return m;
}

template <class T>
void BSTree<T>::massOfLeaves(BSTNode<T>* nd, int& m) {
    if (nd == nullptr)
        return;
    if (!nd->left && !nd->right)
        m++;
    massOfLeaves(nd->left, m);
    massOfLeaves(nd->right, m);
}

template <class T>
void BSTree<T>::nodeHeights() {
    BSTree<T>::nodeHeights(root);
}

template <class T>
int BSTree<T>::nodeHeights(BSTNode<T>* nd) {
    if (nd == nullptr)
        return 0;
    int hl = nodeHeights(nd->left),
        hr = nodeHeights(nd->right);
    int h = 1 + ((hl > hr) ? hl : hr);
    std::cout << *nd->info << ": " << h << "\n";
    return h;
}

template <class T>
void BSTree<T>::balance() {
    T* arr = new T[numOfNodes];
    int i = 0;
    BSTree<T>::getSortedArray(root, arr, i);
    this->deletion();
    BSTree<T>::balance(*this, arr, 0, i);
    delete[] arr;
}

template <class T>
void BSTree<T>::balance(BSTree<T>& nd, T* arr, int left, int right) {
    if (left >= right)
        return;
    int s = (left + right) / 2;
    nd.addNode(arr[s]);
    BSTree<T>::balance(nd, arr, s + 1, right);
    BSTree<T>::balance(nd, arr, left, s);
}

template <class T>
void BSTree<T>::getSortedArray(BSTNode<T>* nd, T* arr, int& i) {
    if (nd == nullptr)
        return;
    getSortedArray(nd->left, arr, i);
    arr[i++] = *nd->info;
    getSortedArray(nd->right, arr, i);
}

template <class T>
BSTNode<T>* BSTree<T>::bifurcationNode() {
    int diff = 0;
    BSTNode<T>* maxNode = nullptr;
    BSTree<T>::bifurcationNode(root, &maxNode, diff);
    std::cout << "\nMaxDiff = " << diff << "\n";
    return maxNode;
}

template <class T>
void BSTree<T>::bifurcationNode(BSTNode<T>* root, BSTNode<T>** bifNode, int& maxdiff) {
    if (root == nullptr)
        return;
    int ileft = 0, iright = 0;
    BSTree<T>::countNodes(root->left, ileft);
    BSTree<T>::countNodes(root->right, iright);
    // diff = abs(iright - ileft);
    int diff = ((ileft > iright) ? ileft - iright : iright - ileft);
    if (diff >= maxdiff) {
        maxdiff = diff;
        *bifNode = root;
    }
    BSTree<T>::bifurcationNode(root->left, bifNode, maxdiff);
    BSTree<T>::bifurcationNode(root->right, bifNode, maxdiff);
}

template <class T>
void BSTree<T>::countNodes(BSTNode<T>* root, int& i) {
    if (root == nullptr)
        return;
    i++;
    countNodes(root->left, i);
    countNodes(root->right, i);
}

template <class T>
int BSTree<T>::deleteAllLeftLeafs() {
    int i = 0;
    BSTree<T>::deleteAllLeftLeaves(root, nullptr, i);
    return i;
}

template <class T>
void BSTree<T>::deleteAllLeftLeaves(BSTNode<T>* root, BSTNode<T>* parent, int& i) {
    if (parent == nullptr) {
        deleteAllLeftLeaves(root->left, root, i);
        deleteAllLeftLeaves(root->right, root, i);
    }
    if (root == nullptr)
        return;
    if (!root->left && !root->right && parent->left == root) {
        parent->left = nullptr;
        delete root;
        i++;
        return;
    }
    deleteAllLeftLeaves(root->left, root, i);
    deleteAllLeftLeaves(root->right, root, i);
}

template <class T>
void BSTree<T>::nodeDepths() {
    nodeDepths(root, 1);
}

template <class T>
void BSTree<T>::nodeDepths(BSTNode<T>* nd, int i) {
    if (nd == nullptr)
        return;
    nodeDepths(nd->left, i + 1);
    std::cout << *nd->info << ": " << i << "\n";
    nodeDepths(nd->right, i + 1);
}

template <class T>
void BSTree<T>::incrementTree(BSTNode<T>* nd) {
    if (nd == nullptr)
        return;
    ++*nd->info;
    incrementTree(nd->left);
    incrementTree(nd->right);
}

template <class T>
void BSTree<T>::incrementWhole() {
    BSTree<T>::incrementTree(root);
}

template <class T>
bool BSTree<T>::deleteNode(T info) {
    BSTNode<T>* parent = nullptr, *ptr = root, *node;
    while (ptr != nullptr && *ptr->info != info) {
        parent = ptr;
        if (*ptr > info)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    // nije nadjen
    if (ptr == nullptr)
        return false;
    
    node = ptr;

    bool isLeft;
    if (parent != nullptr)
        isLeft = node == parent->left;

    if (node->left == nullptr && node->right == nullptr) { // leaf
        if (node != root)
            if (*node < *parent)
                parent->left = nullptr;
            else
                parent->right = nullptr;
        else root = nullptr;
        delete node;
    }
    else if (node->left == nullptr) { // nema levog potomka
        if (node != root)
            if (isLeft)
                parent->left = node->right;
            else
                parent->right = node->right;
        else root = root->right;
        delete node;
    }
    else if (node->right == nullptr) { // nema desnog potomka
        if (node != root)
            if (isLeft)
                parent->left = node->left;
            else
                parent->right = node->left;
        else root = root->left;
        delete node;
    }
    else { // ima oba potomka

        parent = node, ptr = node->left;
        // trazimo krajnjeg desnog u levom
        // podstablu; on sigurno nece imati
        // desno podstablo
        while (ptr->right != nullptr) {
            parent = ptr;
            ptr = ptr->right;
        }
        delete node->info;
        node->info = new T(*ptr->info);
        // moze da se desi da je krajnji desni u levom
        // podstablu upravo nas node->left
        if (parent == node)
            parent->left = ptr->left;
        else
            // kopiramo sadrzaj ptr-a
            // u nas node
            parent->right = ptr->left;

    }
    numOfNodes--;
    return true;
}

template <class T>
int BSTree<T>::height() {
    return height(root);
}

template <class T>
int BSTree<T>::height(BSTNode<T>* nd) {
    if (nd == nullptr)
        return 0;
    int l = height(nd->left);
    int r = height(nd->right);
    return (l > r) ? l + 1 : r + 1;
}

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
int BSTree<T>::iterativePostorder(BSTNode<T>* nd) {
    int i = 0;
    std::stack<BSTNode<T>*> stek;
    BSTNode<T>* ptr = nd, * lastVisited = nullptr;
    while (ptr != nullptr) {
        for (; ptr->left != nullptr; ptr = ptr->left)
            stek.push(ptr);
        while (ptr != nullptr && (ptr->right == nullptr || ptr->right == lastVisited)) {
            BSTNode<T>::visit(ptr), i++;
            lastVisited = ptr;
            if (stek.empty())
                return i;
            ptr = stek.top();
            stek.pop();
        }
        stek.push(ptr);
        ptr = ptr->right;
    }
    return i;
}

template <class T>
void BSTree<T>::addNode(T info) {

    if (root == nullptr) {
        root = new BSTNode<T>(info);
        numOfNodes++;
        return;
    }

    BSTNode<T>* cnd = root, *pnd = nullptr;

    while (cnd != nullptr) {
        pnd = cnd;
        if (*cnd <= info)
            cnd = cnd->right;
        else
            cnd = cnd->left;
    }

    if (*pnd <= info)
        pnd->right = new BSTNode<T>(info);
    else
        pnd->left = new BSTNode<T>(info);
        
    numOfNodes++;

}

template <class T>
BSTNode<T>* BSTree<T>::findNode(T info) {

    BSTNode<T>* pok = root;

    while (pok != nullptr) {
        if (*pok == info)
            return pok;
        if (*pok < info)
            pok = pok->right;
        else
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
    root = nullptr;
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