#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <stack>
#include <queue>

class Vertex;

class Edge {
public:
    int weight;
    Edge* link;
    Vertex* dest;
public:

    Edge() 
        : weight(0), link(0), dest(0) {}
    Edge(int _weight, Vertex* _dest, Edge* _link)
        : weight(_weight), link(_link), dest(_dest) {}
    virtual ~Edge() {
        weight = 0;
        link = nullptr;
        dest = nullptr;
    }

};

class Vertex {
public:
    int data;
    Vertex* next;
    Edge* adj;
    int status;
    // unprocessed  == 0
    // processing   == 1
    // processed    == 2
private:
    Vertex* prev;
    int indeg;

public:

    Vertex() 
        : status(0), next(nullptr), 
        adj(nullptr), prev(nullptr), indeg(0) {}
    Vertex(int _data, Vertex* _next = nullptr) 
        : data(_data), next(_next), status(0),
        adj(nullptr), prev(nullptr), indeg(0) {}
    virtual ~Vertex() {
        data = 0;
        indeg = 0;
        next = nullptr;
        while (adj != nullptr) {
            Edge* forDel = adj;
            adj = adj->link;
            delete forDel;
        }
        prev = nullptr;
        status = 0;
    }

    friend std::ostream& operator<<(std::ostream& _ostr, const Vertex& _vert);
    void visit() {
        std::cout << *this << " ";
    }

    friend class Graph;

};

std::ostream& operator<<(std::ostream& _ostr, const Vertex& _vert) {
    return _ostr << _vert.data;
}

class Graph {
private:
    Vertex* vertices;
    unsigned int numOfNodes;

public:

    Graph();
    virtual ~Graph();

    Vertex* findVertex(int _data);
    Edge* findEdge(int _dataA, int _dataB);
    void insertVertex(int _data);
    bool deleteVertex(int _data);
    bool insertEdge(int _dataA, int _dataB, int _weight = 1);
    bool deleteEdge(int _dataA, int _dataB);
    unsigned int breadthTraversal(int _start);
    unsigned int depthTraversal(int _start);
    unsigned int topologicalOrderTraversal(bool _visit = false);
    bool isCyclic();
    void print() const;
    friend std::ostream& operator<<(std::ostream& _out, const Graph& _graph);

private:
    void deleteEdgesToVertex(Vertex* _vertex);
    void findNodes(Vertex** ptrA, Vertex** ptrB, int _dataA, int _dataB);
    void statusReset();
    void previousReset();

public:
    // zadaci
    unsigned int findShorterPath(int _start, int _frst, int _scnd);

};

Graph::Graph()
    : vertices(nullptr), numOfNodes(0) {}

Graph::~Graph() {
    while (vertices != nullptr) {
        Vertex* forDel = vertices;
        vertices = vertices->next;
        delete forDel;
    }
    numOfNodes = 0;
}

Vertex* Graph::findVertex(int _data) {
    Vertex* ptr = vertices;
    while (ptr != nullptr) {
        if (ptr->data == _data)
            break;
        ptr = ptr->next;
    }
    return ptr;
}

void Graph::findNodes(Vertex** ptrA, Vertex** ptrB,
     int _dataA, int _dataB) {
    *ptrA = nullptr, *ptrB = nullptr;
    Vertex* temp = vertices;
    while (temp != nullptr) {
        if (temp->data == _dataA &&
            *ptrA == nullptr)
            *ptrA = temp;
        if (temp->data == _dataB &&
            *ptrB == nullptr)
            *ptrB = temp;
        if (*ptrA != nullptr && *ptrB != nullptr)
            break;
        temp = temp->next;
    }
}

Edge* Graph::findEdge(int _dataA, int _dataB) {
    Vertex* ptrA = nullptr, * ptrB = nullptr;
    Vertex* temp = vertices;
    findNodes(&ptrA, &ptrB, _dataA, _dataB);
    if (ptrA == nullptr || ptrB == nullptr)
        return nullptr;
    Edge* ret = ptrA->adj;
    while (ret != nullptr) {
        if (ret->dest == ptrB)
            break;
        ret = ret->link;
    }
    return ret;
}

void Graph::insertVertex(int _data) {
    Vertex* newVertex = new Vertex(_data, vertices);
    vertices = newVertex;
}

