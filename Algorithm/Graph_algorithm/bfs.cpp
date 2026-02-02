/**
 * Title: Breadth-First Search (BFS) Algorithm
 * File: bfs.cpp
 *
 * THE PROBLEM:
 * Breadth-First Search (BFS) is a fundamental graph traversal algorithm used to explore 
 * all vertices (nodes) in a graph in breadth-first order. Starting from a source vertex, 
 * BFS explores all neighbors at the present depth level before moving to vertices at 
 * the next depth level. This is commonly used for:
 * - Finding the shortest path in unweighted graphs
 * - Level-order traversal of trees
 * - Detecting cycles in graphs
 * - Social network analysis (finding degrees of separation)
 * - Robot path planning
 *
 * THE ALGORITHM:
 * 1. Create a queue and add the source vertex to it
 * 2. Mark the source vertex as visited
 * 3. While the queue is not empty:
 *    a. Dequeue a vertex from the queue
 *    b. Process the vertex (print it, record it, etc.)
 *    c. For each neighbor of the current vertex:
 *       - If not visited, mark as visited and enqueue it
 * 4. Repeat until the queue is empty
 *
 * TIME COMPLEXITY: O(V + E) where V is the number of vertices and E is the number of edges
 * SPACE COMPLEXITY: O(V) for the visited array and queue
 */

#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

// 1. Graph Class using Adjacency List representation
class Graph {
private:
    int numVertices;
    vector<vector<int>> adjacencyList;

public:
    /**
     * @brief Constructor to initialize the graph with a given number of vertices.
     * @param vertices Number of vertices in the graph.
     */
    Graph(int vertices) : numVertices(vertices), adjacencyList(vertices) {}

