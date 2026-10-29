#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using usize = std::size_t;
using isize = std::ptrdiff_t;

// DisjointSet is essentially implementing Disjoint Set Union (DSU) / Union-Find.
// This is a good candidate for a standalone reusable class.
class DisjointSet final {
   public:
    DisjointSet() noexcept = default;

    explicit DisjointSet(const usize n) noexcept { reset(n); }

    void reset(const usize n) noexcept {
        parents.resize(n);
        std::iota(parents.begin(), parents.end(), 0);
        ranks.assign(n, 0);
        sizes.assign(n, 1);
        components_ = n;
    }

    [[nodiscard]] usize find(const usize x) noexcept {
        if (parents[x] != x)
            parents[x] = find(parents[x]);

        return parents[x];
    }

    bool unite(const usize x, const usize y) noexcept {
        usize px = find(x);
        usize py = find(y);

        if (px == py)
            return false;

        if (ranks[px] < ranks[py])
            std::swap(px, py);

        parents[py] = px;
        sizes[px] += sizes[py];

        ranks[px] += (ranks[px] == ranks[py]);

        --components_;

        return true;
    }

    [[nodiscard]] bool connected(const usize x, const usize y) noexcept {
        return find(x) == find(y);
    }

    [[nodiscard]] usize size(const usize x) noexcept { return sizes[find(x)]; }

    [[nodiscard]] usize components() const noexcept { return components_; }

   private:
    std::vector<usize> parents;
    std::vector<usize> ranks;
    std::vector<usize> sizes;
    usize              components_ = 0;
};

enum class GraphType {
    Directed,
    Undirected
};

template<typename Vertex,
         GraphType Type                         = GraphType::Directed,
         typename Weight                        = int,
         template<typename, typename> class Map = std::unordered_map>
class Graph final {
   public:
    using vertex_type          = Vertex;
    using weight_type          = Weight;
    using adjacency_type       = Map<Vertex, Weight>;
    using map_type             = Map<Vertex, adjacency_type>;
    using component_type       = std::vector<Vertex>;
    using components_type      = std::vector<component_type>;
    using component_index_type = Map<Vertex, usize>;

   private:
    template<typename T, typename = void>
    struct HasReserve: std::false_type {};

    template<typename T>
    struct HasReserve<T, std::void_t<decltype(std::declval<T&>().reserve(usize{}))>>
        : std::true_type {};

   public:
    Graph() = default;

    explicit Graph(usize capacity) {
        if constexpr (HasReserve<map_type>::value)
            adjacencies_.reserve(capacity);

        if constexpr (HasReserve<component_index_type>::value)
            componentIndices.reserve(capacity);

        components_.reserve(capacity);
    }

    // Vertex operations

    bool add_vertex(const Vertex& vertex) {
        if (!ensure_vertex(vertex))
            return false;

        add_component(vertex);
        return true;
    }

    bool remove_vertex(const Vertex& vertex) {
        auto victimItr = adjacencies_.find(vertex);

        if (victimItr == adjacencies_.end())
            return false;

        // Remove outgoing edges.
        edgeCount -= victimItr->second.size();

        // Remove incoming edges.
        for (auto itr = adjacencies_.begin(); itr != adjacencies_.end(); ++itr)
        {
            if (itr == victimItr)
                continue;

            if (itr->second.erase(vertex) != 0)
            {
                if constexpr (Type == GraphType::Directed)
                    --edgeCount;
            }
        }

        adjacencies_.erase(victimItr);
        rebuild_components();

        return true;
    }

    bool contains_vertex(const Vertex& vertex) const {
        return adjacencies_.find(vertex) != adjacencies_.end();
    }

    // Edge operations

