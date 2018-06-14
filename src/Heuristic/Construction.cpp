#include "Construction.hpp"

void Construction::insert(int w, std::vector<bool> &U, std::vector<int> &wgtU,
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

void Construction::construct(std::vector<std::vector<Edge>>& adjList,
                                std::vector<Edge>& edges) {
    int nEdges = adjList.size();

    // Evitar problemas com lixo de memória.
    while (!score.empty()) score.pop();

    // Dá 0 pontos para todos os vértices.
    for (int i = 0; i < nEdges; i++)
        score.push(0);

    // Cria n vértices com 0 ou falso nas listas.
    U.assign(nEdges, 0);
    V.assign(nEdges, 0);
    wgtU.assign(nEdges, 0);
    wgtV.assign(nEdges, 0);

    // Escolhe-se o vértice para iniciar o corte
    Edge maxEdge = *std::max_element(edges.begin(), edges.end(),
        [](Edge a, Edge b) { return a.weight < b.weight; });

    int cut = maxEdge.weight;
    insert(maxEdge.src, U, wgtU, adjList);
    insert(maxEdge.dest, V, wgtV, adjList);

    while (!score.empty()) {
        int w = score.front();
        score.pop();
        if (U[w] || V[w]) continue;
        cut += max(wgtU[w], wgtV[w]);
        if (wgtU[w] < wgtV[w])
            insert(w, U, wgtU, adjList);
        else
            insert(w, V, wgtV, adjList);
    }
    std::cout << cut << std::endl;
}
