/**
 * Title: Prim's Algorithm for Minimum Spanning Tree (MST)
 * File: prim.cpp
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
 * PRIM'S ALGORITHM:
 * Prim's algorithm builds the MST one edge at a time by always selecting the minimum weight 
 * edge that connects a vertex in the tree to a vertex outside the tree.
 *
 * GREEDY STRATEGY:
 * 1. Start with any vertex (typically vertex 0)
 * 2. Mark it as part of the MST
 * 3. Repeat until all vertices are in the MST:
 *    a. Find the minimum weight edge that connects a vertex in MST to one outside MST
 *    b. Add that edge and vertex to the MST
 *    c. Update the minimum edges for remaining vertices
 * 4. Stop when all vertices are included
 *
 * TIME COMPLEXITY: O(V²) with simple array, O((V+E)logV) with binary heap
 * SPACE COMPLEXITY: O(V²) for adjacency matrix or O(V+E) for adjacency list
 */

#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;

// Structure to represent an edge with weight
struct Edge {
    int u, v, weight;
};

// 1. Weighted Graph Class for Prim's Algorithm using Adjacency Matrix
class PrimGraph {
private:
    int numVertices;
    vector<vector<int>> adjacencyMatrix;

public:
    /**
     * @brief Constructor to initialize the graph with a given number of vertices.
     * @param vertices Number of vertices in the graph.
     */
    PrimGraph(int vertices) : numVertices(vertices), adjacencyMatrix(vertices, vector<int>(vertices, 0)) {}

    /**
     * @brief Adds an undirected weighted edge between two vertices.
     * @param u Source vertex
     * @param v Destination vertex
     * @param weight Weight of the edge
     */
    void addEdge(int u, int v, int weight) {
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            adjacencyMatrix[u][v] = weight;
            adjacencyMatrix[v][u] = weight; // Undirected graph
            cout << "Edge added: " << u << " -- " << v << " (weight: " << weight << ")" << endl;
        } else {
            cerr << "Error: Invalid vertices for edge!" << endl;
        }
    }

    /**
     * @brief Finds the vertex with minimum key value not yet in MST.
     * @param key Array of minimum weights to reach each vertex
     * @param inMST Array tracking which vertices are in the MST
     * @return Index of vertex with minimum key value
     */
    int findMinKeyVertex(vector<int>& key, vector<bool>& inMST) {
        int minKey = INT_MAX;
        int minVertex = -1;

        for (int v = 0; v < numVertices; ++v) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                minVertex = v;
            }
        }
        return minVertex;
    }

    /**
     * @brief Implements Prim's algorithm to find the MST starting from a given vertex.
     * @param startVertex The vertex to start MST construction from.
     */
    void primMST(int startVertex) {
        if (startVertex < 0 || startVertex >= numVertices) {
            cerr << "Error: Invalid start vertex!" << endl;
            return;
        }

        // Array to store the minimum key value for each vertex
        vector<int> key(numVertices, INT_MAX);

        // Array to track which vertices are included in the MST
        vector<bool> inMST(numVertices, false);

        // Array to store the parent of each vertex in MST
        vector<int> parent(numVertices, -1);

        // Start with the given vertex
        key[startVertex] = 0;

        cout << "\n--- Prim's MST starting from vertex " << startVertex << " ---" << endl;
        cout << "Total edges to process: " << numVertices << endl << endl;

        // Process all vertices
        for (int count = 0; count < numVertices; ++count) {
            // Find the vertex with minimum key value not in MST
            int u = findMinKeyVertex(key, inMST);

            if (u == -1) {
                cout << "Error: Graph is not connected!" << endl;
                return;
            }

            // Add the vertex to MST
            inMST[u] = true;

            if (parent[u] != -1) {
                cout << "Step " << count << ": Added edge " << parent[u] << " -- " << u 
                     << " (weight: " << key[u] << ")" << endl;
            } else {
                cout << "Step " << count << ": Starting vertex " << u << " (key: 0)" << endl;
            }

            // Update key values of adjacent vertices
            for (int v = 0; v < numVertices; ++v) {
                if (adjacencyMatrix[u][v] != 0 && !inMST[v] && adjacencyMatrix[u][v] < key[v]) {
                    key[v] = adjacencyMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        // Display the MST
        cout << "\n--- Minimum Spanning Tree ---" << endl;
        cout << "Edges in MST:" << endl;

        int totalWeight = 0;
        for (int v = 1; v < numVertices; ++v) {
            if (parent[v] != -1) {
                int weight = adjacencyMatrix[parent[v]][v];
                cout << "  " << parent[v] << " -- " << v << " (weight: " << weight << ")" << endl;
                totalWeight += weight;
            }
        }

        cout << "\nTotal weight of MST: " << totalWeight << endl;
    }

    /**
     * @brief Display the adjacency matrix representation of the graph.
     */
    void displayGraph() {
        cout << "\n--- Graph (Adjacency Matrix) ---" << endl;
        cout << "    ";
        for (int i = 0; i < numVertices; ++i) {
            cout << setw(3) << i;
        }
        cout << endl;

        for (int i = 0; i < numVertices; ++i) {
            cout << setw(2) << i << ": ";
            for (int j = 0; j < numVertices; ++j) {
                cout << setw(3) << adjacencyMatrix[i][j];
            }
            cout << endl;
        }
    }
};

// Main function demonstrating Prim's Algorithm
int main() {
    cout << "=========================================" << endl;
    cout << "Prim's Algorithm - Minimum Spanning Tree" << endl;
    cout << "=========================================" << endl;

    // Example 1: Basic MST
    cout << "\n--- Example 1: Simple Weighted Graph ---" << endl;
    PrimGraph graph1(5);
    graph1.addEdge(0, 1, 2);
    graph1.addEdge(0, 3, 6);
    graph1.addEdge(1, 2, 3);
    graph1.addEdge(1, 3, 8);
    graph1.addEdge(1, 4, 5);
    graph1.addEdge(2, 4, 7);
    graph1.addEdge(3, 4, 9);

    graph1.displayGraph();
    graph1.primMST(0);

    // Example 2: Different starting vertex
    cout << "\n=========================================" << endl;
    cout << "--- Example 2: MST Starting from Different Vertex ---" << endl;
    PrimGraph graph2(4);
    graph2.addEdge(0, 1, 1);
    graph2.addEdge(0, 2, 4);
    graph2.addEdge(1, 2, 2);
    graph2.addEdge(1, 3, 5);
    graph2.addEdge(2, 3, 3);

    graph2.displayGraph();
    cout << "\nStarting from vertex 1:" << endl;
    graph2.primMST(1);

    // Example 3: More complex graph
    cout << "\n=========================================" << endl;
    cout << "--- Example 3: Complex Weighted Graph ---" << endl;
    PrimGraph graph3(6);
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
    graph3.primMST(0);

    // Example 4: Star-shaped graph
    cout << "\n=========================================" << endl;
    cout << "--- Example 4: Star-Shaped Graph ---" << endl;
    PrimGraph graph4(5);
    graph4.addEdge(0, 1, 1);
    graph4.addEdge(0, 2, 2);
    graph4.addEdge(0, 3, 3);
    graph4.addEdge(0, 4, 4);

    graph4.displayGraph();
    graph4.primMST(0);

    cout << "\n=========================================" << endl;
    cout << "--- Program Finished ---" << endl;
    cout << "=========================================" << endl;

    return 0;
}