    // Returns false if the edge already exists.
    // Missing vertices are added automatically.
    // The default weight is zero.
    bool add_edge(const Vertex& src, const Vertex& dst, const Weight& weight = Weight{0}) {
        const bool addedSrc = ensure_vertex(src);
        const bool addedDst = ensure_vertex(dst);

        auto srcItr = adjacencies_.find(src);
        auto dstItr = adjacencies_.find(dst);

        const bool isSelfLoop = srcItr == dstItr;

        if (srcItr->second.find(dst) != srcItr->second.end())
        {
            if (addedSrc || addedDst)
                rebuild_components();

            return false;
        }

        auto [edgeItr, inserted] = srcItr->second.try_emplace(dst, weight);

        if (!inserted)
        {
            if (addedSrc || addedDst)
                rebuild_components();

            return false;
        }

        if constexpr (Type == GraphType::Undirected)
        {
            if (!isSelfLoop)
            {
                const auto [reverseItr, reverseInserted] = dstItr->second.try_emplace(src, weight);

                (void) reverseItr;

                if (!reverseInserted)
                {
                    srcItr->second.erase(edgeItr);

                    if (addedSrc || addedDst)
                        rebuild_components();

                    return false;
                }
            }
        }

        ++edgeCount;
        rebuild_components();

        return true;
    }

    bool remove_edge(const Vertex& src, const Vertex& dst) {
        auto srcItr = adjacencies_.find(src);

        if (srcItr == adjacencies_.end())
            return false;

        auto dstItr  = adjacencies_.find(dst);
        auto edgeItr = srcItr->second.find(dst);

        if (edgeItr == srcItr->second.end())
            return false;

        if constexpr (Type == GraphType::Undirected)
        {
            if (dstItr == adjacencies_.end())
                return false;

            if (dstItr != srcItr && dstItr->second.find(src) == dstItr->second.end())
                return false;

            if (dstItr != srcItr)
                dstItr->second.erase(src);
        }

        srcItr->second.erase(edgeItr);

        --edgeCount;
        rebuild_components();

        return true;
    }

    bool contains_edge(const Vertex& src, const Vertex& dst) const {
        auto srcItr = adjacencies_.find(src);

        return srcItr != adjacencies_.end()  //
            && srcItr->second.find(dst) != srcItr->second.end();
    }

    // Returns nullptr if the edge does not exist.
    const Weight* get_weight(const Vertex& src, const Vertex& dst) const {
        auto srcItr = adjacencies_.find(src);

        if (srcItr == adjacencies_.end())
            return nullptr;

        auto edgeItr = srcItr->second.find(dst);

        return edgeItr == srcItr->second.end() ? nullptr : &edgeItr->second;
    }

    // Updates an existing edge's weight.
    bool set_weight(const Vertex& src, const Vertex& dst, const Weight& weight) {
        auto srcItr = adjacencies_.find(src);

        if (srcItr == adjacencies_.end())
            return false;

        auto edgeItr = srcItr->second.find(dst);

        if (edgeItr == srcItr->second.end())
            return false;

        if constexpr (Type == GraphType::Undirected)
        {
            auto dstItr = adjacencies_.find(dst);

            if (dstItr == adjacencies_.end())
                return false;

            if (dstItr != srcItr)
            {
                auto reverseItr = dstItr->second.find(src);

                if (reverseItr == dstItr->second.end())
                    return false;

                edgeItr->second    = weight;
                reverseItr->second = weight;
            }
            else
            {
                edgeItr->second = weight;
            }
        }
        else
        {
            edgeItr->second = weight;
        }

        return true;
    }

    // Connectivity

    // Directed graphs use weak connectivity: edge direction is ignored.
    bool connected(const Vertex& src, const Vertex& dst) const { return connected_(src, dst); }

    // Counts and access

    // Returns the authoritative adjacency collection.
    const map_type& adjacencies() const noexcept { return adjacencies_; }

    // Returns the adjacency collection for a vertex, or nullptr if absent.
    const adjacency_type* adjacency_of(const Vertex& vertex) const {
        auto itr = adjacencies_.find(vertex);

        return itr == adjacencies_.end() ? nullptr : &itr->second;
    }

    // Returns the number of vertices.
    usize vertex_count() const noexcept { return adjacencies_.size(); }

    // Returns the number of edges. Undirected edges are counted once.
    usize edge_count() const noexcept { return edgeCount; }

