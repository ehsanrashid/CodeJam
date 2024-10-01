#include <algorithm>
#include <iostream>
#include <limits>
#include <list>
#include <deque>
#include <queue>
#include <utility>
#include <vector>
#include <unordered_set>

// using namespace std;

using Vertex = int;
using Weight = int;

using Edge = std::pair<Vertex, Weight>; // Pair (neighbor, weight)

class Graph final
{
public:
    Graph(int nodes, bool isDirected = false);

    void addEdge(Vertex u, Vertex v, Weight weight = 1) noexcept;

    void print() const noexcept;

    void shortestDistances(Vertex start) const noexcept;
    void shortestPath(Vertex start, Vertex end) const noexcept;

private:
    int nodes;
    bool isDirected;
    std::vector<std::list<Edge>> adjList;
};

Graph::Graph(int nodes, bool isDirected)
    : nodes(nodes), isDirected(isDirected), adjList(nodes) {}

void Graph::addEdge(Vertex u, Vertex v, Weight weight) noexcept
{
    adjList[u].push_back({v, weight});
    if (!isDirected)
        adjList[v].push_back({u, weight}); // Since the graph is undirected
}

void Graph::print() const noexcept
{
    for (std::size_t i = 0; i < adjList.size(); ++i)
    {
        std::cout << "Node# " << i << ": ";
        for (const auto &edge : adjList[i])
        {
            auto neighbor = edge.first;
            auto weight = edge.second;

            std::cout << "{" << neighbor << ":" << weight << "} ";
        }
        std::cout << "\n";
    }
}

void Graph::shortestDistances(Vertex start) const noexcept
{
    std::vector<Weight> weights(nodes, std::numeric_limits<Weight>::max());
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>
        priorityQueue;

    weights[start] = 0;
    priorityQueue.push({start, 0});

    while (!priorityQueue.empty())
    {
        auto current_vertex = priorityQueue.top().first;
        auto current_weight = priorityQueue.top().second;
        priorityQueue.pop();

        if (current_weight > weights[current_vertex])
            continue;

        for (const auto &edge : adjList[current_vertex])
        {
            auto neighbor = edge.first;
            auto weight = edge.second;

            Weight new_weight = current_weight + weight;
            if (weights[neighbor] > new_weight)
            {
                weights[neighbor] = new_weight;
                priorityQueue.push({neighbor, new_weight});
            }
        }
    }

    for (int n = 0; n < nodes; ++n)
    {
        std::cout << "Distance from node " << start << " to node " << n << " is ";
        if (weights[n] != std::numeric_limits<int>::max())
            std::cout << weights[n] << std::endl;
        else
            std::cout << "INF" << std::endl;
    }
}

void Graph::shortestPath(Vertex start, Vertex end) const noexcept
{
    std::vector<bool> visited(nodes, false);
    std::vector<Weight> weights(nodes, -1);
    std::vector<Vertex> predecessor(nodes, -1);

    bool pathFound = false;
    // std::queue<Vertex> queue;
    // std::unordered_set<Vertex> set;
    std::deque<Vertex> deque;

    // visited[start] = true;
    weights[start] = 0;
    // queue.push(start);
    // set.insert(start);
    deque.push_back(start);
    // while (!queue.empty())
    while (!deque.empty())
    {
        // int current = queue.front();
        // queue.pop();
        int current = deque.front();
        deque.pop_front();

        visited[current] = true;
        for (auto &edge : adjList[current])
        {
            auto neighbor = edge.first;
            auto weight = edge.second;

            if (!visited[neighbor])
            {
                weights[neighbor] = weights[current] + weight;
                predecessor[neighbor] = current;

                if (neighbor == end)
                {
                    pathFound = true;

                    // Reached the destination node
                    std::cout << "Shortest path weight is " << weights[end] << std::endl;
                    std::cout << "Path: ";
                    std::vector<Vertex> path;
                    for (Vertex v = end; v != -1; v = predecessor[v])
                        path.push_back(v);
                    std::reverse(path.begin(), path.end());

                    std::string pathStr;
                    for (Vertex v : path)
                        pathStr += std::to_string(v) + " ";

                    std::cout << pathStr << std::endl;
                    continue;
                }

                // if (std::find(set.begin(), set.end(), neighbor) == set.end())
                // {
                //     queue.push(neighbor);
                //     set.insert(neighbor);
                // }
                if (std::find(deque.begin(), deque.end(), neighbor) == deque.end())
                    deque.push_back(neighbor);

            }
        }
    }

    if (!pathFound)
        std::cout << "No path exists between nodes " << start << " and " << end << std::endl;
}

int main()
{
    // Graph g(6, true); // Create directed graph with 6 nodes (0 to 5)
    Graph graph(6); // Create undirected graph with 6 nodes (0 to 5)
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 7);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 5, 1);
    graph.addEdge(4, 3, 2);
    graph.addEdge(4, 5, 5);
    // graph.addEdge(5, 0, 2);

    graph.print();

    Vertex start = 0, end = 3;
    graph.shortestDistances(start); // Find the shortest paths from node 0
    graph.shortestPath(start, end);

    return 0;
}
