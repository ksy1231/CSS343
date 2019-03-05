//
// Created by SooYunKim on 11/1/18.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <set>
#include <stack>
#include "graph.h"

using namespace std;

/** constructor, empty graph */
Graph::Graph() : numberOfEdges{0}, numberOfVertices{0} { }

/** destructor, delete all vertices and edges */
Graph::~Graph() {
    for (auto &vertice : vertices)
        delete vertice.second;
}

/** @return total number of vertices */
int Graph::NumberOfVertices() const {
    return numberOfVertices;
}

/** @return total number of edges */
int Graph::NumberOfEdges() const {
    return numberOfEdges;
}

/**
 * @param label
 * @return number of edges from given vertex, -1 if vertex not found
 * */
int Graph::NumberOfEdges(const std::string &label) const {
    if (vertices.find(label) != vertices.end())
        return vertices.at(label)->getNumberOfNeighbors();
    else
        return -1;
}

/**
 * Add a vertex to the graph, no duplicates allowed
 * @param label
 * @return true if vertex added, false if it already is in the graph
 * */
bool Graph::AddVertex(const std::string &label) {
    auto itr = vertices.find(label);
    if (itr == vertices.end()) {
        createVertex(label);
        return true;
    }
    return false;
}

/**
 * @param label
 * @return true if vertex is in the graph
 * */
bool Graph::HasVertex(const std::string &label) const {
    Vertex* v = findVertex(label);
    return v != nullptr;
}

/**
 * Get edges of the vertex in a readable format
 * such as b(10),c(20),d(40)
 * @param label
 * @return string representing edges and weights, "" if vertex not found
 * */
std::string Graph::GetEdges(const std::string &label) const {
    if (findVertex(label) == nullptr)
        return "";
    std::map<std::string, Edge, std::less<>> m =
            vertices.at(label)->adjacencyList;
    string str;
    for (const auto &pair : m) {
        str += pair.first + "(" + to_string(pair.second.getWeight()) + "),";
    }
    str = str.substr(0, str.length() - 1);
    return str;
}

/**
 * Add a new edge between start and end vertex
 * If the vertices do not exist, create them
 * A vertex cannot connect to itself
 * or have multiple edges to the same vertex
 * @param fromLabel
 * @param toLabel
 * @param edgeWeight optional, defaults to 0
 * @return true if successfully connected
 * */
bool Graph::Connect(const std::string &fromLabel, const std::string &toLabel,
        int edgeWeight) {
    if (fromLabel == toLabel) {
        return false;
    } else {
        if (!HasVertex(fromLabel))
            createVertex(fromLabel);
        if (!HasVertex(toLabel))
            createVertex(toLabel);
        if (!vertices.at(fromLabel)->isDuplicate(toLabel)) {
            vertices.at(fromLabel)->connect(vertices.at(toLabel)->getLabel(),
                    edgeWeight);
            ++numberOfEdges;
            return true;
        }
    }
    return false;
}

/**
 * Remove edge from graph
 * @param fromLabel starting vertex label
 * @param edge ending vertex label
 * @return true if edge successfully deleted
 * */
bool Graph::Disconnect(const std::string &fromLabel,
        const std::string &toLabel) {
    if (vertices.at(fromLabel)->disconnect(vertices.at(toLabel)->getLabel())) {
        numberOfEdges--;
        return true;
    }
    return false;
}

/**
 * Read edges from file
 * first line of file is an integer, indicating number of edges
 * each line represents an edge in the form of "string string int"
 * vertex labels cannot contain spaces
 * @param filename
 * @return true if file successfully read
 * */
bool Graph::ReadFile(const std::string &filename) {
    ifstream graphFile;
    graphFile.open(filename);
    int numEdge = 0;
    string start;
    string end;
    int weight = 0;
    if (graphFile.fail()){
        cerr << "Error opening file" << std::endl;
        return false;
    }
    if (graphFile >> numEdge){
        numberOfEdges = numEdge;
    }
    while (graphFile >> start >> end >> weight){
        Connect(start, end, weight);
    }
    graphFile.close();
    return true;
}

/**
 * depth-first traversal starting from given startLabel
 * @param startLabel starting vertex label
 * @param visit function to be called on each vertex label
 * */
void Graph::DFS(const std::string &startLabel,
        void (*visit)(const std::string &)) {
    if (HasVertex(startLabel)) {
        unvisitVertices();
        dfsHelper(findVertex(startLabel), visit);
    }
}

/** breadth-first traversal starting from startLabel
    call the function visit on each vertex label */
/**
 * breadth-first traversal starting from given startLabel
 * @param starting vertex label
 * @param function to be called on each vertex label
 * */
void Graph::BFS(const std::string &startLabel,
        void (*visit)(const std::string &)) {
    if (HasVertex(startLabel)) {
        unvisitVertices();
        bfsHelper(findVertex(startLabel), visit);
    }
}

