#include <bits/stdc++.h>

using namespace std;

template<typename T>
class Graph final {
    
public:

    struct Edge final {
        T node1;
        T node2;
        size_t weight;
        
        Edge() = default;
        Edge(T node1, T node2, size_t weight) noexcept :
            node1(node1), node2(node2), weight(weight) {}

        friend bool operator<(const Edge& e1, const Edge& e2) noexcept {
            return e1.weight != e2.weight ? e1.weight < e2.weight
                 : e1.node1 != e2.node1   ? e1.node1  < e2.node1
                                          : e1.node2  < e2.node2;
        }
        friend bool operator>(const Edge& e1, const Edge& e2) noexcept {
            return e2 < e1;
        }
        
        string toString() const noexcept {
            ostringstream oss;
            oss << "(" << node1 << "-> " << node2 << ": " << weight << ")";
            return oss.str();
        }
        
        friend ostream& operator<<(ostream& os, const Edge& edge) noexcept {
            os << edge.toString();
            return os;
        }
    };

    using Pair = pair<T, size_t>;

    struct PairHash final {
        template<typename T1, typename T2>
        size_t operator() (const std::pair<T1, T2>& pair) const {
            return (std::hash<T1>()(pair.first ) << 4)
                 ^ (std::hash<T2>()(pair.second) << 0);
        }
    };

    using Adjacency     = unordered_set<Pair, PairHash>;  
    using AdjacencyList = unordered_map<T, Adjacency>;

    Graph(vector<T> nodes, vector<Edge> edges, bool directed = false) noexcept :
        directed(directed) {

        //size_t n = nodes.size();
        adjacencyList.reserve(nodes.size());
        for (auto& node : nodes)
        {
            adjacencyList[node] = Adjacency{};
            this->nodes.insert(node);
        }
        for (auto [node1, node2, weight] : edges)
            addEdge(node1, node2, weight);
    }

    Graph(vector<T> nodes, bool directed = false) noexcept :
        Graph(nodes, {}, directed) {}

    
    auto size() const noexcept { return nodes.size(); }

    void addEdge(T node1, T node2, size_t weight) noexcept {
        adjacencyList[node1].emplace(node2, weight);
        if (!directed)
            adjacencyList[node2].emplace(node1, weight);
    }

    void removeEdge(T node1, T node2, size_t weight) noexcept {
        adjacencyList[node1].erase({node2, weight});       
    }

    void clearEdges(T node) noexcept {
        adjacencyList[node].clear();
    }    
    void erase(T node) noexcept {
        adjacencyList.erase(node);
    }
    
    const AdjacencyList& getList() const noexcept {
        return adjacencyList;
    }
    AdjacencyList& getList() noexcept {
        return adjacencyList;
    }
    
    const Adjacency& getNeighbors(T node) const noexcept {
        return adjacencyList.at(node);
    }
    Adjacency& getNeighbors(T node) noexcept {
        return adjacencyList.at(node);
    }
    
    string toString() const noexcept {
        ostringstream oss;
        
        for (auto node : nodes)
        {
            oss << node << ":-> ";
            for (const auto& [n, w] : getNeighbors(node))
                oss << "(" << n << ": " << w << ") ";
            oss << '\n';
        }
        return oss.str();
    }
    
    friend ostream& operator<<(ostream& os, const Graph& graph) noexcept {
        os << graph.toString();
        return os;
    }

private:

    set<T> nodes;
    AdjacencyList adjacencyList;
    bool directed;
};

template<typename T>
class CityConnections final {
public:
    CityConnections(vector<T> cities,
                    vector<typename Graph<T>::Edge> flights) noexcept
        : cities(cities), graph(cities, flights, true) {}

    vector<vector<T>> findStronglyConnectedComponents() noexcept {
        
        return kosarajuSCC();
    }


private:
    vector<T> cities;
    Graph<T> graph;
    unordered_map<T, T> sccMap; // Maps node to its SCC captain

    vector<vector<T>> kosarajuSCC() noexcept {
        stack<T> finishedStack;
        unordered_set<T> visited;

        cerr << graph;
        // Step 1: First DFS to fill the stack in order of finish times
        for (const T& node : cities)
            if (visited.find(node) == visited.end())
                dfs1(node, visited, finishedStack);

        // Step 2: Transpose the graph
        Graph<T> transposedGraph = transposeGraph();

        // Step 3: Second DFS on transposed graph
        vector<vector<T>> SCCs;
        visited.clear();

        while (!finishedStack.empty())
        {
            T node = finishedStack.top();
            finishedStack.pop();

            if (visited.find(node) == visited.end())
            {
                vector<T> scc;
                dfs2(transposedGraph, node, visited, scc);
                SCCs.push_back(scc);

                // Assign the "captain" of this SCC, which is the first node in this SCC
                T captain = scc[0]; // Choose the first node as the captain
                for (const T& sccNode : scc)
                    sccMap[sccNode] = captain; // Map each node in the SCC to its captain
            }
        }
        //cerr << "SCC Map:\n";
        //for (auto& [node, captain] : sccMap)
        //    cerr << node << "->" << captain << "\n";        

        return SCCs;
    }

    void dfs1(T node, unordered_set<T>& visited, stack<T>& finishedStack) noexcept {
        visited.insert(node);
        for (const auto& [neighbor, weight] : graph.getNeighbors(node))
            if (visited.find(neighbor) == visited.end())
                dfs1(neighbor, visited, finishedStack);
        finishedStack.push(node);
    }

    void dfs2(Graph<T>& transposedGraph, T node, unordered_set<T>& visited, vector<T>& scc) noexcept {
        visited.insert(node);
        scc.push_back(node);
        for (const auto& [neighbor, weight] : transposedGraph.getNeighbors(node))
            if (visited.find(neighbor) == visited.end())
                dfs2(transposedGraph, neighbor, visited, scc);
    }

    Graph<T> transposeGraph() noexcept {
        vector<typename Graph<T>::Edge> transposedEdges;
        for (const auto& [node, neighbors] : graph.getList())
            for (const auto& [neighbor, weight] : neighbors)
                // Reverse edge
                transposedEdges.emplace_back(neighbor, node, weight);
        
        return Graph<T>(cities, transposedEdges, true);
    }

};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n, m;
    cin >> n >> m;
    assert(1 <= n && n <= 1e5);
    assert(1 <= m && m <= 2e5);

    vector<size_t> cities(n);
    std::iota(cities.begin(), cities.end(), 1);
    
    vector<Graph<size_t>::Edge> flights(m);
    for (size_t i = 0; i < m; ++i)
    {
        size_t node1, node2;
        size_t weight = 0;
        cin >> node1 >> node2;
        //assert(node1 != node2);

        flights[i].node1 = node1;
        flights[i].node2 = node2;
        flights[i].weight = weight;
    }

    CityConnections cityConnections(cities, flights);

    auto scc = cityConnections.findStronglyConnectedComponents();
    if (scc.size() > 1)
    {
        cout << "NO\n";
        cout << scc[1][0] << ' '
             << scc[0][0] << '\n';
    }
    else
    {
        cout << "YES\n";
    }
    //for (auto comp : scc) {
    //    for (auto node : comp)
    //        cout << node << ' ';
    //    cout << '\n';    
    //}
        
    return 0;
}
