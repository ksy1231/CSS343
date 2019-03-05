#include <utility>

//
// Created by SooYunKim on 11/2/18.
//

#include "vertex.h"
#include "edge.h"

/**
 * Creates an unvisited vertex and gives it a label
 * NOTE: A vertex must have a unique label that cannot be changed.
 * */
Vertex::Vertex(std::string label) : vertexLabel{std::move(label)} { }

/** @return  The label of this vertex. */
std::string Vertex::getLabel() const {
    return vertexLabel;
}

/** Marks this vertex as visited. */
void Vertex::visit() {
    visited = true;
}

/** Marks this vertex as not visited. */
void Vertex::unvisit() {
    visited = false;
}

/**
 * Returns the visited status of this vertex.
 * @return  True if the vertex has been visited, otherwise
 * returns false/
 * */
bool Vertex::isVisited() const {
    return visited;
}

/**
 * Adds an edge between this vertex and the given vertex.
 * Cannot have multiple connections to the same endVertex
 * Cannot connect back to itself
 * @return  True if the connection is successful.
 * */
bool Vertex::connect(const std::string &endVertex, const int edgeWeight) {
    if (adjacencyList.count(endVertex) > 0 || endVertex == this->getLabel()) {
        return false;
    } else {
        Edge newEdge(endVertex, edgeWeight);
        adjacencyList[endVertex] = newEdge;
        currentNeighbor = adjacencyList.begin();
        return true;
    }
}

/**
 * Removes the edge between this vertex and the given one.
 * @return  True if the removal is successful.
 * */
bool Vertex::disconnect(const std::string &endVertex) {
    auto itr = adjacencyList.find(endVertex);
    if (itr == adjacencyList.end())
        return false;
    adjacencyList.erase(endVertex);
    return true;
}

/**
 * Gets the weight of the edge between this vertex and the given vertex.
 * @return  The edge weight. This value is zero for an unweighted graph and
 * is negative if the .edge does not exist
 * */
int Vertex::getEdgeWeight(const std::string &endVertex) const {
    return adjacencyList.at(endVertex).getWeight();
}

/**
 * Calculates how many neighbors this vertex has.
 * @return  The number of the vertex's neighbors.
 * */
int Vertex::getNumberOfNeighbors() const {
    return static_cast<int>(adjacencyList.size());
}

/**
 * Sets current neighbor to first in adjacency list.
 * */
void Vertex::resetNeighbor() {
    currentNeighbor = adjacencyList.begin();
}

/**
 * Gets this vertex's next neighbor in the adjacency list.
 * Neighbors are automatically sorted alphabetically via map
 * Returns the vertex label if there are no more neighbors
 * @return  The label of the vertex's next neighbor.
 * */
std::string Vertex::getNextNeighbor() {
    if (currentNeighbor != adjacencyList.end()) {
        std::string next = currentNeighbor->second.getEndVertex();
        ++currentNeighbor;
        return next;
    } else {
        return getLabel();
    }
}

/**
 * Check whether the vertex exists in the adjacency list.
 * @return  True if  the vertex exists, otherwise
 * returns false/
 * */
bool Vertex::isDuplicate(const std::string toLebel) {
    for (auto &itr : adjacencyList) {
        if (itr.second.getEndVertex() == toLebel)
            return true;
    }
    return false;
}

/**
 * Sees whether this vertex is equal to another one.
 * Two vertices are equal if they have the same label.
 * */
bool Vertex::operator==(const Vertex &rightHandItem) const {
    return this->getLabel() == rightHandItem.getLabel();
}

/**
 * Sees whether this vertex is < another one.
 * Compares vertexLabel.
 * */
bool Vertex::operator<(const Vertex &rightHandItem) const {
    return this->getLabel() < rightHandItem.getLabel();
}
