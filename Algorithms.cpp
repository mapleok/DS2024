#include "Algorithms.h"
#include "Graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <tuple>

void Algorithms::bfs(const Graph &graph, int start)
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

void Algorithms::dfs(const Graph &graph, int start)
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

std::unordered_map<int, int> Algorithms::dijkstra(const Graph &graph, int start)
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

std::vector<std::tuple<int, int, int>> Algorithms::prim(const Graph &graph)
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
