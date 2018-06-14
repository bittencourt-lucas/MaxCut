#include "MaxCut.hpp"
#define LIVES 5

int bestCut = 0;

void MaxCut::insert(int w, std::vector<bool> &U, std::vector<int> &wgtU,
                            std::vector<std::vector<Edge>>& adjList) {
    U[w] = true;
    for (auto e : adjList[w]) {
        int s = e.dest;
        if (U[s] || V[s]) continue;
        // Conta quantas arestas um vértice possui.
        wgtU[s] += e.weight;
        edges_queue.push(s);
    }
}

Best MaxCut::construct(int chosen, std::vector<std::vector<Edge>>& adjList,
                                std::vector<Edge>& edges) {
    int nEdges = edges.size();

    // Evitar problemas com lixo de memória.
    while (!edges_queue.empty()) edges_queue.pop();

    // Cria listas de n vértices com 0 ou falso nas listas.
    U.assign(nEdges, false);
    V.assign(nEdges, false);
    wgtU.assign(nEdges, 0);
    wgtV.assign(nEdges, 0);

    // Escolhe-se aleatoriamente o vértice para iniciar o corte.
    if (chosen == -1) {
        std::random_device generator;
        std::uniform_int_distribution<int> distribution(0, nEdges - 1);
        chosen = distribution(generator);
    }
    std::cout << "Edge: (" << edges[chosen].src << "," << edges[chosen].dest << "): ";
    Edge maxEdge = edges[chosen];

    int cut = maxEdge.weight;
    insert(maxEdge.src, U, wgtU, adjList);
    insert(maxEdge.dest, V, wgtV, adjList);

    while (!edges_queue.empty()) {
        int w = edges_queue.front();
        edges_queue.pop();
        if (U[w] || V[w]) continue;
        cut += max(wgtU[w], wgtV[w]);
        // O vértice contém mais arestas?
        wgtU[w] < wgtV[w] ? insert(w, U, wgtU, adjList) :
                                    insert(w, V, wgtV, adjList);
    }
    // Primeira solução.
    std::cout << "Cut: " << cut << std::endl;
    Best currBest;
    currBest.cutValue = cut;
    if (cut > bestCut) {
        bestCut = cut;
    }
    currBest.stEdge = chosen;
    return currBest;
}

void MaxCut::searchImprovement(Best currEdge, std::vector<std::vector<Edge>>& adjList,
                                std::vector<Edge>& edges) {
    bool isBest = false;
    int lives = LIVES;
    Best testBest;
    testBest.stEdge = 0;
    testBest.cutValue = 0;
    testBest.stEdge = currEdge.stEdge;
    int oldMax = currEdge.cutValue;
    while(!isBest) {
        testBest = construct(++testBest.stEdge, adjList, edges);
        if (testBest.cutValue < oldMax && lives == 0) {
            isBest = true;
            std::cout << "Best Cut: " << bestCut << std::endl;
        }
        if (testBest.cutValue < bestCut && lives > 0) {
            lives--;
        }
        else if (currEdge.stEdge == edges.size() - 1)
            break;
        else
            oldMax = testBest.cutValue;
    }
}
