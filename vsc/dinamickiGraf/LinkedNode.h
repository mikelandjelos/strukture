#ifndef LINKEDNODE_H
#define LINKEDNODE_H

#include <iostream>

class Edge;

class LinkedNode {
    // class fields
public:
    int* node;
    Edge* adj;
    LinkedNode* next;
    int status;
private:
    LinkedNode* dijPrev;

public:
    // c&d
    LinkedNode(int* _node = nullptr, LinkedNode* _next = nullptr);
    virtual ~LinkedNode();

    // methods
    void visit() const;

    // friends
    friend std::ostream& operator<<(std::ostream& ostr, const LinkedNode& _node);

};

#endif // !LINKEDNODE_H