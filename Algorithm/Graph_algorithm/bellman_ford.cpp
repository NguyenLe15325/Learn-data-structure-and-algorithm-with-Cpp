/**
 * Title: Bellman-Ford Algorithm for Shortest Path
 * File: bellman_ford.cpp
 *
 * THE PROBLEM:
 * Bellman-Ford algorithm finds the shortest path from a source vertex to all other vertices
 * in a weighted graph. Unlike Dijkstra's, it works with NEGATIVE edge weights and can
 * detect negative-weight cycles.
 *
 * Applications:
 * - Currency arbitrage detection (negative cycle detection)
 * - Distributed shortest path algorithms
 * - Network routing in systems with negative weights
 * - Game development (cost-based pathfinding)
 *
 * COMPARISON WITH DIJKSTRA'S:
 * Dijkstra's:
 *   - Only works with non-negative weights
 *   - Faster: O((V+E)logV) with heap
 *   - Uses greedy approach
 *
 * Bellman-Ford:
 *   - Works with negative weights
 *   - Can detect negative cycles
 *   - Slower: O(V*E)
 *   - Uses dynamic programming approach
 *
 * THE ALGORITHM:
 * Bellman-Ford uses relaxation technique:
 * 1. Initialize distances: source = 0, all others = infinity
 * 2. Relax all edges (V-1) times:
 *    For each edge (u, v, weight):
 *       if distance[u] + weight < distance[v]:
 *           distance[v] = distance[u] + weight
 * 3. Check for negative cycles (optional):
 *    Try one more relaxation pass
 *    If any distance updates, negative cycle exists
 *
 * KEY INSIGHT:
 * After V-1 relaxations, all shortest paths are found (if no negative cycles).
 * This is because the longest simple path has at most V-1 edges.
 *
 * TIME COMPLEXITY: O(V*E)
 * SPACE COMPLEXITY: O(V)
 */

#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int u, v, weight;
};

// Weighted Graph Class for Bellman-Ford Algorithm using Edge List
class BellmanFordGraph {
private:
    int numVertices;
    vector<Edge> edges;

public:
    /**
     * @brief Constructor to initialize the graph with a given number of vertices.
     * @param vertices Number of vertices in the graph.
     */
    BellmanFordGraph(int vertices) : numVertices(vertices) {}

    /**
     * @brief Adds a weighted directed edge from u to v.
     * @param u Source vertex
     * @param v Destination vertex
     * @param weight Weight of the edge (can be negative)
     */
    void addEdge(int u, int v, int weight) {
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            edges.push_back({u, v, weight});
            cout << "Edge added: " << u << " -> " << v << " (weight: " << weight << ")" << endl;
        } else {
            cerr << "Error: Invalid vertices for edge!" << endl;
        }
    }

    /**
     * @brief Implements Bellman-Ford algorithm to find shortest paths from source.
     * Also detects negative-weight cycles.
     * @param source The source vertex
     */
    void bellmanFord(int source) {
        if (source < 0 || source >= numVertices) {
            cerr << "Error: Invalid source vertex!" << endl;
            return;
        }

        // Array to store the shortest distance from source to each vertex
        vector<long long> distance(numVertices, LLONG_MAX);

        // Array to store the previous vertex in the shortest path
        vector<int> previous(numVertices, -1);

        // Distance to source is 0
        distance[source] = 0;

        cout << "\n--- Bellman-Ford Shortest Path from vertex " << source << " ---" << endl;
        cout << "Total edges: " << edges.size() << endl;
        cout << "Number of relaxation passes: " << numVertices - 1 << endl << endl;

        // STEP 1: Relax all edges (V-1) times
        for (int pass = 1; pass <= numVertices - 1; ++pass) {
            cout << "Pass " << pass << ": Relaxing edges..." << endl;
            int updateCount = 0;

            for (const auto& edge : edges) {
                int u = edge.u;
                int v = edge.v;
                int w = edge.weight;

                // Relax the edge
                if (distance[u] != LLONG_MAX && distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    previous[v] = u;
                    updateCount++;
                    cout << "  Updated: distance[" << v << "] = " << distance[v] 
                         << " (via edge " << u << " -> " << v << ", weight: " << w << ")" << endl;
                }
            }

            if (updateCount == 0) {
                cout << "  No updates in this pass - distances converged!" << endl;
            }
            cout << endl;
        }

        // STEP 2: Check for negative-weight cycles
        cout << "--- Checking for Negative-Weight Cycles ---" << endl;
        bool hasNegativeCycle = false;
        for (const auto& edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int w = edge.weight;

            if (distance[u] != LLONG_MAX && distance[u] + w < distance[v]) {
                cout << "NEGATIVE CYCLE DETECTED: Edge " << u << " -> " << v 
                     << " can still be relaxed!" << endl;
                hasNegativeCycle = true;
            }
        }

        if (!hasNegativeCycle) {
            cout << "No negative cycles found - shortest paths are reliable!" << endl;
        } else {
            cout << "WARNING: Shortest paths may not be accurate due to negative cycle!" << endl;
        }

        // STEP 3: Display the shortest paths and distances
        cout << "\n--- Shortest Distances from vertex " << source << " ---" << endl;
        for (int v = 0; v < numVertices; ++v) {
            if (distance[v] == LLONG_MAX) {
                cout << "Vertex " << setw(2) << v << ": Unreachable" << endl;
            } else {
                cout << "Vertex " << setw(2) << v << ": Distance = " << setw(5) << distance[v];

                // Reconstruct path (only if no negative cycles and path exists)
                if (v != source && !hasNegativeCycle) {
                    vector<int> path;
                    int current = v;
                    int steps = 0;
                    const int MAX_STEPS = numVertices; // Prevent infinite loops from negative cycles
                    
                    while (current != -1 && steps < MAX_STEPS) {
                        path.push_back(current);
                        current = previous[current];
                        steps++;
                    }
                    
                    if (steps < MAX_STEPS) {
                        reverse(path.begin(), path.end());
                        cout << " | Path: ";
                        for (size_t i = 0; i < path.size(); ++i) {
                            cout << path[i];
                            if (i < path.size() - 1) cout << " -> ";
                        }
                    }
                }
                cout << endl;
            }
        }
    }

    /**
     * @brief Display all edges in the graph.
     */
    void displayGraph() {
        cout << "\n--- Graph (Edge List) ---" << endl;
        cout << "Vertices: " << numVertices << endl;
        cout << "Edges:" << endl;
        for (const auto& e : edges) {
            cout << "  " << e.u << " -> " << e.v << " (weight: " << e.weight << ")" << endl;
        }
    }
};

