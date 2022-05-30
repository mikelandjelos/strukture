#include "Graph.h"

// #define GRAPH_TESTING
// #define DELETION_TEST
// #define SEARCHING_TEST
// #define BFS_TEST
// #define DFS_TEST
// #define RECURSIVEDFS
// #define TOPOLOGICAL_TEST
// #define FINDSHORTERPATH
// #define FINDPATHBYPASSINGEDGE
// #define FINDCYCLEINCLUDINGVERTEX
#define FINDCYCLEINCLUDINGVERTICES

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

#ifdef FINDPATHBYPASSINGEDGE

    Graph fpbe;

    fpbe.insertVertex(7);
    fpbe.insertVertex(3);
    fpbe.insertVertex(1);
    fpbe.insertVertex(6);
    fpbe.insertVertex(2);
    fpbe.insertVertex(12);
    fpbe.insertVertex(5);
    fpbe.insertVertex(8);

    fpbe.insertEdge(7, 3, 1);
    fpbe.insertEdge(7, 1, 1);
    fpbe.insertEdge(3, 1, 1);
    fpbe.insertEdge(3, 6, 1);
    fpbe.insertEdge(1, 2, 1);
    fpbe.insertEdge(2, 6, 1);
    fpbe.insertEdge(2, 5, 1);
    fpbe.insertEdge(6, 5, 1);
    fpbe.insertEdge(5, 12, 1);
    fpbe.insertEdge(5, 8, 1);
    fpbe.insertEdge(12, 2, 1);
    fpbe.insertEdge(12, 8, 1);
    // fpbe.insertEdge(8, 12, 1);

    // put od 7 ka 8, zaobilazeci poteg 1 -> 2
    fpbe.findPathBypassingEdge(7, 12, 1, 2);

#endif // !FINDPATHBYPASSINGEDGE

#ifdef RECURSIVEDFS

    Graph traversals;

    for (int i = 1; i <= 12; ++i)
        traversals.insertVertex(i);

    traversals.insertEdge(1, 4, 1);
    traversals.insertEdge(1, 3, 1);
    traversals.insertEdge(1, 2, 1);
    traversals.insertEdge(2, 6, 1);
    traversals.insertEdge(2, 5, 1);
    traversals.insertEdge(3, 8, 1);
    traversals.insertEdge(3, 7, 1);
    traversals.insertEdge(4, 9, 1);
    traversals.insertEdge(5, 10, 1);
    traversals.insertEdge(6, 11, 1);
    traversals.insertEdge(6, 4, 1);
    traversals.insertEdge(9, 12, 1);
    traversals.insertEdge(4, 1, 1);

    std::cout << "\nBFS: ";
    traversals.breadthTraversal(1);
    std::cout << "\nDFS: ";
    traversals.depthTraversal(1);
    std::cout << "\nDFSr: ";
    traversals.depthTraversalRecursive(1);

#endif // !RECURSIVEDFS

#ifdef FINDCYCLEINCLUDINGVERTEX

    Graph fciv;

    fciv.insertVertex(1);
    fciv.insertVertex(12);
    fciv.insertVertex(7);
    fciv.insertVertex(2);
    fciv.insertVertex(8);
    fciv.insertVertex(3);
    fciv.insertVertex(6);

    fciv.insertEdge(1, 1, 1);
    fciv.insertEdge(1, 7, 1);
    fciv.insertEdge(7, 2, 1);
    fciv.insertEdge(7, 3, 1);
    fciv.insertEdge(2, 12, 1);
    fciv.insertEdge(3, 6, 1);
    fciv.insertEdge(8, 2, 1);
    fciv.insertEdge(6, 8, 1);
    fciv.insertEdge(12, 1, 1);

    std::cout << fciv.findCycleIncludingVertex(1);
    std::cout << "\n" << fciv.findCycleIncludingVertexIterative(1);

#endif // !FINDCYCLEINCLUDINGVERTEX

#ifdef FINDCYCLEINCLUDINGVERTICES

    Graph fcivs1;

    fcivs1.insertVertex(7);
    fcivs1.insertVertex(5);
    fcivs1.insertVertex(2);
    fcivs1.insertVertex(1);
    fcivs1.insertVertex(3);
    fcivs1.insertVertex(8);
    fcivs1.insertVertex(6);
    fcivs1.insertVertex(12);

    fcivs1.insertEdge(7, 2, 1);
    fcivs1.insertEdge(5, 7, 1);
    fcivs1.insertEdge(2, 1, 1);
    fcivs1.insertEdge(2, 3, 1);
    fcivs1.insertEdge(1, 5, 1);
    fcivs1.insertEdge(1, 8, 1);
    // fcivs1.insertEdge(3, 12, 1);
    fcivs1.insertEdge(8, 12, 1);
    fcivs1.insertEdge(12, 6, 1);
    fcivs1.insertEdge(6, 8, 1);
    fcivs1.insertEdge(6, 5, 1);
    // fcivs1.insertEdge(1, 12, 1);

    int lenfcivs = fcivs1.findCycleIncludingVertices(8, 12);
    std::cout << "\nCycle len: " << lenfcivs;

#endif // !FINDCYCLEINCLUDINGVERTICES

    return 0;
    
}