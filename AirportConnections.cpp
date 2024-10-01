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
class AirportConnections final {
public:
    AirportConnections(vector<T> airports,
                       vector<typename Graph<T>::Edge> routes) noexcept
        : airports(airports), graph(airports, routes, true) {}

    vector<pair<T, T>> findRequiredConnections(T startAirport) noexcept {

        cerr << graph;
        // Step 1: Find Strongly Connected Components (Kosaraju's Algorithm)
        auto SCCs = kosarajuSCC();
        
        //for (auto& nodes : SCCs) {
        //    for (auto node : nodes)
        //        cerr << node << ' ';
        //    cerr << '\n';
        //}
        
        // Step 2: Reduce graph to a Directed Acyclic Graph (DAG)
        auto reducedGraph = buildSCCGraph(SCCs);

        cerr << "Reduced Graph:\n";
        cerr << reducedGraph;
        
        // Step 3: Calculate the required pairs of connections
        // needed to make all airports reachable from starts
        auto requiredConnections = calculateMinConnections(SCCs, reducedGraph, startAirport);

        return requiredConnections;
    }


private:
    vector<T> airports;
    Graph<T> graph;
    unordered_map<T, T> sccMap; // Maps node to its SCC captain

    vector<vector<T>> kosarajuSCC() noexcept {
        stack<T> finishedStack;
        unordered_set<T> visited;

        // Step 1: First DFS to fill the stack in order of finish times
        for (const T& node : airports)
            if (visited.find(node) == visited.end())
                DFS1(node, visited, finishedStack);

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
                DFS2(transposedGraph, node, visited, scc);
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

    void DFS1(T node, unordered_set<T>& visited, stack<T>& finishedStack) noexcept {
        visited.insert(node);
        for (const auto& [neighbor, weight] : graph.getNeighbors(node))
            if (visited.find(neighbor) == visited.end())
                DFS1(neighbor, visited, finishedStack);
        finishedStack.push(node);
    }

    void DFS2(Graph<T>& transposedGraph, T node, unordered_set<T>& visited, vector<T>& scc) noexcept {
        visited.insert(node);
        scc.push_back(node);
        for (const auto& [neighbor, weight] : transposedGraph.getNeighbors(node))
            if (visited.find(neighbor) == visited.end())
                DFS2(transposedGraph, neighbor, visited, scc);
    }

    Graph<T> transposeGraph() noexcept {
        vector<typename Graph<T>::Edge> transposedEdges;
        for (const auto& [node, neighbors] : graph.getList())
            for (const auto& [neighbor, weight] : neighbors)
                // Reverse edge
                transposedEdges.emplace_back(neighbor, node, weight);
        
        return Graph<T>(airports, transposedEdges, true);
    }

    Graph<T> buildSCCGraph(const vector<vector<T>>& SCCs) {
        vector<typename Graph<T>::Edge> sccEdges;

        for (const auto& [node, neighbors] : graph.getList()) {
            T fromSCC = sccMap[node];
            for (const auto& [neighbor, weight] : neighbors) {
                T toSCC = sccMap[neighbor];
                if (fromSCC != toSCC)
                    sccEdges.emplace_back(fromSCC, toSCC, 0); // Add edge between SCCs
            }
        }

        // Fill sccNodes with the captain (first node) of each SCC
        unordered_set<T> sccNodesSet;
        for (const auto& scc : SCCs)
        {
            if (!scc.empty())
            {
                T captain = scc[0]; // First node of each SCC as captain
                sccNodesSet.insert(captain);
            }
        }

        vector<T> sccNodes(sccNodesSet.begin(), sccNodesSet.end());

        // Directed graph of SCCs
        return Graph<T>(sccNodes, sccEdges, true);
    }

    vector<pair<T, T>> calculateMinConnections(const vector<vector<T>>& SCCs, Graph<T>& reducedGraph, T startAirport) noexcept {

        unordered_set<T> allSCCs;
        unordered_map<T, size_t> inDegree, outDegree;

        // Initialize inDegree and outDegree
        for (const auto& [sccNode, _] : reducedGraph.getList())
        {
            allSCCs.insert(sccNode);
            inDegree[sccNode] = 0;
            outDegree[sccNode] = 0;
        }

        // Calculate inDegree and outDegree for each SCC in the reduced graph
        for (const auto& [scc, neighbors] : reducedGraph.getList())
            for (const auto& [neighbor, _] : neighbors)
            {
                ++inDegree[neighbor];
                ++outDegree[scc];
            }

        // BFS from the SCC containing the start node
        T startSCC = sccMap[startAirport];
        unordered_set<T> visitedSCCs;
        visitedSCCs.insert(startSCC);

        queue<T> queue;
        queue.push(startSCC);

        // BFS to visit all reachable SCCs from start
        while (!queue.empty())
        {
            T currentSCC = queue.front();
            queue.pop();

            for (const auto& [neighborSCC, weight] : reducedGraph.getNeighbors(currentSCC))
            {
                if (visitedSCCs.find(neighborSCC) == visitedSCCs.end())
                {
                    visitedSCCs.insert(neighborSCC);
                    queue.push(neighborSCC);
                }
            }
        }

        // SCCs with no outgoing edges (potential sources)
        vector<T> sources;
        // SCCs with no incoming edges (potential sinks)
        vector<T> sinks;

        // Identify unreachable SCCs and categorize them as sources and sinks
        for (const T& scc : allSCCs)
        {
            if (visitedSCCs.find(scc) == visitedSCCs.end())
            {
                if (inDegree[scc] == 0)
                    sinks.push_back(scc);  // Unreachable SCC, no incoming edges
            }

            // If a SCC is not startCC has no outgoing edges
            if (scc != startSCC && outDegree[scc] == 0)
                sources.push_back(scc);
        }
        cerr << "Sources:\n";
        for (auto source : sources) cerr << source << ' ';
        cerr << '\n';
        cerr << "Sinks:\n";
        for (auto sink : sinks) cerr << sink << ' ';
        cerr << '\n';

        // Calculate the required new connections by pairing sources and sinks
	vector<pair<T, T>> requiredConnections;
        for (size_t i = 0; i < std::max(sources.size(), sinks.size()); ++i)
        {
            // Wrap around sources and sinks if their sizes differ
            T source = sources[i % sources.size()];
            T sink = sinks[i % sinks.size()];

            // Add the connection between a source SCC and a sink SCC
            requiredConnections.push_back({source, sink});
        }

        return requiredConnections;  // Return the new connections needed
    }

};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<string> airports(n);
    for (size_t i = 0; i < n; ++i)
    {
        string airport;
        cin >> airport;
        airports[i] = airport;
    }
    