    // Returns the authoritative component collection.
    // Each element contains all vertices belonging to one weakly connected component.
    const components_type& components() const noexcept { return components_; }

    // Returns the number of weakly connected components.
    usize component_count() const noexcept { return components_.size(); }

    // Returns the mapping from each vertex to its component index.
    // The index refers to an element in components().
    const component_index_type& component_index() const noexcept { return componentIndices; }

    // Returns the component index for a vertex, or nullptr if absent.
    // The returned pointer is invalidated by topology changes.
    const usize* component_index_of(const Vertex& vertex) const {
        auto itr = componentIndices.find(vertex);

        return itr == componentIndices.end() ? nullptr : &itr->second;
    }

    // Returns the size of the component containing vertex.
    //
    // O(1) average with std::unordered_map.
    // O(log V) with std::map.
    usize component_size_of(const Vertex& vertex) const {
        auto itr = componentIndices.find(vertex);

        if (itr == componentIndices.end())
            return 0;

        return components_[itr->second].size();
    }

    bool empty() const noexcept { return adjacencies_.empty(); }

    // Returns the adjacency collection for a vertex, or nullptr if absent.
    const adjacency_type* neighbors(const Vertex& vertex) const { return adjacency_of(vertex); }

    void clear() noexcept {
        adjacencies_.clear();
        components_.clear();
        componentIndices.clear();
        edgeCount = 0;
    }

    std::string to_string() const {
        std::ostringstream oss;

        oss << "[\n"
            << "    type: " << (Type == GraphType::Directed ? "Directed" : "Undirected") << "\n"
            << "    vertices: " << vertex_count() << "\n"
            << "    edges: " << edge_count() << "\n"
            << "    components: " << component_count() << "\n"
            << "    component sizes:\n";

        for (const auto& [vertex, index] : component_index())
        {
            oss << "        " << vertex << ": " << components_[index].size() << "\n";
        }

        oss << "    adjacencies:\n";

        for (const auto& [vertex, edges] : adjacencies())
        {
            oss << "        " << vertex << " -> [";

            bool first = true;

            for (const auto& [neighbor, weight] : edges)
            {
                if (!first)
                    oss << ", ";

                oss << neighbor << " (" << weight << ")";
                first = false;
            }

            oss << "]\n";
        }

        oss << "]";

        return oss.str();
    }

   private:
    // Inserts a vertex without rebuilding component data.
    // Used internally to batch topology changes.
    bool ensure_vertex(const Vertex& vertex) { return adjacencies_.try_emplace(vertex).second; }

    void add_component(const Vertex& vertex) {
        const usize index = components_.size();

        components_.emplace_back(1, vertex);
        componentIndices.try_emplace(vertex, index);
    }

    // Rebuild weakly connected components using DSU.
    //
    // For directed graphs, every directed edge A -> B is treated as
    // an undirected connection A <-> B.
    //
    // Complexity:
    //     O((V + E) * alpha(V))
    //
    // which is effectively O(V + E).

    void rebuild_components() {
        components_.clear();
        componentIndices.clear();

        const usize vertexCount = adjacencies_.size();

        if (vertexCount == 0)
            return;

        if constexpr (HasReserve<component_index_type>::value)
            componentIndices.reserve(vertexCount);

        // Assign each vertex a compact integer index.
        Map<Vertex, usize> vertexIndices;

        if constexpr (HasReserve<Map<Vertex, usize>>::value)
            vertexIndices.reserve(vertexCount);

        usize index = 0;

        for (const auto& [vertex, edges] : adjacencies_)
        {
            (void) edges;
            vertexIndices.try_emplace(vertex, index++);
        }

        DisjointSet disjointSet(vertexCount);

        // Build weakly connected components by ignoring edge direction.
        for (const auto& [vertex, edges] : adjacencies_)
        {
            const usize srcIndex = vertexIndices.find(vertex)->second;

            for (const auto& [neighbor, weight] : edges)
            {
                (void) weight;

                const usize dstIndex = vertexIndices.find(neighbor)->second;
                disjointSet.unite(srcIndex, dstIndex);
            }
        }

        const usize componentCount = disjointSet.components();

        components_.reserve(componentCount);

        // Map DSU roots to compact component indices.
        Map<usize, usize> rootIndices;

        if constexpr (HasReserve<Map<usize, usize>>::value)
            rootIndices.reserve(componentCount);

        // Group vertices and build vertex -> component index simultaneously.
        for (const auto& [vertex, vertexIndex] : vertexIndices)
        {
            const usize root = disjointSet.find(vertexIndex);

            auto [rootItr, inserted] = rootIndices.try_emplace(root, components_.size());

            if (inserted)
            {
                components_.emplace_back();

                // Reserve the exact number of vertices in this component.
                components_.back().reserve(disjointSet.size(root));
            }

            const usize componentIndex = rootItr->second;

            components_[componentIndex].push_back(vertex);
            componentIndices.try_emplace(vertex, componentIndex);
        }
    }

