#include <iostream>
#include "Graph.h"
#include "Algorithms.h"

int main()
{
    // 创建图实例
    Graph graph;

    // 添加边：节点、目标节点、边的权重
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 1);
    graph.addEdge(2, 1, 2);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 8);

    // BFS测试
    std::cout << "BFS: ";
    Algorithms::bfs(graph, 0);

    // DFS测试
    std::cout << "DFS: ";
    Algorithms::dfs(graph, 0);

    // Dijkstra 最短路径
    std::cout << "Dijkstra Shortest Path from 0: ";
    auto dist = Algorithms::dijkstra(graph, 0);
    for (const auto &p : dist)
    {
        std::cout << p.first << "->" << p.second << " ";
    }
    std::cout << std::endl;

    // Prim 最小生成树
    std::cout << "Prim Minimum Spanning Tree: ";
    auto mst = Algorithms::prim(graph);
    for (const auto &edge : mst)
    {
        std::cout << "(" << std::get<0>(edge) << "," << std::get<1>(edge) << "," << std::get<2>(edge) << ") ";
    }
    std::cout << std::endl;
    std::cout << "Press Enter to exit.";
    std::cin.get(); // 等待用户输入
    return 0;
}
