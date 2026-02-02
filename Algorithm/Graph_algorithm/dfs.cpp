/**
 * Title: Depth-First Search (DFS) Algorithm
 * File: dfs.cpp
 *
 * THE PROBLEM:
 * Depth-First Search (DFS) is a fundamental graph traversal algorithm used to explore 
 * all vertices (nodes) in a graph in depth-first order. Starting from a source vertex, 
 * DFS explores as far as possible along each branch before backtracking. This is commonly 
 * used for:
 * - Detecting cycles in graphs
 * - Topological sorting
 * - Finding strongly connected components
 * - Maze solving and path finding
 * - Tree traversal (pre-order, in-order, post-order)
 * - Backtracking problems
 *
 * THE ALGORITHM:
 * There are two common approaches:
 * 
 * RECURSIVE APPROACH:
 * 1. Mark the current vertex as visited
 * 2. Process the current vertex (print it, record it, etc.)
 * 3. For each unvisited neighbor:
 *    - Recursively call DFS on that neighbor
 * 4. Return when all neighbors have been explored
 *
 * ITERATIVE APPROACH (using stack):
 * 1. Create a stack and push the source vertex
 * 2. Mark the source as visited
 * 3. While the stack is not empty:
 *    a. Pop a vertex from the stack
 *    b. Process the vertex
 *    c. For each unvisited neighbor:
 *       - Mark as visited and push onto stack
 * 4. Repeat until the stack is empty
 *
 * TIME COMPLEXITY: O(V + E) where V is the number of vertices and E is the number of edges
 * SPACE COMPLEXITY: O(V) for the visited array and recursion/stack space
 */

#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>

using namespace std;

// 1. Graph Class using Adjacency List representation
class Graph {
private:
    int numVertices;
    vector<vector<int>> adjacencyList;

    /**
     * @brief Helper function for recursive DFS.
     * @param vertex Current vertex being explored
     * @param visited Array tracking visited vertices
     */
    void dfsRecursiveHelper(int vertex, vector<bool>& visited) {
        // Mark the current vertex as visited
        visited[vertex] = true;
        
        // Process the current vertex (print it)
        cout << vertex << " ";

        // Explore all adjacent vertices
        for (int neighbor : adjacencyList[vertex]) {
            if (!visited[neighbor]) {
                // Recursively call DFS on unvisited neighbors
                dfsRecursiveHelper(neighbor, visited);
            }
        }
    }

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
     * @brief Performs recursive DFS traversal starting from a given vertex.
     * This approach uses the call stack implicitly through recursion.
     * @param startVertex The vertex to start DFS from.
     */
    void dfsRecursive(int startVertex) {
        if (startVertex < 0 || startVertex >= numVertices) {
            cerr << "Error: Invalid start vertex!" << endl;
            return;
        }

        vector<bool> visited(numVertices, false);
        cout << "\nDFS Traversal (Recursive) starting from vertex " << startVertex << ":\n";
        cout << "Order of traversal: ";
        
        dfsRecursiveHelper(startVertex, visited);
        
        cout << "\n";
    }

