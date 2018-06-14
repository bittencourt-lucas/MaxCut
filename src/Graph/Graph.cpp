#include "Graph.hpp"
#include <iostream>

Graph::Graph(int vertNumber, int edgeNumber) {
    this->vertNumber = vertNumber;
    this->edgeNumber = edgeNumber;
}

void Graph::addEdge(int eSrc, int eDest, int eWgt) {
    edges.push_back({eSrc, eDest, eWgt});
}

void Graph::buildGraph() {
    adjList.resize(vertNumber + 1);

    // Para cada aresta
    for (auto edge : edges) {
        // Adiciona na posição [origem] da lista a aresta
        adjList[edge.src].push_back(edge);
        // Troca origem e destino
        swap(edge.src, edge.dest);
        // Adiciona na posição [destino] da lista a aresta de destino
        // Isso precisa acontecer porque o grafo é não-direcionado
        adjList[edge.src].push_back(edge);
    }
}

void Graph::swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}
