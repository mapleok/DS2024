#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <climits>
#include <tuple>

// Graph 类定义
class Graph
{
public:
    // 添加边
    void addEdge(int u, int v, int weight)
    {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    // 获取某个节点的邻居
    const std::list<std::pair<int, int>> &getNeighbors(int u) const
    {
        return adjList.at(u);
    }

    // 获取整个邻接表
    const std::unordered_map<int, std::list<std::pair<int, int>>> &getAdjList() const
    {
        return adjList;
    }

private:
    std::unordered_map<int, std::list<std::pair<int, int>>> adjList;
};

// 算法类定义
class Algorithms
{
public:
    // 广度优先搜索
    static void bfs(const Graph &graph, int start)
    {
        std::unordered_set<int> visited;
        std::queue<int> q;
        q.push(start);
        visited.insert(start);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            std::cout << node << " ";

            for (const auto &neighbor : graph.getNeighbors(node))
            {
                int neighborNode = neighbor.first;
                if (visited.find(neighborNode) == visited.end())
                {
                    visited.insert(neighborNode);
                    q.push(neighborNode);
                }
            }
        }
        std::cout << std::endl;
    }

    // 深度优先搜索
    static void dfs(const Graph &graph, int start)
    {
        std::unordered_set<int> visited;
        std::vector<int> stack;
        stack.push_back(start);

        while (!stack.empty())
        {
            int node = stack.back();
            stack.pop_back();

            if (visited.find(node) == visited.end())
            {
                visited.insert(node);
                std::cout << node << " ";

                for (const auto &neighbor : graph.getNeighbors(node))
                {
                    int neighborNode = neighbor.first;
                    stack.push_back(neighborNode);
                }
            }
        }
        std::cout << std::endl;
    }

    // Dijkstra 最短路径算法
    static std::unordered_map<int, int> dijkstra(const Graph &graph, int start)
    {
        std::unordered_map<int, int> dist;
        for (const auto &pair : graph.getAdjList())
        {
            dist[pair.first] = INT_MAX;
        }
        dist[start] = 0;

        auto cmp = [](const std::pair<int, int> &a, const std::pair<int, int> &b)
        {
            return a.second > b.second;
        };

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> pq(cmp);
        pq.push({start, 0});

        while (!pq.empty())
        {
            int u = pq.top().first;
            int d = pq.top().second;
            pq.pop();

            if (d > dist[u])
                continue;

            for (const auto &neighbor : graph.getNeighbors(u))
            {
                int v = neighbor.first;
                int weight = neighbor.second;
                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    pq.push({v, dist[v]});
                }
            }
        }

        return dist;
    }

    // Prim 最小生成树算法
    static std::vector<std::tuple<int, int, int>> prim(const Graph &graph)
    {
        std::unordered_set<int> visited;
        std::vector<std::tuple<int, int, int>> mst;
        auto cmp = [](const std::tuple<int, int, int> &a, const std::tuple<int, int, int> &b)
        {
            return std::get<2>(a) > std::get<2>(b);
        };

        std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, decltype(cmp)> pq(cmp);

        int start = graph.getAdjList().begin()->first;
        visited.insert(start);

        for (const auto &neighbor : graph.getNeighbors(start))
        {
            pq.push({start, neighbor.first, neighbor.second});
        }

        while (!pq.empty())
        {
            int u = std::get<0>(pq.top());
            int v = std::get<1>(pq.top());
            int weight = std::get<2>(pq.top());
            pq.pop();

            if (visited.find(v) == visited.end())
            {
                visited.insert(v);
                mst.push_back({u, v, weight});

                for (const auto &neighbor : graph.getNeighbors(v))
                {
                    int neighborNode = neighbor.first;
                    int neighborWeight = neighbor.second;
                    if (visited.find(neighborNode) == visited.end())
                    {
                        pq.push({v, neighborNode, neighborWeight});
                    }
                }
            }
        }

        return mst;
    }
};

// 主程序
int main()
{
    Graph g;

    // 添加一些边
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 4, 9);

    std::cout << "BFS from node 1: ";
    Algorithms::bfs(g, 1);

    std::cout << "DFS from node 1: ";
    Algorithms::dfs(g, 1);

    std::cout << "Dijkstra's shortest path from node 1: ";
    auto dist = Algorithms::dijkstra(g, 1);
    for (const auto &pair : dist)
    {
        std::cout << pair.first << ": " << pair.second << " ";
    }
    std::cout << std::endl;

    std::cout << "Prim's Minimum Spanning Tree: ";
    auto mst = Algorithms::prim(g);
    for (const auto &edge : mst)
    {
        std::cout << "(" << std::get<0>(edge) << ", " << std::get<1>(edge) << ", " << std::get<2>(edge) << ") ";
    }
    std::cout << std::endl;

    return 0;
}
