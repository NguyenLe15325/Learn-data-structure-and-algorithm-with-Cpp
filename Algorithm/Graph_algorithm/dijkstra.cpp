/**
 * Title: Dijkstra's Algorithm for Shortest Path
 * File: dijkstra.cpp
 *
 * THE PROBLEM:
 * Dijkstra's algorithm finds the shortest path from a source vertex to all other vertices
 * in a weighted graph with NON-NEGATIVE edge weights. It's one of the most popular shortest
 * path algorithms due to its efficiency and practical applications.
 *
 * Applications:
 * - GPS navigation systems (finding shortest routes)
 * - Network routing protocols (OSPF)
 * - Social networks (finding degrees of separation)
 * - Game AI pathfinding
 * - Telephone network routing
 *
 * THE ALGORITHM:
 * Dijkstra's uses a greedy approach:
 * 1. Initialize distances: source = 0, all others = infinity
 * 2. Mark all vertices as unvisited
 * 3. While unvisited vertices exist:
 *    a. Select the unvisited vertex with minimum distance
 *    b. Mark it as visited
 *    c. For each unvisited neighbor:
 *       - If path through current vertex is shorter, update distance
 * 4. Continue until all vertices are visited
 *
 * KEY PROPERTY:
 * Once a vertex is visited and its shortest distance is finalized, it cannot change.
 * This greedy property makes Dijkstra's efficient but only valid for non-negative weights.
 *
 * TIME COMPLEXITY: O(V²) with simple array, O((V+E)logV) with binary heap
 * SPACE COMPLEXITY: O(V)
 */

#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
#include <algorithm>

using namespace std;

// 1. Weighted Graph Class for Dijkstra's Algorithm using Adjacency Matrix
class DijkstraGraph {
private:
    int numVertices;
    vector<vector<int>> adjacencyMatrix;

public:
    /**
     * @brief Constructor to initialize the graph with a given number of vertices.
     * @param vertices Number of vertices in the graph.
     */
    DijkstraGraph(int vertices) : numVertices(vertices), adjacencyMatrix(vertices, vector<int>(vertices, 0)) {}

    /**
     * @brief Adds a weighted directed edge from u to v.
     * @param u Source vertex
     * @param v Destination vertex
     * @param weight Weight of the edge
     */
    void addEdge(int u, int v, int weight) {
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            adjacencyMatrix[u][v] = weight;
            cout << "Edge added: " << u << " -> " << v << " (weight: " << weight << ")" << endl;
        } else {
            cerr << "Error: Invalid vertices for edge!" << endl;
        }
    }

    /**
     * @brief Finds the unvisited vertex with the minimum distance.
     * @param distance Array of distances from source
     * @param visited Array tracking visited vertices
     * @return Index of vertex with minimum distance
     */
    int findMinDistanceVertex(vector<int>& distance, vector<bool>& visited) {
        int minDistance = INT_MAX;
        int minVertex = -1;

        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v] && distance[v] < minDistance) {
                minDistance = distance[v];
                minVertex = v;
            }
        }
        return minVertex;
    }

    /**
     * @brief Implements Dijkstra's algorithm to find shortest paths from source to all vertices.
     * @param source The source vertex
     */
    void dijkstra(int source) {
        if (source < 0 || source >= numVertices) {
            cerr << "Error: Invalid source vertex!" << endl;
            return;
        }

        // Array to store the shortest distance from source to each vertex
        vector<int> distance(numVertices, INT_MAX);

        // Array to track visited vertices
        vector<bool> visited(numVertices, false);

        // Array to store the previous vertex in the shortest path
        vector<int> previous(numVertices, -1);

        // Distance to source is 0
        distance[source] = 0;

        cout << "\n--- Dijkstra's Shortest Path from vertex " << source << " ---" << endl;
        cout << "Processing vertices..." << endl << endl;

        // Process all vertices
        for (int count = 0; count < numVertices; ++count) {
            // Find the unvisited vertex with minimum distance
            int u = findMinDistanceVertex(distance, visited);

            if (u == -1) {
                // No more reachable vertices
                break;
            }

            // Mark the vertex as visited
            visited[u] = true;

            if (distance[u] == INT_MAX) {
                cout << "Vertex " << u << ": Unreachable" << endl;
            } else {
                cout << "Step " << count + 1 << ": Selected vertex " << u 
                     << " with distance " << distance[u];
                if (previous[u] != -1) {
                    cout << " (from vertex " << previous[u] << ")";
                }
                cout << endl;
            }

            // Update distances to adjacent vertices
            for (int v = 0; v < numVertices; ++v) {
                if (adjacencyMatrix[u][v] != 0 && !visited[v]) {
                    int newDistance = distance[u] + adjacencyMatrix[u][v];

                    if (newDistance < distance[v]) {
                        distance[v] = newDistance;
                        previous[v] = u;
                        cout << "  Updated distance to vertex " << v << ": " << newDistance << endl;
                    }
                }
            }
        }

        // Display the shortest paths and distances
        cout << "\n--- Shortest Distances from vertex " << source << " ---" << endl;
        for (int v = 0; v < numVertices; ++v) {
            if (distance[v] == INT_MAX) {
                cout << "Vertex " << setw(2) << v << ": Unreachable" << endl;
            } else {
                cout << "Vertex " << setw(2) << v << ": Distance = " << setw(3) << distance[v];
                
                // Reconstruct path
                if (v != source) {
                    vector<int> path;
                    int current = v;
                    while (current != -1) {
                        path.push_back(current);
                        current = previous[current];
                    }
                    reverse(path.begin(), path.end());

                    cout << " | Path: ";
                    for (size_t i = 0; i < path.size(); ++i) {
                        cout << path[i];
                        if (i < path.size() - 1) cout << " -> ";
                    }
                }
                cout << endl;
            }
        }
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
                if (adjacencyMatrix[i][j] == 0) {
                    cout << setw(3) << "-";
                } else {
                    cout << setw(3) << adjacencyMatrix[i][j];
                }
            }
            cout << endl;
        }
    }
};

