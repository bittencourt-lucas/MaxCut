#include "MaxCut.hpp"

void MaxCut::insert(int w, std::vector<bool> &W, std::vector<int> &wgtW,
                            std::vector<std::vector<Edge>>& adjList) {
    // Envia o vértice para um dos subconjuntos.
    W[w] = true;
    // Para cada aresta que pertence ao meu vértice...
    for (auto e : adjList[w]) {
        int s = e.dest;
        // Soma 1 ao peso dos vértices de destino válidos.
        wgtW[s] += e.weight;
        //std::cout << "Peso associado ao vértice " << s << ": " << wgtW[s] << std::endl;
        // Adiciona o vértice destino à minha lista de arestas.
        edges_queue.push(s);
    }
}

int MaxCut::construct(std::vector<std::vector<Edge>>& adjList,
                                std::vector<Edge>& edges) {
    // Número total de arestas.
    int nVertices = adjList.size();

    // Evitar problemas com lixo de memória.
    while (!edges_queue.empty()) edges_queue.pop();

    // Cria listas de n vértices com 0 ou falso nas listas.
    U.assign(nVertices, false);
    V.assign(nVertices, false);
    wgtU.assign(nVertices, 0);
    wgtV.assign(nVertices, 0);

    // Escolhe-se aleatoriamente o vértice para iniciar o corte.
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(0, edges.size() - 1);
    int chosen = distribution(generator);

    Edge maxEdge = edges[chosen];

    int cut = maxEdge.weight;
    //std::cout << "Peso inicial: " << cut << std::endl;
    //std::cout << "Inserindo Vértice: " << maxEdge.src << std::endl;
    insert(maxEdge.src, U, wgtU, adjList);
    //std::cout << "Inserindo Vértice: " << maxEdge.dest << std::endl;
    insert(maxEdge.dest, V, wgtV, adjList);

    while (!edges_queue.empty()) {
        int w = edges_queue.front();
        edges_queue.pop();
        if (U[w] || V[w]) continue;
       // std::cout << "Inserindo Vértice: " << w << std::endl;
        cut += max(wgtU[w], wgtV[w]);
        // O vértice contém mais arestas?
        wgtU[w] < wgtV[w] ? insert(w, U, wgtU, adjList) : insert(w, V, wgtV, adjList);
    }
    // Primeira solução.
    /*std::cout << "Vértices que fazem parte do corte: " << std::endl;
    for (int i = 0; i < U.size(); i++) {
        if (U[i])
            std::cout << "Vértice " << i << std::endl;
    }*/
    std::cout << "Corte: " << cut << std::endl;
    VND(adjList, U, 10, cut);
    return cut;
}

void MaxCut::VND(std::vector<std::vector<Edge>>& adjList, std::vector<bool> &U, int r, int firstCut) {
    int k = 1;
    int vertices = U.size();
    int newCut = 0;
    int bestCut = firstCut;
    std::vector<bool> W = U;
    int timelimit = 0;
    while (k <= r) {
        newCut = 0;
        std::random_device generator;
        std::uniform_int_distribution<int> distribution(1, vertices - 1);
        int chosen = distribution(generator);
        if (W[chosen])
            W[chosen] = false;
        else
            W[chosen] = true;
        // Reconstrutor
        for (int i = 0; i < vertices; i++) {
            if (W[i]) {
                for (auto e : adjList[i]) {
                    if(W[e.dest]) continue;
                    newCut++;
                }
            }
        }
        if (newCut < firstCut) {
            U = W;
            k = 1;
            timelimit++;
            if (timelimit == 1000) break;
        }
        else {
            k++;
            bestCut = newCut;
            //timelimit++;
            //if (timelimit == 5) break;
        }
    }
    std::cout << "Melhor local: " << bestCut << std::endl;
}