void Graph::deleteEdgesToVertex(Vertex* _vertex) {
    Vertex* tmp = vertices;
    while (tmp != nullptr) {
        Edge* tmpEdge = tmp->adj, *tmpEdgePrev = nullptr;
        while (tmpEdge != nullptr) {
            if (tmpEdge->dest == _vertex) {
                Edge* forDel = tmpEdge;
                if (tmpEdgePrev != nullptr)
                    tmpEdgePrev->link = tmpEdge->link;
                else
                    tmp->adj = tmp->adj->link;
                tmpEdge = tmpEdge->link;
                tmp->indeg--;
                delete forDel;
            }
            else {
                tmpEdgePrev = tmpEdge;
                tmpEdge = tmpEdge->link;
            }
        }
        tmp = tmp->next;
    }
}

bool Graph::deleteVertex(int _data) {
    Vertex* temp = vertices, *tempPrev = nullptr;
    while (temp != nullptr) {
        if (temp->data == _data) {
            if (tempPrev != nullptr)
                tempPrev->next = temp->next;
            else
                vertices = vertices->next;
            deleteEdgesToVertex(temp);
            delete temp;
            return true;
        }
        tempPrev = temp;
        temp = temp->next;
    }
    return false;
}

bool Graph::insertEdge(int _dataA, int _dataB, int _weight) {
    Vertex* ptrA = nullptr, * ptrB = nullptr;
    Vertex* temp = vertices;
    findNodes(&ptrA, &ptrB, _dataA, _dataB);
    if (ptrA == nullptr || ptrB == nullptr)
        return false;
    Edge* newEdge = new Edge(_weight, ptrB, ptrA->adj);
    ptrB->indeg++;
    ptrA->adj = newEdge;
    return true;
}

bool Graph::deleteEdge(int _dataA, int _dataB) {
    Vertex* ptrA = nullptr, * ptrB = nullptr;
    findNodes(&ptrA, &ptrB, _dataA, _dataB);
    if (ptrA == nullptr || ptrB == nullptr)
        return false;
    Edge* temp = ptrA->adj, *tempPrev = nullptr;
    while (temp != nullptr) {
        if (temp->dest == ptrB) {
            if (tempPrev != nullptr)
                tempPrev->link = temp->link;
            else
                ptrA->adj = ptrA->adj->link;
            ptrB->indeg--;
            delete temp;
            return true;
        }
        tempPrev = temp;
        temp = temp->link;
    }
    return false;
}

std::ostream& operator<<(std::ostream& _out, const Graph& _graph) {
    Vertex* tmp = _graph.vertices;
    while (tmp != nullptr) {
        Edge* tmpEdge = tmp->adj;
        _out << tmp->data << " { ";
        while (tmpEdge != nullptr) {
            if (tmpEdge->link != nullptr)
                _out << tmpEdge->dest->data << " | ";
            else
                _out << tmpEdge->dest->data << " ";
            tmpEdge = tmpEdge->link;
        }
        _out << "}\n";
        tmp = tmp->next;
    }
    return _out;
}

void Graph::print() const {
    std::cout << *this;
}

void Graph::statusReset() {
    Vertex* tmp = vertices;
    while (tmp != nullptr) {
        tmp->status = 0; // status == 0 => vertex unprocessed
        tmp = tmp->next;
    }
}

unsigned int Graph::breadthTraversal(int _start) {
    Vertex* _tmpVert = findVertex(_start);
    if (!_tmpVert)
        return 0U;
    statusReset();
    unsigned int numVisited = 0U;
    std::queue<Vertex*> q;
    q.push(_tmpVert);
    _tmpVert->status = 1; // processing
    while (!q.empty()) {
        _tmpVert = q.front();
        q.pop();
        _tmpVert->status = 2; // processed
        _tmpVert->visit();
        numVisited++;
        Edge* _tmpAdj = _tmpVert->adj;
        while (_tmpAdj != nullptr) {
            if (_tmpAdj->dest->status == 0) // only unprocessed
                q.push(_tmpAdj->dest),
                _tmpAdj->dest->status = 1;  // are getting processed
            _tmpAdj = _tmpAdj->link;
        }
    }
    return numVisited;
}

