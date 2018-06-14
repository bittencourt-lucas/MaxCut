#include "MaxCut.hpp"

void MaxCut::insert(int w, std::vector<bool> &U, std::vector<int> &wgtU,
                            std::vector<std::vector<Edge>>& adjList) {
    U[w] = true;
    // Percorre as arestas
    for (auto e : adjList[w]) {
        int s = e.dest;
        if (U[s] || V[s]) continue;
        // Somando pesos.
        wgtU[s] += e.weight;
        score.push(s);
    }
}

void MaxCut::construct(std::vector<std::vector<Edge>>& adjList,
                                std::vector<Edge>& edges) {
    int nEdges = adjList.size();

    // Evitar problemas com lixo de memória.
    while (!score.empty()) score.pop();

    // Dá 0 pontos para todos os vértices.
    for (int i = 0; i < nEdges; i++)
        score.push(0);

    // Cria n vértices com 0 ou falso nas listas.
    U.assign(nEdges, false);
    V.assign(nEdges, false);
    wgtU.assign(nEdges, 0);
    wgtV.assign(nEdges, 0);

    // Escolhe-se aleatoriamente o vértice para iniciar o corte.
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(0, nEdges - 1);
    int chosen = distribution(generator);
    std::cout << "Starting Vertex: #" << chosen << std::endl;
    Edge maxEdge = edges[chosen];

    int cut = maxEdge.weight;
    insert(maxEdge.src, U, wgtU, adjList);
    insert(maxEdge.dest, V, wgtV, adjList);

    while (!score.empty()) {
        int w = score.front();
        score.pop();
        if (U[w] || V[w]) continue;
        cut += max(wgtU[w], wgtV[w]);

        wgtU[w] < wgtV[w] ? insert(w, U, wgtU, adjList) :
                                    insert(w, V, wgtV, adjList);
        //std::cout << "U[w]=" << U[w] << " V[w]=" << V[w] << std::endl;
    }
    std::cout << cut << std::endl;
}
