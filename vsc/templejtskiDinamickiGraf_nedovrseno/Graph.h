#ifndef GRAPH_H
#define GRAPH_H

namespace template_graph {

    // T - info
    // W - weight

template <class T, class W>
class Edge;

template <class T, class W>
class Node {
    // class fields
public:
    T* node;            // node info
    Edge<T, W> * adj;   // adjacent nodes
    Node* next;         // next node (no physical meaning)
    int status;         // status for bfs/dfs/topological algos
    int indeg;          // number of edges going into the node
private:
    Node* dijkstraPrev; // dijkstra pathfinding

public:
    // constructors
    Node(T _node);
    // destructor
    virtual ~Node();
    // methods (public)

    // friends

private:
    // methods (private)
    void deleteEdges();
};

template <class T, class W>
Node<T, W>::Node(T _node) : node(new T(_node)), adj(nullptr),
        next(nullptr), status(-1) {}

template <class T, class W>
Node<T, W>::~Node() {
    
}


}

#endif // !GRAPH_H