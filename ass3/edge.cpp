//
// Created by SooYunKim on 11/2/18.
//

#include "edge.h"

/** empty constructor */
Edge::Edge() = default;

/** constructor with label and weight */
Edge::Edge(const std::string &end, int weight)
: endVertex{end}, edgeWeight{weight} { }

/** return the vertex this edge connects to */
std::string Edge::getEndVertex() const {
    return endVertex;
}

/** return the weight of this edge */
int Edge::getWeight() const {
    return edgeWeight;
}
