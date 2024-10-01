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

        bool operator<(const Edge& edge) const noexcept {
            return weight != edge.weight ? weight < edge.weight
                  : node1 != edge.node1  ? node1  < edge.node1
                                         : node2  < edge.node2;
        }
        bool operator>(const Edge& edge) const noexcept {
            return edge < *this;
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
            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
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

    void DFS(T node, unordered_map<T, bool>& visited, vector<T>& component) {
        visited[node] = true;
        component.push_back(node);
        for (auto [neighbor, _] : getNeighbors(node))
        {
            if (!visited[neighbor])
                DFS(neighbor, visited, component);
        }
    }
    
    vector<vector<T>> getConnectedComponents() {
        unordered_map<T, bool> visited;
        vector<vector<T>> components;
        for (auto node : nodes)
        {
            if (!visited[node])
            {
                vector<T> component;
                DFS(node, visited, component);
                components.push_back(component);
            }
        }
        return components;
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


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<Graph<size_t>::Edge> edges(m);
    for (size_t i = 0; i < m; ++i)
    {
        size_t node1, node2, weight = 0;
        cin >> node1 >> node2;
        assert(1 <= node1 && node1 <= n);
        assert(1 <= node2 && node2 <= n);

        edges[i].node1  = node1;
        edges[i].node2  = node2;
        edges[i].weight = weight;
    }
    
    vector<size_t> nodes(n);
    std::iota(nodes.begin(), nodes.end(), 1);
    // Create a graph with nodes and edges
    Graph graph(nodes, edges, false);
    cerr << graph;

    // Step 1: Find all connected components
    auto components = graph.getConnectedComponents();
    int k = components.size();

    // Step 2: Output the number of new roads needed
    cout << k - 1 << '\n';

    // Step 3: Output the roads that need to be built
    // Connect each component to the next one
    for (int i = 1; i < k; ++i) {
        cout << components[i - 1][0] << " " << components[i][0] << '\n';
    }
    
    return 0;
}