    /**
     * @brief Adds an undirected edge between two vertices.
     * @param u Source vertex
     * @param v Destination vertex
     */
    void addEdge(int u, int v) {
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            adjacencyList[u].push_back(v);
            adjacencyList[v].push_back(u); // For undirected graph
            cout << "Edge added: " << u << " -- " << v << endl;
        } else {
            cerr << "Error: Invalid vertices for edge!" << endl;
        }
    }

    /**
     * @brief Adds a directed edge from u to v.
     * @param u Source vertex
     * @param v Destination vertex
     */
    void addDirectedEdge(int u, int v) {
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            adjacencyList[u].push_back(v);
            cout << "Directed edge added: " << u << " -> " << v << endl;
        } else {
            cerr << "Error: Invalid vertices for edge!" << endl;
        }
    }

    /**
     * @brief Performs BFS traversal starting from a given vertex.
     * @param startVertex The vertex to start BFS from.
     */
    void bfs(int startVertex) {
        if (startVertex < 0 || startVertex >= numVertices) {
            cerr << "Error: Invalid start vertex!" << endl;
            return;
        }

        // Array to track visited vertices
        vector<bool> visited(numVertices, false);
        
        // Queue for BFS
        queue<int> q;

        // Mark the start vertex as visited and enqueue it
        visited[startVertex] = true;
        q.push(startVertex);

        cout << "\nBFS Traversal starting from vertex " << startVertex << ":\n";
        cout << "Order of traversal: ";

        // Process the queue until it's empty
        while (!q.empty()) {
            // Dequeue a vertex
            int vertex = q.front();
            q.pop();

            // Print the current vertex
            cout << vertex << " ";

            // Explore all adjacent vertices
            for (int neighbor : adjacencyList[vertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "\n";
    }

    /**
     * @brief Performs BFS and returns the shortest path between two vertices.
     * Returns -1 if no path exists.
     * @param start Source vertex
     * @param end Destination vertex
     * @return Distance (number of edges) from start to end
     */
    int bfsShortestPath(int start, int end) {
        if (start < 0 || start >= numVertices || end < 0 || end >= numVertices) {
            cerr << "Error: Invalid vertices!" << endl;
            return -1;
        }

        vector<bool> visited(numVertices, false);
        vector<int> distance(numVertices, -1);
        queue<int> q;

        visited[start] = true;
        distance[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();

            // If we reached the destination
            if (vertex == end) {
                return distance[end];
            }

            // Explore neighbors
            for (int neighbor : adjacencyList[vertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    distance[neighbor] = distance[vertex] + 1;
                    q.push(neighbor);
                }
            }
        }

        return -1; // No path found
    }

    /**
     * @brief Performs BFS and returns the level of each vertex (distance from source).
     * @param startVertex The starting vertex
     */
    void bfsLevels(int startVertex) {
        if (startVertex < 0 || startVertex >= numVertices) {
            cerr << "Error: Invalid start vertex!" << endl;
            return;
        }

        vector<bool> visited(numVertices, false);
        vector<int> level(numVertices, -1);
        queue<int> q;

        visited[startVertex] = true;
        level[startVertex] = 0;
        q.push(startVertex);

        cout << "\nBFS Levels (distance from vertex " << startVertex << "):\n";

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();

            for (int neighbor : adjacencyList[vertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    level[neighbor] = level[vertex] + 1;
                    q.push(neighbor);
                }
            }
        }

        // Print the level of each vertex
        for (int i = 0; i < numVertices; ++i) {
            if (level[i] == -1) {
                cout << "Vertex " << i << ": Not reachable" << endl;
            } else {
                cout << "Vertex " << setw(2) << i << ": Level " << level[i] << endl;
            }
        }
    }

    /**
     * @brief Display the adjacency list representation of the graph.
     */
    void displayGraph() {
        cout << "\n--- Graph (Adjacency List) ---\n";
        for (int i = 0; i < numVertices; ++i) {
            cout << "Vertex " << i << ": ";
            for (int neighbor : adjacencyList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

// Main function demonstrating BFS with various examples
int main() {
    cout << "=========================================" << endl;
    cout << "Breadth-First Search (BFS) Algorithm" << endl;
    cout << "=========================================" << endl;

    // Example 1: Basic BFS on an undirected graph
    cout << "\n--- Example 1: Basic BFS on Undirected Graph ---" << endl;
    Graph graph1(7);
    graph1.addEdge(0, 1);
    graph1.addEdge(0, 2);
    graph1.addEdge(1, 3);
    graph1.addEdge(1, 4);
    graph1.addEdge(2, 5);
    graph1.addEdge(2, 6);

    graph1.displayGraph();
    graph1.bfs(0);
    graph1.bfsLevels(0);

    // Example 2: BFS on a more complex undirected graph
    cout << "\n=========================================" << endl;
    cout << "--- Example 2: Complex Undirected Graph ---" << endl;
    Graph graph2(6);
    graph2.addEdge(0, 1);
    graph2.addEdge(0, 2);
    graph2.addEdge(1, 2);
    graph2.addEdge(1, 3);
    graph2.addEdge(2, 4);
    graph2.addEdge(3, 4);
    graph2.addEdge(3, 5);
    graph2.addEdge(4, 5);

    graph2.displayGraph();
    graph2.bfs(0);
    graph2.bfsLevels(0);

    // Example 3: BFS for shortest path
    cout << "\n=========================================" << endl;
    cout << "--- Example 3: Finding Shortest Path ---" << endl;
    Graph graph3(8);
    graph3.addEdge(0, 1);
    graph3.addEdge(0, 3);
    graph3.addEdge(1, 2);
    graph3.addEdge(2, 6);
    graph3.addEdge(3, 4);
    graph3.addEdge(4, 5);
    graph3.addEdge(5, 6);

    graph3.displayGraph();
    graph3.bfs(0);

    cout << "\nShortest Paths from vertex 0:" << endl;
    for (int i = 1; i < 8; ++i) {
        int distance = graph3.bfsShortestPath(0, i);
        if (distance == -1) {
            cout << "Vertex 0 to Vertex " << i << ": Not connected" << endl;
        } else {
            cout << "Vertex 0 to Vertex " << i << ": " << distance << " edges" << endl;
        }
    }

    // Example 4: BFS on a directed graph
    cout << "\n=========================================" << endl;
    cout << "--- Example 4: Directed Graph ---" << endl;
    Graph directedGraph(5);
    directedGraph.addDirectedEdge(0, 1);
    directedGraph.addDirectedEdge(0, 2);
    directedGraph.addDirectedEdge(1, 3);
    directedGraph.addDirectedEdge(2, 4);
    directedGraph.addDirectedEdge(3, 4);

    directedGraph.displayGraph();
    directedGraph.bfs(0);
    directedGraph.bfsLevels(0);

    // Example 5: BFS from different starting vertices
    cout << "\n=========================================" << endl;
    cout << "--- Example 5: BFS from Different Start Vertices ---" << endl;
    Graph graph5(5);
    graph5.addEdge(0, 1);
    graph5.addEdge(1, 2);
    graph5.addEdge(2, 3);
    graph5.addEdge(3, 4);

    for (int start = 0; start < 5; ++start) {
        graph5.bfs(start);
    }

    cout << "\n=========================================" << endl;
    cout << "--- Program Finished ---" << endl;
    cout << "=========================================" << endl;

    return 0;
}
