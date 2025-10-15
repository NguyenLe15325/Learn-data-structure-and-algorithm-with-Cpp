/*
===============================================================================
SHORTEST PATH ALGORITHMS - DIJKSTRA & BELLMAN-FORD
===============================================================================

PROBLEM STATEMENT:
------------------
Given a weighted, directed graph, find the shortest path from a source vertex
to all other vertices (or to a specific destination).

DIJKSTRA'S ALGORITHM:
====================

TIME COMPLEXITY: O((V + E) log V) with min-heap
SPACE COMPLEXITY: O(V)

CONSTRAINTS:
- Works with NON-NEGATIVE edge weights only
- Cannot handle negative weight edges

REAL-WORLD USES:
1. GPS & NAVIGATION
   - Google Maps, Apple Maps find shortest route to destination
   - Calculate travel time between locations
   - Example: Finding fastest route considering road distances

2. NETWORK ROUTING (OSPF Protocol)
   - Internet routing protocols use Dijkstra
   - Routers find optimal path to forward packets
   - Minimize hop count and latency

3. SOCIAL NETWORKS
   - Find shortest path between two people (degrees of separation)
   - Recommendation systems

4. GAME PATHFINDING
   - NPC movement in video games
   - Finding optimal path on game map

5. FLIGHT ROUTES
   - Airlines find shortest/cheapest route between cities
   - Minimize fuel costs and flight time

EXAMPLE USE CASE - GPS NAVIGATION:
---------------------------------
City network with roads:
  New York -> Boston: 4 hours
  New York -> Philadelphia: 2 hours
  Philadelphia -> Boston: 3 hours
  Philadelphia -> Washington DC: 2.5 hours
  Boston -> Washington DC: 7 hours

Find shortest path from New York to all cities:
  New York -> Boston: 7 hours (via Philadelphia)
  New York -> Philadelphia: 2 hours (direct)
  New York -> Washington DC: 4.5 hours (via Philadelphia)

ALGORITHM STEPS:
1. Initialize: distance[source] = 0, all others = INF
2. Add source to priority queue with distance 0
3. While queue not empty:
   a. Extract vertex with minimum distance
   b. For each neighbor:
      - Calculate new distance through current vertex
      - If new distance < stored distance: update and add to queue
4. Result: shortest distances and paths to all vertices

GREEDY APPROACH:
Always process the unvisited vertex with minimum distance first.
Once a vertex is visited (shortest path found), it's never reconsidered.

===============================================================================
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <iomanip>
using namespace std;

// Comparator for priority queue (min-heap by distance)
struct CompareDistance {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        return a.second > b.second;  // {vertex, distance}
    }
};

/*
===============================================================================
DIJKSTRA'S ALGORITHM
===============================================================================

GREEDY SHORTEST PATH FOR NON-NEGATIVE WEIGHTS

Real Use Case: GPS Navigation System
------------------------------------
We have cities connected by roads with distances. We need to find the
shortest driving distance from our current location to any destination.

The algorithm greedily selects the closest unvisited city and marks it
as the next waypoint. This ensures optimal path finding.
*/
class DijkstraShortestPath {
private:
    int vertices;
    vector<vector<pair<int, int>>> adjList;  // {neighbor, distance}
    
public:
    DijkstraShortestPath(int v) : vertices(v) {
        adjList.resize(vertices);
    }
    
    /*
    ADD DIRECTED EDGE TO GRAPH
    
    For GPS: This represents a road segment with distance
    Example: road from New York to Philadelphia with 100 miles
    */
    void addEdge(int u, int v, int distance) {
        adjList[u].push_back({v, distance});
    }
    
