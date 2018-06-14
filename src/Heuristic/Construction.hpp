#ifndef CONSTRUCTION_HPP_
#define CONSTRUCTION_HPP_

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include "../Graph/Graph.hpp"

class Construction {

private:

    std::queue<int> score;
    std::vector<int> wgtU;
    std::vector<int> wgtV;
    std::vector<bool> U;
    std::vector<bool> V;
    int max(int a, int b) { return a > b ? a : b; }

public:
    void insert(int, std::vector<bool>&, std::vector<int>&, std::vector<std::vector<Edge>>&);
    void construct(std::vector<std::vector<Edge>>&, std::vector<Edge>&);

};

#endif /* CONSTRUCTION_HPP_ */