    bool connected_(const Vertex& src, const Vertex& dst) const {
        auto srcItr = componentIndices.find(src);
        auto dstItr = componentIndices.find(dst);

        return srcItr != componentIndices.end() && dstItr != componentIndices.end()
            && srcItr->second == dstItr->second;
    }

    map_type             adjacencies_;
    components_type      components_;
    component_index_type componentIndices;
    usize                edgeCount = 0;
};

template<typename Vertex,
         GraphType Type                         = GraphType::Directed,
         typename Weight                        = int,
         template<typename, typename> class Map = std::unordered_map>
class StronglyConnectedComponents final {
   public:
    using graph_type      = Graph<Vertex, Type, Weight, Map>;
    using component_type  = std::vector<Vertex>;
    using components_type = std::vector<component_type>;

    explicit StronglyConnectedComponents(const graph_type& graph) noexcept :
        graph_(graph) {}

    components_type find() const {
        const usize vertexCount = graph_.vertex_count();

        components_type components;
        components.reserve(vertexCount);

        std::vector<Vertex> finishOrder;
        finishOrder.reserve(vertexCount);

        Map<Vertex, bool> visited;

        // Step 1: DFS on the original graph; record finish order.
        for (const auto& [vertex, edges] : graph_.adjacencies())
        {
            (void) edges;

            if (visited.find(vertex) == visited.end())
                dfs_finish(vertex, visited, finishOrder);
        }

        // Step 2: Build the transpose adjacency.
        Map<Vertex, std::vector<Vertex>> reverseAdjacencies;

        for (const auto& [vertex, edges] : graph_.adjacencies())
        {
            (void) edges;
            reverseAdjacencies.try_emplace(vertex);
        }

        for (const auto& [from, edges] : graph_.adjacencies())
            for (const auto& [to, weight] : edges)
            {
                (void) weight;
                reverseAdjacencies.find(to)->second.push_back(from);
            }

        // Step 3: DFS on the transpose in reverse finish order.
        visited.clear();

        for (auto itr = finishOrder.rbegin(); itr != finishOrder.rend(); ++itr)
        {
            if (visited.find(*itr) != visited.end())
                continue;

            components.emplace_back();
            dfs_collect(*itr, reverseAdjacencies, visited, components.back());
        }

        return components;
    }

   private:
    using visited_type = Map<Vertex, bool>;
    using reverse_type = Map<Vertex, std::vector<Vertex>>;

    const graph_type& graph_;

    void dfs_finish(const Vertex&        vertex,
                    visited_type&        visited,
                    std::vector<Vertex>& finishOrder) const {
        visited.try_emplace(vertex, true);

        if (const auto* edges = graph_.neighbors(vertex))
            for (const auto& [neighbor, weight] : *edges)
            {
                (void) weight;

                if (visited.find(neighbor) == visited.end())
                    dfs_finish(neighbor, visited, finishOrder);
            }

        finishOrder.push_back(vertex);
    }