    /*
    DIJKSTRA'S ALGORITHM IMPLEMENTATION
    ====================================
    
    GREEDY STRATEGY:
    ---------------
    1. Start from source vertex
    2. Always process the unvisited vertex with MINIMUM distance
    3. Update distances to all neighbors
    4. Mark vertex as visited (shortest path found - won't revisit)
    5. Repeat until all reachable vertices processed
    
    WHY THIS WORKS:
    Once we find the shortest path to a vertex, we never need to revisit it.
    Any other path would be longer because all weights are non-negative.
    */
    void dijkstra(int source) {
        cout << "\n";
        cout << "========================================\n";
        cout << "DIJKSTRA'S ALGORITHM - SHORTEST PATH\n";
        cout << "========================================\n\n";
        
        cout << "Real Use Case: GPS Navigation System\n";
        cout << "Task: Find shortest route from source city to all others\n\n";
        
        // Initialize distances
        vector<int> distance(vertices, INT_MAX);
        vector<bool> visited(vertices, false);
        vector<int> parent(vertices, -1);
        
        distance[source] = 0;
        
        // Min-heap: {vertex, distance}
        priority_queue<pair<int, int>, 
                      vector<pair<int, int>>, 
                      CompareDistance> pq;
        
        pq.push({source, 0});
        
        int step = 0;
        
        while (!pq.empty()) {
            auto [u, dist] = pq.top();
            pq.pop();
            
            // Skip if already visited
            if (visited[u]) {
                continue;
            }
            
            visited[u] = true;
            step++;
            
            cout << "Step " << step << ": Processing city " << u 
                 << " (shortest distance: " << dist << ")\n";
            
            // Check all neighbors
            for (auto& [neighbor, edgeWeight] : adjList[u]) {
                if (!visited[neighbor]) {
                    int newDistance = distance[u] + edgeWeight;
                    
                    // Found shorter path
                    if (newDistance < distance[neighbor]) {
                        distance[neighbor] = newDistance;
                        parent[neighbor] = u;
                        pq.push({neighbor, newDistance});
                        
                        cout << "  Update: City " << neighbor 
                             << " distance = " << newDistance 
                             << " (via city " << u << ")\n";
                    }
                }
            }
        }
        
        cout << "\n";
        printDijkstraResult(distance, parent, source);
    }
    
    void printDijkstraResult(const vector<int>& distance, 
                            const vector<int>& parent, int source) {
        cout << "========================================\n";
        cout << "DIJKSTRA'S RESULT - SHORTEST PATHS\n";
        cout << "========================================\n\n";
        
        cout << "From City " << source << " to all destinations:\n\n";
        cout << setw(12) << "City" 
             << setw(15) << "Distance" 
             << setw(30) << "Route Path" << "\n";
        cout << string(57, '-') << "\n";
        
        for (int i = 0; i < vertices; i++) {
            cout << setw(12) << i;
            
            if (distance[i] == INT_MAX) {
                cout << setw(15) << "UNREACHABLE" << setw(30) << "---\n";
            } else {
                cout << setw(15) << distance[i];
                
                // Reconstruct path
                vector<int> path;
                int curr = i;
                while (curr != -1) {
                    path.push_back(curr);
                    curr = parent[curr];
                }
                
                reverse(path.begin(), path.end());
                cout << setw(30);
                for (size_t j = 0; j < path.size(); j++) {
                    if (j > 0) cout << " -> ";
                    cout << path[j];
                }
                cout << "\n";
            }
        }
        
        cout << "\n>>> Dijkstra's algorithm complete <<<\n";
    }
};

/*
===============================================================================
BELLMAN-FORD ALGORITHM
===============================================================================

SHORTEST PATH WITH NEGATIVE WEIGHTS (But no negative cycles)

TIME COMPLEXITY: O(V * E)
SPACE COMPLEXITY: O(V)

CONSTRAINTS:
- Works with NEGATIVE edge weights
- Cannot handle negative weight cycles
- Slower than Dijkstra but more flexible

REAL-WORLD USES:
1. CURRENCY EXCHANGE NETWORKS
   - Convert currencies with exchange rates
   - Some exchanges might give "negative profits" (lose money)
   - Detect arbitrage opportunities (negative cycles)

2. FINANCIAL MARKETS
   - Find lowest cost portfolio adjustments
   - Some adjustments have penalties (negative weights)

3. GAME DEVELOPMENT
   - Some paths have "boosts" (negative costs)
   - NPCs prefer low-cost routes considering penalties

4. NETWORK PROTOCOLS (BGP Routing)
   - Internet Border Gateway Protocol
   - Can handle negative weight scenarios

5. ROBOTICS PATH PLANNING
   - Some areas have "rewards" (negative cost)
   - Find path that maximizes total reward

EXAMPLE USE CASE - CURRENCY EXCHANGE:
------------------------------------
Exchange rates between currencies:
  USD -> EUR: rate 0.92 (lose money in conversion)
  EUR -> GBP: rate 1.15 (gain in conversion)
  GBP -> USD: rate 1.36 (gain)
  USD -> GBP: rate 1.25 (direct but worse)

Find best exchange path from USD to GBP:
Direct: USD -> GBP: 1.25
Indirect: USD -> EUR -> GBP: 0.92 * 1.15 = 1.058 (better!)

ALGORITHM STEPS:
1. Initialize: distance[source] = 0, all others = INF
2. Repeat V-1 times (max edges in path):
   a. For each edge (u, v, weight):
      - If distance[u] + weight < distance[v]:
        - Update distance[v] = distance[u] + weight
3. Check for negative cycles: iterate once more
   - If any distance improves, negative cycle exists

DIFFERENCE FROM DIJKSTRA:
- Dijkstra: Greedy, one pass, O(E log V)
- Bellman-Ford: Relaxes all edges V-1 times, O(V*E)
- Bellman-Ford can detect negative cycles
- Dijkstra fails with negative weights
*/
class BellmanFordShortestPath {
private:
    int vertices;
    vector<tuple<int, int, int>> edges;  // {src, dest, weight}
    bool isDirected;
    
public:
    BellmanFordShortestPath(int v, bool directed = true) 
        : vertices(v), isDirected(directed) {}
    
