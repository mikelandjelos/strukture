#include "Graph.h"

// #define GRAPH_TESTING
// #define DELETION_TEST
// #define SEARCHING_TEST
// #define BFS_TEST
// #define DFS_TEST
// #define TOPOLOGICAL_TEST
#define FINDSHORTERPATH

int main() {

#ifdef GRAPH_TESTING

    Graph g;

    for (int i = 5; i > 0; --i)
        g.insertVertex(i);

    g.insertEdge(1, 2, 1);
    g.insertEdge(1, 3, 1);
    g.insertEdge(2, 4, 1);
    g.insertEdge(3, 4, 1);
    g.insertEdge(3, 5, 1);

    g.print();

#ifdef DELETION_TEST

    std::cout << (g.deleteEdge(3, 4) 
        ? "\ndeletion successful" : "\ndeletion unsuccessful");
    std::cout << (g.deleteEdge(3, 5) 
        ? "\ndeletion successful" : "\ndeletion unsuccessful");
    std::cout << (g.deleteEdge(3, 3) 
        ? "\ndeletion successful" : "\ndeletion unsuccessful");
    g.deleteVertex(4);

    std::cout << "\n";
    g.print();

#endif // !DELETION_TEST

#ifdef SEARCHING_TEST

    Vertex* foundV = g.findVertex(5);
    if (foundV != nullptr)
        std::cout << foundV->data << "\n";

    Edge* foundE = g.findEdge(1, 5);
    if (foundE != nullptr)
        std::cout << foundE->weight << "\n";

#endif // !SEARCHING_TEST

    Vertex* startVert;

#ifdef BFS_TEST

    startVert = g.findVertex(1);
    if (startVert) {
        std::cout << "\nBFS: ";
        int n = g.breadthTraversal(startVert->data);
        std::cout << "\nNodes visited: " << n;
    }

#endif // !BFS_TEST

#ifdef DFS_TEST

    startVert = g.findVertex(1);
    if (startVert) {
        std::cout << "\nDFS: ";
        int n = g.depthTraversal(startVert->data);
        std::cout << "\nNodes visited: " << n;
    }

#endif // !DFS_TEST

#ifdef TOPOLOGICAL_TEST

    std::cout << "\nTopological order: ";
    int n = g.topologicalOrderTraversal(true);
    std::cout << "\nNodes visited: " << n;
    std::cout << (g.isCyclic() ? "\nGraph is cyclic!\n" :
        "\nGraph is not cyclic!\n");

#endif // !TOPOLOGICAL_TEST

#endif // !GRAPH_TESTING

#ifdef FINDSHORTERPATH

    Graph fsp;

    fsp.insertVertex(7);
    fsp.insertVertex(15);
    fsp.insertVertex(2);
    fsp.insertVertex(1);
    fsp.insertVertex(6);
    fsp.insertVertex(12);
    fsp.insertVertex(8);
    fsp.insertVertex(13);

    fsp.insertEdge(1, 7, 1);
    fsp.insertEdge(7, 1, 1);
    fsp.insertEdge(7, 15, 1);
    fsp.insertEdge(7, 2, 1);
    fsp.insertEdge(2, 6, 1);
    fsp.insertEdge(2, 15, 1);
    fsp.insertEdge(15, 12, 1);
    // fsp.insertEdge(15, 7, 1);
    fsp.insertEdge(6, 8, 1);
    fsp.insertEdge(8, 12, 1);
    fsp.insertEdge(12, 13, 1);

    fsp.print();
    std::cout << "\n";
    fsp.findShorterPath(2, 13, 1);
    std::cout << "\n";

#endif // !FINDSHORTERPATH

    return 0;
    
}