    /**
     * @brief Performs iterative DFS traversal starting from a given vertex using an explicit stack.
     * This approach mimics the recursive approach but uses an explicit data structure.
     * @param startVertex The vertex to start DFS from.
     */
    void dfsIterative(int startVertex) {
        if (startVertex < 0 || startVertex >= numVertices) {
            cerr << "Error: Invalid start vertex!" << endl;
            return;
        }

        vector<bool> visited(numVertices, false);
        stack<int> s;

        // Push the start vertex onto the stack
        s.push(startVertex);
        visited[startVertex] = true;

        cout << "\nDFS Traversal (Iterative) starting from vertex " << startVertex << ":\n";
        cout << "Order of traversal: ";

        // Process the stack until it's empty
        while (!s.empty()) {
            // Pop a vertex from the stack
            int vertex = s.top();
            s.pop();

            // Process the vertex
            cout << vertex << " ";

            // Explore all adjacent vertices (in reverse to maintain order)
            // We iterate in reverse so that vertices are pushed in the same order as recursive DFS
            for (int i = adjacencyList[vertex].size() - 1; i >= 0; --i) {
                int neighbor = adjacencyList[vertex][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
        cout << "\n";
    }

    /**
     * @brief Detects if the graph contains a cycle using DFS.
     * For undirected graphs, we check if we reach a visited vertex other than the parent.
     * @return true if a cycle is detected, false otherwise.
     */
    bool hasCycle() {
        vector<bool> visited(numVertices, false);

        // Check for cycles starting from each unvisited vertex
        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i]) {
                if (hasCycleDFS(i, -1, visited)) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * @brief Helper function for cycle detection using DFS.
     * @param vertex Current vertex
     * @param parent Parent vertex (to avoid checking the edge we came from)
     * @param visited Array tracking visited vertices
     * @return true if a cycle is found
     */
    bool hasCycleDFS(int vertex, int parent, vector<bool>& visited) {
        visited[vertex] = true;

        for (int neighbor : adjacencyList[vertex]) {
            if (!visited[neighbor]) {
                if (hasCycleDFS(neighbor, vertex, visited)) {
                    return true;
                }
            } else if (neighbor != parent) {
                // We found a visited vertex that is not the parent -> cycle detected
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Checks if the graph is connected (all vertices are reachable from vertex 0).
     * @return true if the graph is connected, false otherwise.
     */
    bool isConnected() {
        vector<bool> visited(numVertices, false);
        
        // Perform DFS from vertex 0
        dfsRecursiveHelper(0, visited);

        // Check if all vertices were visited
        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Finds the path from source to destination using DFS.
     * @param source Starting vertex
     * @param destination Target vertex
     * @return Vector representing the path from source to destination, empty if no path exists
     */
    vector<int> findPath(int source, int destination) {
        if (source < 0 || source >= numVertices || destination < 0 || destination >= numVertices) {
            cerr << "Error: Invalid vertices!" << endl;
            return {};
        }

        vector<bool> visited(numVertices, false);
        vector<int> path;
        findPathDFS(source, destination, visited, path);
        return path;
    }

    /**
     * @brief Helper function to find path using DFS.
     * @param vertex Current vertex
     * @param destination Target vertex
     * @param visited Array tracking visited vertices
     * @param path Vector accumulating the path
     * @return true if path to destination is found
     */
    bool findPathDFS(int vertex, int destination, vector<bool>& visited, vector<int>& path) {
        visited[vertex] = true;
        path.push_back(vertex);

        if (vertex == destination) {
            return true;
        }

        for (int neighbor : adjacencyList[vertex]) {
            if (!visited[neighbor]) {
                if (findPathDFS(neighbor, destination, visited, path)) {
                    return true;
                }
            }
        }

        // Backtrack: remove the current vertex from path
        path.pop_back();
        return false;
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

// Main function demonstrating DFS with various examples
int main() {
    cout << "=========================================" << endl;
    cout << "Depth-First Search (DFS) Algorithm" << endl;
    cout << "=========================================" << endl;

    // Example 1: Basic DFS (Recursive vs Iterative)
    cout << "\n--- Example 1: Recursive vs Iterative DFS ---" << endl;
    Graph graph1(7);
    graph1.addEdge(0, 1);
    graph1.addEdge(0, 2);
    graph1.addEdge(1, 3);
    graph1.addEdge(1, 4);
    graph1.addEdge(2, 5);
    graph1.addEdge(2, 6);

    graph1.displayGraph();
    graph1.dfsRecursive(0);
    graph1.dfsIterative(0);

    // Example 2: DFS on a more complex undirected graph
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
    graph2.dfsRecursive(0);
    graph2.dfsIterative(0);

    // Example 3: Cycle Detection
    cout << "\n=========================================" << endl;
    cout << "--- Example 3: Cycle Detection ---" << endl;
    
    cout << "\nGraph without cycle:" << endl;
    Graph graphNoCycle(4);
    graphNoCycle.addEdge(0, 1);
    graphNoCycle.addEdge(1, 2);
    graphNoCycle.addEdge(2, 3);
    graphNoCycle.displayGraph();
    cout << "Has cycle: " << (graphNoCycle.hasCycle() ? "Yes" : "No") << endl;

    cout << "\nGraph with cycle:" << endl;
    Graph graphWithCycle(4);
    graphWithCycle.addEdge(0, 1);
    graphWithCycle.addEdge(1, 2);
    graphWithCycle.addEdge(2, 3);
    graphWithCycle.addEdge(3, 0); // Creates a cycle
    graphWithCycle.displayGraph();
    cout << "Has cycle: " << (graphWithCycle.hasCycle() ? "Yes" : "No") << endl;

    // Example 4: Connectivity Check
    cout << "\n=========================================" << endl;
    cout << "--- Example 4: Connectivity Check ---" << endl;
    
    cout << "\nConnected graph:" << endl;
    Graph connectedGraph(5);
    connectedGraph.addEdge(0, 1);
    connectedGraph.addEdge(1, 2);
    connectedGraph.addEdge(2, 3);
    connectedGraph.addEdge(3, 4);
    connectedGraph.displayGraph();
    cout << "Is connected: " << (connectedGraph.isConnected() ? "Yes" : "No") << endl;

    cout << "\nDisconnected graph:" << endl;
    Graph disconnectedGraph(5);
    disconnectedGraph.addEdge(0, 1);
    disconnectedGraph.addEdge(1, 2);
    disconnectedGraph.addEdge(3, 4); // Separate component
    disconnectedGraph.displayGraph();
    cout << "Is connected: " << (disconnectedGraph.isConnected() ? "Yes" : "No") << endl;

    // Example 5: Path Finding
    cout << "\n=========================================" << endl;
    cout << "--- Example 5: Path Finding using DFS ---" << endl;
    Graph pathGraph(8);
    pathGraph.addEdge(0, 1);
    pathGraph.addEdge(0, 2);
    pathGraph.addEdge(1, 3);
    pathGraph.addEdge(2, 4);
    pathGraph.addEdge(3, 5);
    pathGraph.addEdge(4, 5);
    pathGraph.addEdge(5, 6);
    pathGraph.addEdge(6, 7);

    pathGraph.displayGraph();
    pathGraph.dfsRecursive(0);

    cout << "\nPaths from vertex 0:" << endl;
    for (int destination = 1; destination < 8; ++destination) {
        vector<int> path = pathGraph.findPath(0, destination);
        if (path.empty()) {
            cout << "No path from 0 to " << destination << endl;
        } else {
            cout << "Path from 0 to " << destination << ": ";
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i < path.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }

    // Example 6: DFS on Directed Graph
    cout << "\n=========================================" << endl;
    cout << "--- Example 6: DFS on Directed Graph ---" << endl;
    Graph directedGraph(5);
    directedGraph.addDirectedEdge(0, 1);
    directedGraph.addDirectedEdge(0, 2);
    directedGraph.addDirectedEdge(1, 3);
    directedGraph.addDirectedEdge(2, 4);
    directedGraph.addDirectedEdge(3, 4);

    directedGraph.displayGraph();
    directedGraph.dfsRecursive(0);
    directedGraph.dfsIterative(0);

    // Example 7: DFS from Different Starting Vertices
    cout << "\n=========================================" << endl;
    cout << "--- Example 7: DFS from Different Start Vertices ---" << endl;
    Graph graph7(5);
    graph7.addEdge(0, 1);
    graph7.addEdge(1, 2);
    graph7.addEdge(2, 3);
    graph7.addEdge(3, 4);

    for (int start = 0; start < 5; ++start) {
        graph7.dfsRecursive(start);
    }

    cout << "\n=========================================" << endl;
    cout << "--- Program Finished ---" << endl;
    cout << "=========================================" << endl;

    return 0;
}