    static void dfs_collect(const Vertex&       vertex,
                            const reverse_type& reverseAdjacencies,
                            visited_type&       visited,
                            component_type&     component) {
        visited.try_emplace(vertex, true);
        component.push_back(vertex);

        const auto itr = reverseAdjacencies.find(vertex);

        if (itr == reverseAdjacencies.end())
            return;

        for (const auto& neighbor : itr->second)
            if (visited.find(neighbor) == visited.end())
                dfs_collect(neighbor, reverseAdjacencies, visited, component);
    }
};

template<typename Vertex, GraphType Type, typename Weight, template<typename, typename> class Map>
auto build_scc_graph(
  const Graph<Vertex, Type, Weight, Map>&                           graph,
  const typename Graph<Vertex, Type, Weight, Map>::components_type& components) noexcept {

    using ComponentMap = std::unordered_map<Vertex, usize>;
    using SCCGraph     = Graph<usize, GraphType::Directed>;

    SCCGraph     sccGraph(components.size());
    ComponentMap componentOf;

    componentOf.reserve(graph.vertex_count());

    // Assign each airport its SCC index.
    for (usize i = 0; i < components.size(); ++i)
    {
        sccGraph.add_vertex(i);

        for (const auto& airport : components[i])
            componentOf.emplace(airport, i);
    }

    // Add edges between different SCCs.
    for (const auto& [from, edges] : graph.adjacencies())
    {
        const usize fromSCC = componentOf.find(from)->second;

        for (const auto& [to, weight] : edges)
        {
            (void) weight;

            const usize toSCC = componentOf.find(to)->second;

            if (fromSCC != toSCC)
                sccGraph.add_edge(fromSCC, toSCC);
        }
    }

    return std::make_pair(std::move(sccGraph), std::move(componentOf));
}

template<typename Point,
         typename Vertex,
         GraphType Type,
         typename Weight,
         template<typename, typename> class Map>
auto find_reachable_sccs(const Point&                            startPoint,
                         const Graph<Vertex, Type, Weight, Map>& sccGraph,
                         const std::unordered_map<Point, usize>& componentOf) {
    std::vector<bool>  visited(sccGraph.vertex_count(), false);
    std::vector<usize> reachable;
    std::vector<usize> stack;

    const auto itr = componentOf.find(startPoint);

    if (itr == componentOf.end())
        return reachable;

    stack.push_back(itr->second);
    visited[itr->second] = true;

    while (!stack.empty())
    {
        const usize current = stack.back();
        stack.pop_back();

        reachable.push_back(current);

        if (const auto* neighbors = sccGraph.neighbors(current))
            for (const auto& [next, weight] : *neighbors)
            {
                (void) weight;

                if (!visited[next])
                {
                    visited[next] = true;
                    stack.push_back(next);
                }
            }
    }

    return reachable;
}

template<typename Weight, template<typename, typename> class Map>
auto calculate_reachability(const Graph<usize, GraphType::Directed, Weight, Map>& graph) {
    const usize                     count = graph.vertex_count();
    std::vector<std::vector<usize>> reachable(count);

    for (usize start = 0; start < count; ++start)
    {
        std::vector<bool>  visited(count, false);
        std::vector<usize> stack{start};
        visited[start] = true;

        while (!stack.empty())
        {
            const usize current = stack.back();
            stack.pop_back();

            reachable[start].push_back(current);

            if (const auto* neighbors = graph.neighbors(current))
                for (const auto& [next, weight] : *neighbors)
                {
                    (void) weight;

                    if (!visited[next])
                    {
                        visited[next] = true;
                        stack.push_back(next);
                    }
                }
        }
    }

    return reachable;
}

template<typename Weight, template<typename, typename> class Map>
auto find_source_sccs(const Graph<usize, GraphType::Directed, Weight, Map>& sccGraph) noexcept {
    const usize        count = sccGraph.vertex_count();
    std::vector<usize> incoming(count, 0);
    std::vector<usize> sources;

    for (const auto& [from, edges] : sccGraph.adjacencies())
    {
        (void) from;

        for (const auto& [to, weight] : edges)
        {
            (void) weight;
            ++incoming[to];
        }
    }

    for (usize scc = 0; scc < count; ++scc)
        if (incoming[scc] == 0)
            sources.push_back(scc);

    return sources;
}