/**
 * dijkstra's algorithm to find shortest distance to all other vertices
 * and the path to all other vertices
 * Path cost is recorded in the map passed in, e.g. weight["F"] = 10
 * How to get to vertex is recorded in map passed in, previous["F" = "C"
 * @param starting vertex label
 * @param map of <string, int> to record shortest path to vertex
 * @param map of <string, string> to record previous node in path to vertex
 * */
void Graph::Dijkstra(const std::string &startLabel,
        std::map<std::string, int> &weights,
        std::map<std::string, std::string> &previous) {
    this->unvisitVertices();
    string u = " ";
    string v = " ";
    int numOfNeighbors = vertices.at(startLabel)->getNumberOfNeighbors();
    int vNeighbors = 0;
    int v2ucost = 0;
    weights.clear();
    previous.clear();
    typedef pair<int, std::string> P;
    struct Order
    {
        bool operator()(P a, P b) const
        {
            return a.first > b.first;
        }
    };
    priority_queue<P, deque<P>, Order> pq;
    set<string> vertexSet;
    for (int i = 0; i < numOfNeighbors; i++) { // set initial weights
        u = vertices.at(startLabel)->getNextNeighbor();
        weights[u] = vertices.at(startLabel)->getEdgeWeight(u);
        previous[u] = startLabel;
        pq.push(P(weights[u], u));
    }
    vertexSet.insert((vertices.at(startLabel)->getLabel()));
    while (!pq.empty()) {
        v = pq.top().second; // lowest cost, first in priority queue
        vertexSet.insert((vertices.at(v)->getLabel()));
        pq.pop();
        if (vertexSet.find(v) != vertexSet.end()) {
            vNeighbors = vertices.at(v)->getNumberOfNeighbors();
            u = vertices.at(v)->getNextNeighbor();
            for (int k = 0; k < vNeighbors; k++) {
                if (vertexSet.count(u) > 0) {
                    u = vertices.at(v)->getNextNeighbor();
                    continue;
                }
                v2ucost = vertices.at(v)->getEdgeWeight(u);
                if (weights.find(u) == weights.end()) {
                    weights[u] = weights[v] + v2ucost;
                    previous[u] = v;
                    pq.push(P(weights[u], u));
                } else {
                    if (weights[u] > (weights[v] + v2ucost)) {
                        weights[u] = weights[v] + v2ucost;
                        previous[u] = v;
                        pq.push(P(weights[u], u));
                    }
                }
                u = vertices.at(v)->getNextNeighbor();
            }
        }
    }
}

/** mark all verticies as unvisited */
void Graph::unvisitVertices() {
    for (auto &vertice : vertices) {
        vertice.second->unvisit();
        vertice.second->resetNeighbor();
    }
}

/** helper for depthFirstTraversal */
void Graph::dfsHelper(Vertex *v, void (*visit)(const std::string &)) {
    v->visit();
    visit(v->getLabel());
    for (int i = 0; i < v->getNumberOfNeighbors(); i++){
        Vertex *n = findVertex(v->getNextNeighbor());
        if (!n->isVisited()){
            dfsHelper(n, visit);
        }
    }
}

/** helper for breadthFirstTraversal */
void Graph::bfsHelper(Vertex *v, void (*visit)(const std::string &)) {
    std::queue<Vertex*> vertexQueue;
    visit(v->getLabel());
    v->visit();
    vertexQueue.push(v);
    Vertex* vertexTrav = v;
    while (!vertexQueue.empty()) {
        vertexTrav = vertexQueue.front();
        while (vertexQueue.front() !=
        (vertexTrav = findVertex(vertexQueue.front()->getNextNeighbor()))) {
            if (!vertexTrav->isVisited()) {
                vertexQueue.push(vertexTrav);
                vertexTrav->visit();
            }
        }
        vertexQueue.pop();
        if (!vertexQueue.empty())
            visit(vertexQueue.front()->getLabel());
    }
    unvisitVertices();
}

/**
 * find vertex with given label
 * @param vertexLabel string as the vertex label
 * @return pointer to vetex or nullptr if not in graph
 */
Vertex *Graph::findVertex(const std::string &vertexLabel) const {
    if (vertices.find(vertexLabel) != vertices.end())
        return vertices.at(vertexLabel);
    else
        return nullptr;
}

/**
 * create a new vertex,
 * @param vertexLabel string as the vertex label
 * @return pointer to the newly created vertex
 */
Vertex *Graph::createVertex(const std::string &vertexLabel) {
    if (findVertex(vertexLabel) == nullptr) {
        Vertex* v = new Vertex(vertexLabel);
        vertices[vertexLabel] = v;
        vertices.at(v->getLabel())->resetNeighbor();
        numberOfVertices++;
        return v;
    }
    return findVertex(vertexLabel);
}
