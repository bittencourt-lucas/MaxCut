#ifndef MAXCUT_HPP_
#define MAXCUT_HPP_

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <random>
#include "../Graph/Graph.hpp"

class MaxCut {

private:
    std::queue<int> edges_queue;
    std::vector<int> wgtU;
    std::vector<int> wgtV;
    std::vector<bool> U;
    std::vector<bool> V;
    int max(int a, int b) { return a > b ? a : b; }

public:
    void insert(int, std::vector<bool>&, std::vector<int>&, std::vector<std::vector<Edge>>&);
    int construct(std::vector<std::vector<Edge>>&, std::vector<Edge>&);
    int VND(std::vector<std::vector<Edge>>&, std::vector<bool>&, int, int);
    int MultiStart(std::vector<std::vector<Edge>>&, std::vector<Edge>&, int);
};

#endif /* MAXCUT_HPP_ */
