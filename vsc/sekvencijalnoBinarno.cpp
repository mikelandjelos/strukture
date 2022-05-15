#include <iostream>
#include <cstdlib>
#include <queue>
#include <ctime>

template <typename T>
struct Node {
public:
    T* info;
    Node<T>* left;
    Node<T>* right;
public:
    Node(T info, Node<T>* left = nullptr, Node<T>* right = nullptr) 
        : info(new T(info)), left(left), right(right) {}
    Node(T* info, Node<T>* left = nullptr, Node<T>* right = nullptr) 
        : info(info), left(left), right(right) {}
    virtual ~Node() {
        if (info != nullptr)
            delete info;
        info = nullptr;
        left = nullptr;
        right = nullptr; 
    }
    static bool visit(Node<T>* nd);
    static bool isInternal(Node<T>* nd);
};

template <class T>
bool Node<T>::visit(Node<T>* nd) {
    if (nd == nullptr)
        return false;
    std::cout << *nd->info;
    return true;
}

template <class T>
bool Node<T>::isInternal(Node<T>* nd) {
    if (nd == nullptr)
        return false;
    return 
        nd->left == nullptr && nd->right == nullptr;
} 

template <typename T>
class Tree {
private:
    Node<T>* root;
public:
    Tree(Node<T>* root = nullptr) 
        : root(root) {}
    virtual ~Tree();
    int breadthTraversal();
    int preorder();
    int postorder();
    int inorder();
private:
    int deletion();
    void deletion(Node<T>* nd, int& i);
    void preorder(Node<T>* nd, int& i);
    void postorder(Node<T>* nd, int& i);
    void inorder(Node<T>* nd, int& i);
};

template <class T>
int Tree<T>::breadthTraversal() {
    std::queue<Node<T>*> q;
    int i = 0;
    Node<T>* ptr = root;
    while (ptr != nullptr) {
        Node<T>::visit(ptr);
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
            Node<T>::visit(ptr);
            i++;
        }
    }
    return i;
}

template <class T>
Tree<T>::~Tree() {
    std::cout << "Destruktor: " 
        << deletion() << "\n";
}

template <class T>
int Tree<T>::deletion() {
    int i = 0;
    deletion(root, i);
    return i;
}

template <class T>
void Tree<T>::deletion(Node<T>* nd, int& i) {
    if (nd == nullptr)
        return;
    deletion(nd->left, i);
    deletion(nd->right, i);
    delete nd, i++;
}

template <class T>
int Tree<T>::preorder() {
    int i = 0;
    preorder(root, i);
    return i;
}

template <class T>
void Tree<T>::preorder(Node<T>* nd, int& i) {
    if (nd == nullptr)
        return;
    Node<T>::visit(nd), i++;
    preorder(nd->left, i);
    preorder(nd->right, i);
}

template <class T>
int Tree<T>::postorder() {
    int i = 0;
    postorder(root, i);
    return i;
}

template <class T>
void Tree<T>::postorder(Node<T>* nd, int& i) {
    if (nd == nullptr)
        return;
    postorder(nd->left, i);
    postorder(nd->right, i);
    Node<T>::visit(nd), i++;
}

template <class T>
int Tree<T>::inorder() {
    int i = 0;
    inorder(root, i);
    return i;
}

template <class T>
void Tree<T>::inorder(Node<T>* nd, int& i) {
    if (nd == nullptr)
        return;
    inorder(nd->left, i);
    Node<T>::visit(nd), i++;
    inorder(nd->right, i);
}

template <class T>
void printBT(const std::string& prefix, const Node<T>* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << *node->info << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

template <class T>
void printBT(const Node<T>* node)
{
    printBT("", node, false);    
}

/* Test primer za obilaske:

             a
           /   \
          b     c
         /\   /
        d e  f 
       /\  \  \
      g  h  i  j

*/

int main() {

    Node<char>* a = new Node<char>('a');
    Node<char>* b = new Node<char>('b');
    Node<char>* c = new Node<char>('c');
    Node<char>* d = new Node<char>('d');
    Node<char>* e = new Node<char>('e');
    Node<char>* f = new Node<char>('f');
    Node<char>* g = new Node<char>('g');
    Node<char>* h = new Node<char>('h');
    Node<char>* i = new Node<char>('i');
    Node<char>* j = new Node<char>('j');

    a->left = b;
    a->right = c;

    b->left = d;
    b->right = e;
    
    d->left = g;
    d->right = h;

    e->right = i;

    c->left = f;
    
    f->right = j;

    Tree<char> t(a);

    std::cout << "Preorder: ";
    int br = t.preorder();
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

    printBT(a);

    return 0;
}