unsigned int Graph::depthTraversal(int _start) {
    Vertex* _tmpVert = findVertex(_start);
    if (!_tmpVert)
        return 0U;
    statusReset();
    unsigned int numVisited = 0U;
    std::stack<Vertex*> s;
    s.push(_tmpVert);
    _tmpVert->status = 1; // processing
    while (!s.empty()) {
        _tmpVert = s.top();
        s.pop();
        _tmpVert->status = 2; // processed
        _tmpVert->visit();
        numVisited++;
        Edge* _tmpAdj = _tmpVert->adj;
        while (_tmpAdj != nullptr) {
            if (_tmpAdj->dest->status == 0) // only unprocessed
                s.push(_tmpAdj->dest),
                _tmpAdj->dest->status = 1;  // are getting processed
            _tmpAdj = _tmpAdj->link;
        }
    }
    return numVisited;
}

unsigned int Graph::topologicalOrderTraversal(bool _visit) {
    int numVisited = 0U;
    Vertex* _tmpVert = vertices;
    std::queue<Vertex*> q;
    while (_tmpVert != nullptr) {
        _tmpVert->status = _tmpVert->indeg;
        if (_tmpVert->indeg == 0)
            q.push(_tmpVert);
        _tmpVert = _tmpVert->next;
    }
    while (!q.empty()) {
        _tmpVert = q.front();
        q.pop();
        if (_visit)
            _tmpVert->visit();
        numVisited++;
        Edge* _tmpAdj = _tmpVert->adj;
        while (_tmpAdj != nullptr) {
            _tmpAdj->dest->status--;
            if (_tmpAdj->dest->status == 0)
                q.push(_tmpAdj->dest);
            _tmpAdj = _tmpAdj->link;
        }
    }
    return numVisited;
}

bool Graph::isCyclic() {
    return numOfNodes == topologicalOrderTraversal();
}

void Graph::previousReset() {
    Vertex* ptr = vertices;
    while (ptr != nullptr) {
        ptr->prev = nullptr;
        ptr = ptr->next;
    }
}

// do ovde je standard struktura
// odavde pocinju zadaci

unsigned int Graph::findShorterPath(int _start, int _frst, int _scnd) {

    Vertex* _tmpVert = vertices;
    Vertex* _startVert = nullptr, 
        * _frstVert = nullptr, 
        * _scndVert = nullptr;
    while (_tmpVert != nullptr) {
        if (_startVert == nullptr && _tmpVert->data == _start)
            _startVert = _tmpVert;
        if (_frstVert == nullptr && _tmpVert->data == _frst)
            _frstVert = _tmpVert;
        if (_scndVert == nullptr && _tmpVert->data == _scnd)
            _scndVert = _tmpVert;
        _tmpVert->prev = nullptr;
        _tmpVert->status = 0;
        _tmpVert = _tmpVert->next;
    }

    if (!_startVert)
        return ~0U;
    bool found = false;
    std::queue<Vertex*> q;
    q.push(_startVert);
    _startVert->status = 1; // processing
    while (!q.empty()) {
        _tmpVert = q.front();
        q.pop();
        _tmpVert->status = 2; // processed
        if (_frstVert != nullptr && 
            _tmpVert->data == _frstVert->data) {
            found = true;
            break;
        }
        if (_scndVert != nullptr && 
            _tmpVert->data == _scndVert->data) {
            found = true;
            break;
        }
        Edge* _tmpAdj = _tmpVert->adj;
        while (_tmpAdj != nullptr) {
            if (_tmpAdj->dest->status == 0)
                q.push(_tmpAdj->dest),
                    _tmpAdj->dest->status = 1,
                    _tmpAdj->dest->prev = _tmpVert;
            _tmpAdj = _tmpAdj->link;
        }
    }
    
    if (!found)
        return ~0U;

    int pathLen = ~0U; // ponasa se kao -1

    std::stack<Vertex*> s;
    while (_tmpVert != nullptr) {
        s.push(_tmpVert);
        _tmpVert = _tmpVert->prev;
        pathLen++;
    }

    while (!s.empty()) {
        _tmpVert = s.top();
        s.pop();
        _tmpVert->visit();
    }

    return pathLen;

}

#endif // !GRAPH_H