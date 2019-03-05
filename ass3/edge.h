//
// Created by SooYunKim on 11/2/18.
//

#ifndef ASS3_EDGE_H
#define ASS3_EDGE_H

#include <string>

class Edge {
public:
    /** empty constructor */
    Edge();

    /** constructor with label and weight */
    Edge(const std::string& end, int weight);

    /** return the vertex this edge connects to */
    std::string getEndVertex() const;

    /** return the weight of this edge */
    int getWeight() const;

private:
    friend class Graph;
    std::string endVertex{""};
    int edgeWeight{0};
};

#endif // ASS3_EDGE_H