    vector<Graph<string>::Edge> routes(m);
    for (size_t i = 0; i < m; ++i)
    {
        string node1, node2;
        size_t weight = 0;
        cin >> node1 >> node2;
        assert(node1 != node2);
        assert(0 <= weight && weight <= 1e4);

        routes[i].node1 = node1;
        routes[i].node2 = node2;
        routes[i].weight = weight;
    }

    string startAirport;
    cin >> startAirport;

    AirportConnections<string> airportConn(airports, routes);

    auto requiredConnections = airportConn.findRequiredConnections(startAirport);
    cout << "Number of required connections: " << requiredConnections.size() << '\n';
    // Output the required connections
    cout << "Required connections to make graph fully connected:\n";
    for (const auto& [from, to] : requiredConnections)
        cout << from << " -> " << to << '\n';

    return 0;
}

/*
* Input
18 19
BGI
CDG
DEL
DOH
DSM
EWR
EYW
HND
ICN
JFK
LGA
LHR
ORD
SAN
SFO
SIN
TLV
BUD
DSM ORD
ORD BGI
BGI LGA
SIN CDG
CDG SIN
CDG BUD
DEL DOH
DEL CDG
TLV DEL
EWR HND
HND ICN
HND JFK
ICN JFK
JFK LGA
EYW LHR
LHR SFO
SFO SAN
SFO DSM
SAN EYW
LGA

* Output
3

Number of required connections: 3
Required connections to make graph fully connected:
DOH -> EYW
BUD -> TLV
DOH -> EWR

*/