#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Graph.h"
#include <vector>
#include <queue>
#include <unordered_set>
#include <climits>

class Algorithms
{
public:
    // 广度优先搜索（BFS）
    static void bfs(const Graph &graph, int start);

    // 深度优先搜索（DFS）
    static void dfs(const Graph &graph, int start);

    // Dijkstra算法，返回最短路径
    static std::unordered_map<int, int> dijkstra(const Graph &graph, int start);

    // Prim算法，计算最小生成树
    static std::vector<std::tuple<int, int, int>> prim(const Graph &graph);
};

#endif
