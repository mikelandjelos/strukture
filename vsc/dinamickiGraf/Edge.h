#ifndef EDGE_H
#define EDGE_H

#include <iostream>

class LinkedNode;

class Edge {
public:
    LinkedNode* dest;
    Edge* link;
    int weight;

public:
    Edge(LinkedNode* _dest, Edge* _link = nullptr, int _weight = 1);
    virtual ~Edge();
};

#endif // !EDGE_H