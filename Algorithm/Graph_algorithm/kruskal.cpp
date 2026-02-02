/**
 * Title: Kruskal's Algorithm for Minimum Spanning Tree (MST)
 * File: kruskal.cpp
 *
 * THE PROBLEM:
 * A Minimum Spanning Tree (MST) is a subset of edges of a connected, weighted graph that 
 * connects all vertices together with the minimum possible total edge weight. It has exactly 
 * (V-1) edges for V vertices and contains no cycles.
 *
 * Applications:
 * - Network design (minimizing cable/fiber length)
 * - Clustering data points
 * - Image processing
 * - Approximating traveling salesman problem
 *
 * KRUSKAL'S ALGORITHM:
 * Kruskal's algorithm builds the MST by sorting all edges by weight and greedily adding 
 * edges that don't create a cycle. It uses Union-Find (Disjoint Set Union) data structure 
 * to efficiently detect cycles.
 *
 * GREEDY STRATEGY:
 * 1. Sort all edges by weight in ascending order
 * 2. Create a disjoint set for each vertex
 * 3. For each edge in sorted order:
 *    a. If the two vertices are not in the same set:
 *       - Add the edge to MST
 *       - Union the two sets
 * 4. Stop when (V-1) edges have been added to MST
 *
 * TIME COMPLEXITY: O(E log E) for sorting edges + O(E α(V)) for union-find
 * SPACE COMPLEXITY: O(V + E)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Structure to represent an edge
struct Edge {
    int u, v, weight;

    // Comparison operator for sorting edges by weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Union-Find (Disjoint Set Union) Data Structure
class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;

public:
    /**
     * @brief Constructor to initialize the union-find structure with n elements.
     * @param n Number of elements
     */
    UnionFind(int n) : parent(n), rank(n, 0) {
        // Initially, each element is its own parent
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    /**
     * @brief Find the root/representative of the set containing x (with path compression).
     * @param x Element to find
     * @return Root of the set containing x
     */
    int find(int x) {
        if (parent[x] != x) {
            // Path compression: make x point directly to root
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    /**
     * @brief Union two sets containing x and y (with union by rank).
     * @param x Element from first set
     * @param y Element from second set
     * @return true if union was performed, false if already in same set
     */
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        // If already in same set, return false
        if (rootX == rootY) {
            return false;
        }

        // Union by rank: attach smaller rank tree under larger rank tree
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

    /**
     * @brief Check if two elements are in the same set.
     * @param x First element
     * @param y Second element
     * @return true if in same set, false otherwise
     */
    bool isSameSet(int x, int y) {
        return find(x) == find(y);
    }
};

// 1. Weighted Graph Class for Kruskal's Algorithm using Edge List
class KruskalGraph {
private:
    int numVertices;
    vector<Edge> edges;

public:
    /**
     * @brief Constructor to initialize the graph with a given number of vertices.
     * @param vertices Number of vertices in the graph.
     */
    KruskalGraph(int vertices) : numVertices(vertices) {}

    /**
     * @brief Adds an undirected weighted edge between two vertices.
     * @param u Source vertex
     * @param v Destination vertex
     * @param weight Weight of the edge
     */
    void addEdge(int u, int v, int weight) {
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            edges.push_back({u, v, weight});
            cout << "Edge added: " << u << " -- " << v << " (weight: " << weight << ")" << endl;
        } else {
            cerr << "Error: Invalid vertices for edge!" << endl;
        }
    }

    /**
     * @brief Implements Kruskal's algorithm to find the MST.
     */
    void kruskalMST() {
        cout << "\n--- Kruskal's MST Algorithm ---" << endl;
        cout << "Total vertices: " << numVertices << endl;
        cout << "Total edges: " << edges.size() << endl << endl;

        // Step 1: Sort all edges by weight
        cout << "Edges before sorting:" << endl;
        for (const auto& e : edges) {
            cout << "  " << e.u << " -- " << e.v << " (weight: " << e.weight << ")" << endl;
        }

        sort(edges.begin(), edges.end());

        cout << "\nEdges after sorting by weight:" << endl;
        for (const auto& e : edges) {
            cout << "  " << e.u << " -- " << e.v << " (weight: " << e.weight << ")" << endl;
        }

        // Step 2: Initialize Union-Find
        UnionFind uf(numVertices);

        vector<Edge> mstEdges;
        int totalWeight = 0;

        cout << "\n--- Processing Edges ---" << endl;

        // Step 3: Process edges in sorted order
        for (const auto& e : edges) {
            // If the edge connects two different components (no cycle)
            if (uf.unite(e.u, e.v)) {
                mstEdges.push_back(e);
                totalWeight += e.weight;
                cout << "Step " << mstEdges.size() << ": Added edge " << e.u << " -- " << e.v 
                     << " (weight: " << e.weight << ") - Components united" << endl;

                // If we have V-1 edges, MST is complete
                if (mstEdges.size() == numVertices - 1) {
                    break;
                }
            } else {
                cout << "        Skipped edge " << e.u << " -- " << e.v 
                     << " (weight: " << e.weight << ") - Would create cycle" << endl;
            }
        }

        // Display the MST
        cout << "\n--- Minimum Spanning Tree ---" << endl;
        cout << "Edges in MST:" << endl;
        for (const auto& e : mstEdges) {
            cout << "  " << e.u << " -- " << e.v << " (weight: " << e.weight << ")" << endl;
        }

        cout << "\nTotal weight of MST: " << totalWeight << endl;
        cout << "Number of edges in MST: " << mstEdges.size() << endl;
    }

    /**
     * @brief Display all edges in the graph.
     */
    void displayGraph() {
        cout << "\n--- Graph (Edge List) ---" << endl;
        cout << "Vertices: " << numVertices << endl;
        cout << "Edges:" << endl;
        for (const auto& e : edges) {
            cout << "  " << e.u << " -- " << e.v << " (weight: " << e.weight << ")" << endl;
        }
    }
};

// Main function demonstrating Kruskal's Algorithm
int main() {
    cout << "=========================================" << endl;
    cout << "Kruskal's Algorithm - Minimum Spanning Tree" << endl;
    cout << "=========================================" << endl;

    // Example 1: Basic MST
    cout << "\n--- Example 1: Simple Weighted Graph ---" << endl;
    KruskalGraph graph1(5);
    graph1.addEdge(0, 1, 2);
    graph1.addEdge(0, 3, 6);
    graph1.addEdge(1, 2, 3);
    graph1.addEdge(1, 3, 8);
    graph1.addEdge(1, 4, 5);
    graph1.addEdge(2, 4, 7);
    graph1.addEdge(3, 4, 9);

    graph1.displayGraph();
    graph1.kruskalMST();

    // Example 2: Different graph
    cout << "\n=========================================" << endl;
    cout << "--- Example 2: Another Weighted Graph ---" << endl;
    KruskalGraph graph2(4);
    graph2.addEdge(0, 1, 1);
    graph2.addEdge(0, 2, 4);
    graph2.addEdge(1, 2, 2);
    graph2.addEdge(1, 3, 5);
    graph2.addEdge(2, 3, 3);

    graph2.displayGraph();
    graph2.kruskalMST();

    // Example 3: More complex graph
    cout << "\n=========================================" << endl;
    cout << "--- Example 3: Complex Weighted Graph ---" << endl;
    KruskalGraph graph3(6);
    graph3.addEdge(0, 1, 4);
    graph3.addEdge(0, 2, 2);
    graph3.addEdge(1, 2, 1);
    graph3.addEdge(1, 3, 5);
    graph3.addEdge(2, 3, 8);
    graph3.addEdge(2, 4, 10);
    graph3.addEdge(3, 4, 2);
    graph3.addEdge(3, 5, 6);
    graph3.addEdge(4, 5, 3);

    graph3.displayGraph();
    graph3.kruskalMST();

    // Example 4: Graph with multiple same-weight edges
    cout << "\n=========================================" << endl;
    cout << "--- Example 4: Graph with Equal Weight Edges ---" << endl;
    KruskalGraph graph4(5);
    graph4.addEdge(0, 1, 5);
    graph4.addEdge(1, 2, 5);
    graph4.addEdge(2, 3, 5);
    graph4.addEdge(3, 4, 5);
    graph4.addEdge(0, 4, 5);

    graph4.displayGraph();
    graph4.kruskalMST();

    // Example 5: Star-shaped graph
    cout << "\n=========================================" << endl;
    cout << "--- Example 5: Star-Shaped Graph ---" << endl;
    KruskalGraph graph5(5);
    graph5.addEdge(0, 1, 1);
    graph5.addEdge(0, 2, 2);
    graph5.addEdge(0, 3, 3);
    graph5.addEdge(0, 4, 4);

    graph5.displayGraph();
    graph5.kruskalMST();

    cout << "\n=========================================" << endl;
    cout << "--- Program Finished ---" << endl;
    cout << "=========================================" << endl;

    return 0;
}
