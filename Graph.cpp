#include "Graph.h"

void Graph::addEdge(int u, int v, int weight)
{
    adjList[u].push_back({v, weight});
    adjList[v].push_back({u, weight}); // 如果是无向图，添加反向边
}

const std::list<std::pair<int, int>> &Graph::getNeighbors(int u) const
{
    return adjList.at(u);
}

const std::unordered_map<int, std::list<std::pair<int, int>>> &Graph::getAdjList() const
{
    return adjList;
}