    /*
    ADD EDGE TO GRAPH
    
    DIRECTED EDGE (isDirected = true):
    For currency exchange: represents one-way exchange rate
    Example: USD (0) to EUR (1) with rate 0.92
    
    UNDIRECTED EDGE (isDirected = false):
    For road network: represents bidirectional road
    Example: City 0 to City 1 with distance 100 (can go both ways)
    Automatically adds reverse edge (1 to 0) with same weight
    */
    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
        
        // For undirected graphs, add reverse edge
        if (!isDirected) {
            edges.push_back({v, u, weight});
        }
    }
    
    /*
    BELLMAN-FORD ALGORITHM IMPLEMENTATION
    ======================================
    
    RELAXATION APPROACH:
    -------------------
    Instead of greedily picking minimum, we relax ALL edges repeatedly.
    "Relaxation" means: if we found a shorter path, update distance.
    
    We do this V-1 times because:
    - Shortest path has at most V-1 edges
    - After V-1 iterations, all shortest paths found
    
    WHY THIS WORKS WITH NEGATIVE WEIGHTS:
    We relax all edges multiple times. Even if an edge is negative,
    we eventually find the shortest path (after multiple passes).
    
    NEGATIVE CYCLE DETECTION:
    If distances still improve on the Vth iteration, there's a
    negative cycle (path we can traverse infinitely to reduce cost).
    */
    bool bellmanFord(int source) {
        cout << "\n";
        cout << "========================================\n";
        cout << "BELLMAN-FORD ALGORITHM - SHORTEST PATH\n";
        cout << "========================================\n\n";
        
        cout << "Real Use Case: Currency Exchange Network\n";
        cout << "Task: Find best exchange rates (handles negative rates)\n\n";
        
        // Initialize distances
        vector<int> distance(vertices, INT_MAX);
        vector<int> parent(vertices, -1);
        
        distance[source] = 0;
        
        cout << "Phase 1: Relaxing edges (V-1 = " << (vertices-1) << " iterations)\n";
        cout << "=========================================\n\n";
        
        /*
        PHASE 1: RELAXATION
        Iterate V-1 times, relaxing all edges
        */
        for (int i = 0; i < vertices - 1; i++) {
            cout << "Iteration " << (i + 1) << ":\n";
            
            bool updated = false;
            for (auto& [u, v, weight] : edges) {
                // Only relax if source is reachable
                if (distance[u] != INT_MAX) {
                    int newDist = distance[u] + weight;
                    
                    if (newDist < distance[v]) {
                        distance[v] = newDist;
                        parent[v] = u;
                        updated = true;
                        
                        cout << "  Update: Currency " << v 
                             << " distance = " << newDist 
                             << " (via currency " << u << ")\n";
                    }
                }
            }
            
            if (!updated) {
                cout << "  No updates in this iteration\n";
            }
            cout << "\n";
        }
        
        /*
        PHASE 2: NEGATIVE CYCLE DETECTION
        Check if any more improvements possible (indicates negative cycle)
        */
        cout << "Phase 2: Checking for negative cycles\n";
        cout << "=====================================\n\n";
        
        for (auto& [u, v, weight] : edges) {
            if (distance[u] != INT_MAX) {
                int newDist = distance[u] + weight;
                
                if (newDist < distance[v]) {
                    cout << "NEGATIVE CYCLE DETECTED!\n";
                    cout << "Edge: " << u << " -> " << v 
                         << " (weight: " << weight << ")\n";
                    cout << "Can still improve distance to " << v << "\n";
                    cout << "This means there's a path that gives infinite profit!\n\n";
                    
                    return false;  // Negative cycle exists
                }
            }
        }
        
        cout << "No negative cycles detected. Graph is safe.\n\n";
        
        printBellmanFordResult(distance, parent, source);
        return true;  // No negative cycle
    }
    
    void printBellmanFordResult(const vector<int>& distance, 
                               const vector<int>& parent, int source) {
        cout << "========================================\n";
        cout << "BELLMAN-FORD RESULT - SHORTEST PATHS\n";
        cout << "========================================\n\n";
        
        cout << "From Currency " << source << " to all others:\n\n";
        cout << setw(12) << "Currency" 
             << setw(15) << "Distance" 
             << setw(30) << "Exchange Path" << "\n";
        cout << string(57, '-') << "\n";
        
        for (int i = 0; i < vertices; i++) {
            cout << setw(12) << i;
            
            if (distance[i] == INT_MAX) {
                cout << setw(15) << "UNREACHABLE" << setw(30) << "---\n";
            } else {
                cout << setw(15) << distance[i];
                
                // Reconstruct path
                vector<int> path;
                int curr = i;
                while (curr != -1) {
                    path.push_back(curr);
                    curr = parent[curr];
                }
                
                reverse(path.begin(), path.end());
                cout << setw(30);
                for (size_t j = 0; j < path.size(); j++) {
                    if (j > 0) cout << " -> ";
                    cout << path[j];
                }
                cout << "\n";
            }
        }
        
        cout << "\n>>> Bellman-Ford algorithm complete <<<\n";
    }
};

