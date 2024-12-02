#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <unordered_map>

class Graph
{
public:
    // 添加边，v是目标节点，weight是边的权重
    void addEdge(int u, int v, int weight = 0);

    // 获取与节点u连接的所有邻居
    const std::list<std::pair<int, int>> &getNeighbors(int u) const;

    // 获取图中所有的节点
    const std::unordered_map<int, std::list<std::pair<int, int>>> &getAdjList() const;

private:
    std::unordered_map<int, std::list<std::pair<int, int>>> adjList; // 邻接表表示图
};

#endif
