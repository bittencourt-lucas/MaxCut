#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <vector>

typedef struct Edge {
    int src;
    int dest;
    int weight;
} Edge;

class Graph {

private:
    int vertNumber;
    int edgeNumber;
    void swap(int&, int&);

public:
    Graph(int, int);
    std::vector<Edge> edges;
    std::vector<std::vector<Edge>> adjList;
    void addEdge(int, int, int);
    void buildGraph();
    std::vector<Edge>& getEdges() { return this->edges; }
    std::vector<std::vector<Edge>>& getList() { return this->adjList; }


};

#endif /* GRAPH_HPP_ */
