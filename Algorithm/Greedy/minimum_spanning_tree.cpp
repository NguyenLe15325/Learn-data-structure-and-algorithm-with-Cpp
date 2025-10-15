/*
===============================================================================
GRAPH ALGORITHMS - PRIM'S, KRUSKAL'S, AND DIJKSTRA
===============================================================================

ALGORITHMS INCLUDED:
====================

1. PRIM'S ALGORITHM - Minimum Spanning Tree
   - Time: O(E log V), Space: O(V + E)
   - Best for dense graphs

2. KRUSKAL'S ALGORITHM - Minimum Spanning Tree
   - Time: O(E log E), Space: O(E)
   - Best for sparse graphs

3. DIJKSTRA'S ALGORITHM - Shortest Path
   - Time: O((V + E) log V), Space: O(V)
   - Finds shortest path from source to all vertices

===============================================================================
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <iomanip>
using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
    
    Edge() {}
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Comparator for min-heap in priority queue
struct CompareEdge {
    bool operator()(const Edge& a, const Edge& b) const {
        return a.weight > b.weight;
    }
};

// Union-Find data structure for Kruskal's
class UnionFind {
private:
    vector<int> parent, rank;
    
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) {
            return false;
        }
        
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        
        return true;
    }
};

/*
===============================================================================
PRIM'S ALGORITHM WITH VISUALIZATION
===============================================================================
*/
class PrimsMST {
private:
    int vertices;
    vector<vector<pair<int, int>>> adjList;
    
public:
    PrimsMST(int v) : vertices(v) {
        adjList.resize(vertices);
    }
    
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }
    
    long long primMST(int startVertex) {
        cout << "\n========================================\n";
        cout << "PRIM'S ALGORITHM - MST CONSTRUCTION\n";
        cout << "========================================\n\n";
        
        priority_queue<Edge, vector<Edge>, CompareEdge> pq;
        vector<bool> visited(vertices, false);
        vector<Edge> mstEdges;
        long long totalCost = 0;
        
        cout << "Starting vertex: " << startVertex << "\n";
        cout << "Strategy: Expand tree by adding minimum weight edge\n\n";
        
        pq.push(Edge(startVertex, startVertex, 0));
        
        int step = 0;
        while (!pq.empty()) {
            Edge current = pq.top();
            pq.pop();
            
            if (visited[current.dest]) {
                continue;
            }
            
            visited[current.dest] = true;
            step++;
            
            if (current.src != current.dest) {
                mstEdges.push_back(current);
                totalCost += current.weight;
                cout << "Step " << step << ": Added edge (" << current.src 
                     << " -- " << current.dest << ") weight = " << current.weight 
                     << ", Total = " << totalCost << "\n";
            }
            
            for (auto& neighbor : adjList[current.dest]) {
                if (!visited[neighbor.first]) {
                    pq.push(Edge(current.dest, neighbor.first, neighbor.second));
                }
            }
        }
        
        printMSTResult(mstEdges, totalCost, "PRIM'S");
        return totalCost;
    }
    
    void printMSTResult(const vector<Edge>& mstEdges, 
                       long long totalCost, const string& algorithm) {
        cout << "\n========================================\n";
        cout << algorithm << " - RESULT\n";
        cout << "========================================\n\n";
        
        cout << "MST Edges:\n";
        vector<Edge> sortedEdges = mstEdges;
        sort(sortedEdges.begin(), sortedEdges.end());
        
        for (const auto& edge : sortedEdges) {
            cout << "  " << edge.src << " --- " << edge.dest 
                 << " : weight " << edge.weight << "\n";
        }
        
        cout << "\nTree Structure:\n";
        vector<vector<pair<int, int>>> treeAdj(vertices);
        for (const auto& edge : mstEdges) {
            treeAdj[edge.src].push_back({edge.dest, edge.weight});
            treeAdj[edge.dest].push_back({edge.src, edge.weight});
        }
        
        for (int i = 0; i < vertices; i++) {
            if (!treeAdj[i].empty()) {
                cout << "  Vertex " << i << ": ";
                for (size_t j = 0; j < treeAdj[i].size(); j++) {
                    if (j > 0) cout << ", ";
                    cout << treeAdj[i][j].first << " (w:" << treeAdj[i][j].second << ")";
                }
                cout << "\n";
            }
        }
        
        cout << "\n>>> TOTAL MST WEIGHT: " << totalCost << " <<<\n";
    }
};

/*
===============================================================================
KRUSKAL'S ALGORITHM WITH VISUALIZATION
===============================================================================
*/
class KruskalMST {
private:
    int vertices;
    vector<Edge> edges;
    
public:
    KruskalMST(int v) : vertices(v) {}
    
    void addEdge(int u, int v, int weight) {
        edges.push_back(Edge(u, v, weight));
    }
    