int main() {
    cout << "\n";
    cout << "##################################################\n";
    cout << "# SHORTEST PATH ALGORITHMS                      #\n";
    cout << "# Dijkstra & Bellman-Ford with Real Use Cases  #\n";
    cout << "##################################################\n";
    
    /*
    TEST CASE 1: DIJKSTRA'S ALGORITHM
    =================================
    Use Case: GPS Navigation
    
    City Network:
      0 (New York)
      1 (Philadelphia)
      2 (Boston)
      3 (Washington DC)
      4 (Atlanta)
    
    Routes with distances:
    */
    cout << "\n\n#####################################\n";
    cout << "# TEST 1: DIJKSTRA'S ALGORITHM    #\n";
    cout << "# Use Case: GPS Navigation        #\n";
    cout << "#####################################\n";
    
    DijkstraShortestPath dijkstra(5);
    
    // City connections (distances in miles)
    dijkstra.addEdge(0, 1, 100);  // New York -> Philadelphia
    dijkstra.addEdge(0, 2, 215);  // New York -> Boston
    dijkstra.addEdge(1, 2, 305);  // Philadelphia -> Boston
    dijkstra.addEdge(1, 3, 140);  // Philadelphia -> Washington DC
    dijkstra.addEdge(2, 3, 440);  // Boston -> Washington DC
    dijkstra.addEdge(3, 4, 640);  // Washington DC -> Atlanta
    dijkstra.addEdge(0, 4, 860);  // New York -> Atlanta
    
    dijkstra.dijkstra(0);
    
    /*
    TEST CASE 2: BELLMAN-FORD ALGORITHM (DIRECTED GRAPH)
    ===================================================
    Use Case: Currency Exchange Network (Directed)
    
    Currency Network:
      0 (USD)
      1 (EUR)
      2 (GBP)
      3 (JPY)
    
    Exchange rates are DIRECTED (one-way rates):
    */
    cout << "\n\n#####################################\n";
    cout << "# TEST 2A: BELLMAN-FORD (DIRECTED) #\n";
    cout << "# Use Case: Currency Exchange      #\n";
    cout << "#####################################\n";
    
    BellmanFordShortestPath bellmanford(4, true);  // true = directed
    
    // Directed edges: exchange rates (one-way)
    bellmanford.addEdge(0, 1, -8);  // USD -> EUR (lose 8)
    bellmanford.addEdge(1, 2, 11);  // EUR -> GBP (gain 11)
    bellmanford.addEdge(0, 2, -5);  // USD -> GBP (lose 5)
    bellmanford.addEdge(2, 3, 20);  // GBP -> JPY (gain 20)
    bellmanford.addEdge(0, 3, 5);   // USD -> JPY (gain 5)
    bellmanford.addEdge(1, 0, 10);  // EUR -> USD (gain 10)
    
    bellmanford.bellmanFord(0);
    
    /*
    TEST CASE 2B: BELLMAN-FORD ALGORITHM (UNDIRECTED GRAPH)
    =======================================================
    Use Case: Road Network (Undirected)
    
    Cities:
      0 (New York)
      1 (Philadelphia)
      2 (Boston)
      3 (Washington DC)
    
    Roads are BIDIRECTIONAL (can travel both ways with same distance):
    */
    cout << "\n\n####################################\n";
    cout << "# TEST 2B: BELLMAN-FORD (UNDIRECTED)#\n";
    cout << "# Use Case: Road Network           #\n";
    cout << "####################################\n";
    
    BellmanFordShortestPath bellmanford2(4, false);  // false = undirected
    
    // Undirected edges: distances (bidirectional)
    // Automatically adds reverse edge too!
    bellmanford2.addEdge(0, 1, 100);  // New York <-> Philadelphia
    bellmanford2.addEdge(0, 2, 215);  // New York <-> Boston
    bellmanford2.addEdge(1, 2, 305);  // Philadelphia <-> Boston
    bellmanford2.addEdge(1, 3, 140);  // Philadelphia <-> Washington DC
    bellmanford2.addEdge(2, 3, 440);  // Boston <-> Washington DC
    
    bellmanford2.bellmanFord(0);
    
    /*
    TEST CASE 3: DIJKSTRA WITH LARGER GRAPH
    ========================================
    */
    cout << "\n\n#################################\n";
    cout << "# TEST 3: DIJKSTRA - TEST 2    #\n";
    cout << "# Use Case: Larger Network     #\n";
    cout << "#################################\n";
    
    DijkstraShortestPath dijkstra2(6);
    
    dijkstra2.addEdge(0, 1, 7);
    dijkstra2.addEdge(0, 2, 9);
    dijkstra2.addEdge(0, 5, 14);
    dijkstra2.addEdge(1, 2, 10);
    dijkstra2.addEdge(1, 3, 15);
    dijkstra2.addEdge(2, 3, 11);
    dijkstra2.addEdge(2, 5, 2);
    dijkstra2.addEdge(3, 4, 6);
    dijkstra2.addEdge(4, 5, 9);
    
    dijkstra2.dijkstra(0);
    
    cout << "\n\n##################################################\n";
    cout << "# ALGORITHM COMPARISON                           #\n";
    cout << "##################################################\n\n";
    
    cout << "DIJKSTRA'S ALGORITHM:\n";
    cout << "  Time: O((V + E) log V)\n";
    cout << "  Space: O(V)\n";
    cout << "  Weights: NON-NEGATIVE only\n";
    cout << "  Graph: DIRECTED or UNDIRECTED (both work)\n";
    cout << "  Use: GPS, routing, social networks, games\n\n";
    
    cout << "BELLMAN-FORD ALGORITHM:\n";
    cout << "  Time: O(V * E)\n";
    cout << "  Space: O(V)\n";
    cout << "  Weights: Can handle NEGATIVE weights\n";
    cout << "  Graph: DIRECTED or UNDIRECTED (both work)\n";
    cout << "  Use: Currency exchange, financial markets, arbitrage\n";
    cout << "  Special: Can detect negative cycles\n\n";
    
    cout << "HOW TO USE WITH UNDIRECTED GRAPHS:\n";
    cout << "  - For undirected: add edge in BOTH directions\n";
    cout << "  - Example: addEdge(0, 1, 10) + addEdge(1, 0, 10)\n";
    cout << "  - OR use isDirected parameter (false) for automatic reverse\n\n";
    
    cout << "KEY DIFFERENCES:\n";
    cout << "  - Dijkstra: Faster, but needs non-negative weights\n";
    cout << "  - Bellman-Ford: Slower, but handles negative weights\n";
    cout << "  - Bellman-Ford: Detects negative cycles (arbitrage/profit loops)\n";
    cout << "  - Dijkstra: Greedy approach, processes best vertex first\n";
    cout << "  - Bellman-Ford: Relaxation approach, iterates all edges multiple times\n\n";
    
    return 0;
}