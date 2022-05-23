#include "LinkedNode.h"
#include "Edge.h"

LinkedNode::LinkedNode(int* _node, LinkedNode* _next) 
    : node(new int(*_node)), adj(nullptr), next(_next),
     status(-1), dijPrev(nullptr) {}

LinkedNode::~LinkedNode() {
    // brisemo info deo
    if (node != nullptr)
        delete node;
    // brisemo listu adjacent-a
    while (adj != nullptr) {
        Edge* forDel = adj;
        adj = adj->link;
        delete forDel;
    }
    next = nullptr;
    status = -1;
    dijPrev = nullptr;
}

void LinkedNode::visit() const {
    std::cout << *node;
}

std::ostream& operator<<(std::ostream& ostr, const LinkedNode& _node) {
    return ostr << *_node.node;
}