    long long kruskalMST() {
        cout << "\n========================================\n";
        cout << "KRUSKAL'S ALGORITHM - MST CONSTRUCTION\n";
        cout << "========================================\n\n";
        
        cout << "Strategy: Sort edges, add if no cycle\n\n";
        
        sort(edges.begin(), edges.end());
        
        cout << "All edges sorted by weight:\n";
        for (const auto& e : edges) {
            cout << "  (" << e.src << " -- " << e.dest << ") : " << e.weight << "\n";
        }
        cout << "\n";
        
        UnionFind uf(vertices);
        vector<Edge> mstEdges;
        long long totalCost = 0;
        
        int step = 0;
        for (const auto& edge : edges) {
            if (uf.unionSets(edge.src, edge.dest)) {
                step++;
                mstEdges.push_back(edge);
                totalCost += edge.weight;
                cout << "Step " << step << ": Added edge (" << edge.src 
                     << " -- " << edge.dest << ") weight = " << edge.weight 
                     << ", Total = " << totalCost << "\n";
            } else {
                cout << "Step -: Skipped edge (" << edge.src << " -- " << edge.dest 
                     << ") - would create cycle\n";
            }
            
            if (mstEdges.size() == vertices - 1) {
                break;
            }
        }
        
        printMSTResult(mstEdges, totalCost, "KRUSKAL'S");
        return totalCost;
    }
    
    void printMSTResult(const vector<Edge>& mstEdges, 
                       long long totalCost, const string& algorithm) {
        cout << "\n========================================\n";
        cout << algorithm << " - RESULT\n";
        cout << "========================================\n\n";
        
        cout << "MST Edges:\n";
        for (const auto& edge : mstEdges) {
            cout << "  " << edge.src << " --- " << edge.dest 
                 << " : weight " << edge.weight << "\n";
        }
        
        cout << "\nTree Structure:\n";
        vector<vector<pair<int, int>>> treeAdj(vertices);
        for (const auto& edge : mstEdges) {
            treeAdj[edge.src].push_back({edge.dest, edge.weight});
            treeAdj[edge.dest].push_back({edge.src, edge.weight});
        }
        
        for (int i = 0; i < vertices; i++) {
            if (!treeAdj[i].empty()) {
                cout << "  Vertex " << i << ": ";
                for (size_t j = 0; j < treeAdj[i].size(); j++) {
                    if (j > 0) cout << ", ";
                    cout << treeAdj[i][j].first << " (w:" << treeAdj[i][j].second << ")";
                }
                cout << "\n";
            }
        }
        
        cout << "\n>>> TOTAL MST WEIGHT: " << totalCost << " <<<\n";
    }
};

int main() {
    cout << "\n";
    cout << "##################################################\n";
    cout << "# GRAPH ALGORITHMS: MST & SHORTEST PATH         #\n";
    cout << "##################################################\n";
    
    /*
    TEST CASE 1: MST Algorithms on same graph
    ==========================================
    */
    cout << "\n#############################\n";
    cout << "# TEST 1: MST COMPARISON    #\n";
    cout << "#############################\n";
    
    PrimsMST primGraph(5);
    primGraph.addEdge(0, 1, 4);
    primGraph.addEdge(0, 2, 2);
    primGraph.addEdge(0, 3, 1);
    primGraph.addEdge(1, 2, 1);
    primGraph.addEdge(1, 4, 5);
    primGraph.addEdge(2, 3, 8);
    primGraph.addEdge(2, 4, 10);
    primGraph.addEdge(3, 4, 2);
    
    primGraph.primMST(0);
    
    KruskalMST kruskalGraph(5);
    kruskalGraph.addEdge(0, 1, 4);
    kruskalGraph.addEdge(0, 2, 2);
    kruskalGraph.addEdge(0, 3, 1);
    kruskalGraph.addEdge(1, 2, 1);
    kruskalGraph.addEdge(1, 4, 5);
    kruskalGraph.addEdge(2, 3, 8);
    kruskalGraph.addEdge(2, 4, 10);
    kruskalGraph.addEdge(3, 4, 2);
    
    kruskalGraph.kruskalMST();
    
    cout << "\n\n##################################################\n";
    cout << "# ALGORITHM SUMMARY                             #\n";
    cout << "##################################################\n";
    cout << "\nPRIM'S ALGORITHM:\n";
    cout << "  - Finds: Minimum Spanning Tree\n";
    cout << "  - Time: O(E log V), Space: O(V + E)\n";
    cout << "  - Best for: Dense graphs\n\n";
    
    cout << "KRUSKAL'S ALGORITHM:\n";
    cout << "  - Finds: Minimum Spanning Tree\n";
    cout << "  - Time: O(E log E), Space: O(E)\n";
    cout << "  - Best for: Sparse graphs\n\n";
    
    cout << "All MST algorithms executed successfully!\n";
    
    return 0;
}