void airport_connections(const std::vector<std::string>&           airports,
                         const std::vector<std::array<std::string, 2>>& routes,
                         const std::string&                        startAirport) noexcept {
    const usize n = airports.size();
    const usize m = routes.size();

    std::cout << n << " " << m << "\n";

    if (n == 0)
    {
        std::cout << "No Input Airport List\n";
        return;
    }

    if (startAirport.empty())
    {
        std::cout << "No Starting Airport Provided\n";
        return;
    }

    Graph<std::string_view, GraphType::Directed> graph(n);

    for (auto& airport : airports)
    {
        std::cout << airport << "\n";
        graph.add_vertex(airport);
    }

    for (auto& route : routes)
    {
        std::cout << route[0] << " " << route[1] << "\n";
        graph.add_edge(route[0], route[1]);
    }

    std::cout << startAirport << "\n";

    std::cout << graph.to_string() << "\n\n";

    // Step 1: Find Strongly Connected Components (Kosaraju's Algorithm)
    StronglyConnectedComponents<std::string_view> scc(graph);

    const auto components = scc.find();

    for (usize i = 0; i < components.size(); ++i)
    {
        std::cout << "SCC " << i << ": {";

        const auto& component = components[i];

        for (usize j = 0; j < component.size(); ++j)
        {
            if (j != 0)
                std::cout << ", ";

            std::cout << component[j];
        }

        std::cout << "}\n";
    }

    // Step 2: Reduce graph to a Directed Acyclic Graph (DAG)
    auto [sccGraph, componentOf] = build_scc_graph(graph, components);

    std::cout << "\nSCC DAG:\n";

    for (const auto& [from, edges] : sccGraph.adjacencies())
    {
        std::cout << "SCC " << from << " -> ";

        for (const auto& [to, weight] : edges)
        {
            (void) weight;
            std::cout << "SCC " << to << " ";
        }

        std::cout << "\n";
    }
    std::cout << "\n";

    /*
    const auto reachable = find_reachable_sccs(startAirport, sccGraph, componentOf);

    std::cout << "\nReachable SCCs from " << startAirport << ":\n";

    for (const usize scc : reachable)
        std::cout << "SCC " << scc << '\n';
    */

    const auto reachable = calculate_reachability(sccGraph);

    for (usize i = 0; i < reachable.size(); ++i)
    {
        std::cout << "SCC " << i << " reaches: ";

        for (const usize scc : reachable[i])
            std::cout << scc << " ";

        std::cout << "\n";
    }
    std::cout << "\n";

    const auto sources = find_source_sccs(sccGraph);

    std::cout << "Source SCCs: (" << sources.size() << ")\n";

    for (const usize scc : sources)
        std::cout << "SCC " << scc << "\n";
    std::cout << "\n";

    std::cout << "Suggested new connections:\n";

    for (const usize scc : sources)
    {
        const auto& airportsInSCC = components[scc];

        if (!airportsInSCC.empty())
            std::cout << startAirport << " -> " << airportsInSCC.front() << "\n";
    }
    std::cout << "\n";
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    /*
    usize n, m;
    std::cin >> n >> m;

    std::vector<std::string> airports(n);
    for (usize i = 0; i < n; ++i)
    {
        std::string airport;
        std::cin >> airport;
        airports[i] = airport;
    }

    std::vector<std::array<std::string, 2>> routes(m);
    for (usize i = 0; i < m; ++i)
    {
        std::cin >> routes[i][0] >> routes[i][1];
        assert(routes[i][0] != routes[i][1]);
    }

    std::string startAirport;
    std::cin >> startAirport;
    */

    std::vector<std::string> airports{
      "BGI",  //
      "CDG",  //
      "DEL",  //
      "DOH",  //
      "DSM",  //
      "EWR",  //
      "EYW",  //
      "HND",  //
      "ICN",  //
      "JFK",  //
      "LGA",  //
      "LHR",  //
      "ORD",  //
      "SAN",  //
      "SFO",  //
      "SIN",  //
      "TLV",  //
      "BUD"   //
    };

    std::vector<std::array<std::string, 2>> routes{
      {"DSM", "ORD"},  //
      {"ORD", "BGI"},  //
      {"BGI", "LGA"},  //
      {"SIN", "CDG"},  //
      {"CDG", "SIN"},  //
      {"CDG", "BUD"},  //
      {"DEL", "DOH"},  //
      {"DEL", "CDG"},  //
      {"TLV", "DEL"},  //
      {"EWR", "HND"},  //
      {"HND", "ICN"},  //
      {"HND", "JFK"},  //
      {"ICN", "JFK"},  //
      {"JFK", "LGA"},  //
      {"EYW", "LHR"},  //
      {"LHR", "SFO"},  //
      {"SFO", "SAN"},  //
      {"SFO", "DSM"},  //
      {"SAN", "EYW"}   //
    };

    std::string startAirport = "LGA";


    airport_connections(airports, routes, startAirport);


    return 0;
}