// Main function demonstrating Bellman-Ford Algorithm
int main() {
    cout << "=========================================" << endl;
    cout << "Bellman-Ford Algorithm - Shortest Path" << endl;
    cout << "=========================================" << endl;

    // Example 1: Simple graph without negative weights
    cout << "\n--- Example 1: Simple Graph (Non-negative Weights) ---" << endl;
    BellmanFordGraph graph1(5);
    graph1.addEdge(0, 1, 4);
    graph1.addEdge(0, 2, 2);
    graph1.addEdge(1, 2, 1);
    graph1.addEdge(1, 3, 5);
    graph1.addEdge(2, 3, 8);
    graph1.addEdge(2, 4, 10);
    graph1.addEdge(3, 4, 2);

    graph1.displayGraph();
    graph1.bellmanFord(0);

    // Example 2: Graph with negative weights (but no negative cycles)
    cout << "\n=========================================" << endl;
    cout << "--- Example 2: Graph with Negative Weights ---" << endl;
    BellmanFordGraph graph2(4);
    graph2.addEdge(0, 1, 4);
    graph2.addEdge(0, 2, 2);
    graph2.addEdge(1, 2, -3); // Negative edge
    graph2.addEdge(2, 3, 2);
    graph2.addEdge(1, 3, 2);

    graph2.displayGraph();
    graph2.bellmanFord(0);

    // Example 3: Graph with negative cycle
    cout << "\n=========================================" << endl;
    cout << "--- Example 3: Graph with Negative Cycle ---" << endl;
    BellmanFordGraph graph3(4);
    graph3.addEdge(0, 1, 1);
    graph3.addEdge(1, 2, -3);
    graph3.addEdge(2, 3, 2);
    graph3.addEdge(3, 1, -1); // Creates negative cycle: 1->2->3->1 = -3+2-1 = -2

    graph3.displayGraph();
    graph3.bellmanFord(0);

    // Example 4: Linear path with one negative edge
    cout << "\n=========================================" << endl;
    cout << "--- Example 4: Linear Path with Negative Edge ---" << endl;
    BellmanFordGraph graph4(5);
    graph4.addEdge(0, 1, 5);
    graph4.addEdge(1, 2, 3);
    graph4.addEdge(2, 3, -2); // Negative edge
    graph4.addEdge(3, 4, 1);
    graph4.addEdge(1, 3, 6); // Alternative path

    graph4.displayGraph();
    graph4.bellmanFord(0);

    // Example 5: Graph with multiple negative weights
    cout << "\n=========================================" << endl;
    cout << "--- Example 5: Graph with Multiple Negative Edges ---" << endl;
    BellmanFordGraph graph5(5);
    graph5.addEdge(0, 1, -1);
    graph5.addEdge(0, 2, 4);
    graph5.addEdge(1, 2, 3);
    graph5.addEdge(1, 3, 2);
    graph5.addEdge(1, 4, -4); // Negative edge
    graph5.addEdge(3, 2, 5);
    graph5.addEdge(3, 1, 1);
    graph5.addEdge(4, 3, -3); // Negative edge

    graph5.displayGraph();
    graph5.bellmanFord(0);

    // Example 6: Graph with unreachable vertices
    cout << "\n=========================================" << endl;
    cout << "--- Example 6: Graph with Unreachable Vertices ---" << endl;
    BellmanFordGraph graph6(6);
    graph6.addEdge(0, 1, 1);
    graph6.addEdge(1, 2, 2);
    graph6.addEdge(2, 0, 1);
    graph6.addEdge(3, 4, -1); // Disconnected component
    graph6.addEdge(4, 5, 1);

    graph6.displayGraph();
    graph6.bellmanFord(0);

    cout << "\n=========================================" << endl;
    cout << "--- Program Finished ---" << endl;
    cout << "=========================================" << endl;

    return 0;
}