// Main function demonstrating Dijkstra's Algorithm
int main() {
    cout << "=========================================" << endl;
    cout << "Dijkstra's Algorithm - Shortest Path" << endl;
    cout << "=========================================" << endl;

    // Example 1: Simple weighted directed graph
    cout << "\n--- Example 1: Simple Directed Graph ---" << endl;
    DijkstraGraph graph1(5);
    graph1.addEdge(0, 1, 4);
    graph1.addEdge(0, 2, 2);
    graph1.addEdge(1, 2, 1);
    graph1.addEdge(1, 3, 5);
    graph1.addEdge(2, 3, 8);
    graph1.addEdge(2, 4, 10);
    graph1.addEdge(3, 4, 2);

    graph1.displayGraph();
    graph1.dijkstra(0);

    // Example 2: Different starting vertex
    cout << "\n=========================================" << endl;
    cout << "--- Example 2: Starting from Different Vertex ---" << endl;
    graph1.dijkstra(2);

    // Example 3: More complex graph
    cout << "\n=========================================" << endl;
    cout << "--- Example 3: Complex Network ---" << endl;
    DijkstraGraph graph3(6);
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
    graph3.dijkstra(0);

    // Example 4: Graph with disconnected component
    cout << "\n=========================================" << endl;
    cout << "--- Example 4: Graph with Unreachable Vertices ---" << endl;
    DijkstraGraph graph4(5);
    graph4.addEdge(0, 1, 5);
    graph4.addEdge(1, 2, 3);
    graph4.addEdge(2, 1, 2);
    graph4.addEdge(3, 4, 7); // Disconnected component

    graph4.displayGraph();
    graph4.dijkstra(0);

    // Example 5: Linear path graph
    cout << "\n=========================================" << endl;
    cout << "--- Example 5: Linear Path Graph ---" << endl;
    DijkstraGraph graph5(6);
    graph5.addEdge(0, 1, 1);
    graph5.addEdge(1, 2, 2);
    graph5.addEdge(2, 3, 3);
    graph5.addEdge(3, 4, 4);
    graph5.addEdge(4, 5, 5);

    graph5.displayGraph();
    graph5.dijkstra(0);

    // Example 6: Dense graph with many shortcuts
    cout << "\n=========================================" << endl;
    cout << "--- Example 6: Dense Graph with Shortcuts ---" << endl;
    DijkstraGraph graph6(5);
    graph6.addEdge(0, 1, 10);
    graph6.addEdge(0, 2, 5);
    graph6.addEdge(1, 2, 3);
    graph6.addEdge(1, 3, 1);
    graph6.addEdge(2, 1, 2);
    graph6.addEdge(2, 3, 9);
    graph6.addEdge(2, 4, 2);
    graph6.addEdge(3, 4, 4);
    graph6.addEdge(4, 3, 6);
    graph6.addEdge(4, 0, 7);

    graph6.displayGraph();
    graph6.dijkstra(0);

    cout << "\n=========================================" << endl;
    cout << "--- Program Finished ---" << endl;
    cout << "=========================================" << endl;

    return 0;
}