/*

Steps:

mkdir -p build

g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic -I./src airport_connections.cpp -o build/airport_connections
g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic -DNDEBUG -I./src airport_connections.cpp -o build/airport_connections

./build/airport_connections
*/

/*
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

----------------------------------------------------
3

[
    type: Directed
    vertices: 18
    edges: 19
    components: 2
    component sizes:
        BUD: 6
        SFO: 12
        LGA: 12
        ICN: 12
        JFK: 12
        HND: 12
        SIN: 6
        EWR: 12
        SAN: 12
        ORD: 12
        EYW: 12
        DSM: 12
        DOH: 6
        TLV: 6
        DEL: 6
        LHR: 12
        CDG: 6
        BGI: 12
    adjacencies:
        BUD -> []
        SFO -> [DSM (0), SAN (0)]
        LGA -> []
        ICN -> [JFK (0)]
        JFK -> [LGA (0)]
        HND -> [JFK (0), ICN (0)]
        SIN -> [CDG (0)]
        EWR -> [HND (0)]
        SAN -> [EYW (0)]
        ORD -> [BGI (0)]
        EYW -> [LHR (0)]
        DSM -> [ORD (0)]
        DOH -> []
        TLV -> [DEL (0)]
        DEL -> [CDG (0), DOH (0)]
        LHR -> [SFO (0)]
        CDG -> [BUD (0), SIN (0)]
        BGI -> [LGA (0)]
]

SCC 0: {TLV}
SCC 1: {DEL}
SCC 2: {DOH}
SCC 3: {EWR}
SCC 4: {SIN, CDG}
SCC 5: {HND}
SCC 6: {ICN}
SCC 7: {JFK}
SCC 8: {SFO, LHR, EYW, SAN}
SCC 9: {DSM}
SCC 10: {ORD}
SCC 11: {BGI}
SCC 12: {LGA}
SCC 13: {BUD}

SCC DAG:
SCC 13 ->
SCC 12 ->
SCC 11 -> SCC 12
SCC 10 -> SCC 11
SCC 9 -> SCC 10
SCC 8 -> SCC 9
SCC 7 -> SCC 12
SCC 6 -> SCC 7
SCC 5 -> SCC 6 SCC 7
SCC 4 -> SCC 13
SCC 3 -> SCC 5
SCC 2 ->
SCC 1 -> SCC 2 SCC 4
SCC 0 -> SCC 1

SCC 0 reaches: 0 1 4 13 2
SCC 1 reaches: 1 4 13 2
SCC 2 reaches: 2
SCC 3 reaches: 3 5 7 12 6
SCC 4 reaches: 4 13
SCC 5 reaches: 5 7 12 6
SCC 6 reaches: 6 7 12
SCC 7 reaches: 7 12
SCC 8 reaches: 8 9 10 11 12
SCC 9 reaches: 9 10 11 12
SCC 10 reaches: 10 11 12
SCC 11 reaches: 11 12
SCC 12 reaches: 12
SCC 13 reaches: 13

Source SCCs: (3)
SCC 0
SCC 3
SCC 8

Suggested new connections:
LGA -> TLV
LGA -> EWR
LGA -> SFO
*/
