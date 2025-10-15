/*
===============================================================================
CONNECT N ROPES WITH MINIMUM COST - PROBLEM & STRATEGY EXPLAINED
===============================================================================

PROBLEM STATEMENT:
------------------
You have N ropes with different lengths. You need to connect all of them into
a single rope. The cost of connecting two ropes is equal to the sum of their
lengths. Find the minimum total cost to connect all ropes.

EXAMPLE:
--------
Ropes: [4, 3, 2, 6]

SUBOPTIMAL APPROACH (connect in order):
----------------------------------------
  Step 1: 4+3=7      cost = 7      (total so far: 7)
  Step 2: 7+2=9      cost = 9      (total so far: 16)
  Step 3: 9+6=15     cost = 15     (total so far: 31)
  
  Problem: We created 7 early, and had to use it in 2 more operations!
  Each use of 7 in future connections adds to total cost.

OPTIMAL GREEDY APPROACH (connect smallest first):
--------------------------------------------------
  Initial state: Ropes available = [4, 3, 2, 6]
  
  Step 1: Connect 2+3=5     (cost = 5)
    - We pick the TWO SMALLEST ropes: 2 and 3
    - We combine them into a single rope of length 5
    - This costs 5 and we ADD it to total cost
    - Now available ropes = [4, 5, 6]  (2 and 3 are gone, replaced by 5)
    - Total cost so far: 5
  
  Step 2: Connect 5+4=9     (cost = 9)
    - We pick the TWO SMALLEST remaining ropes: 4 and 5
    - We combine them into a single rope of length 9
    - This costs 9 and we ADD it to total cost
    - Now available ropes = [6, 9]  (4 and 5 are gone, replaced by 9)
    - Total cost so far: 5 + 9 = 14
  
  Step 3: Connect 9+6=15    (cost = 15)
    - We pick the TWO SMALLEST remaining ropes: 6 and 9
    - We combine them into a single rope of length 15
    - This costs 15 and we ADD it to total cost
    - Now available ropes = [15]  (only one rope left, we're done!)
    - Total cost so far: 5 + 9 + 15 = 29
  
  FINAL RESULT: Total cost = 29 ✓ (BETTER than 31!)
  
KEY INSIGHT:
By connecting the two smallest ropes FIRST, we create smaller intermediate 
ropes (5 instead of 7). This intermediate rope is then used in future 
connections, but since it's smaller, it costs less.

WHY GREEDY WORKS:
-----------------
1. Each time we connect two ropes, they combine into a new rope that will be
   used in future connections.
   
2. If we connect small ropes first, we minimize the size of intermediate ropes.
   Smaller intermediate ropes = smaller costs in future connections.
   
3. If we connect large ropes early, we create a large intermediate rope that
   has to be used in ALL future operations, inflating total cost.
   
4. The problem exhibits OPTIMAL SUBSTRUCTURE: The optimal solution contains
   optimal solutions to subproblems. By always combining the two smallest
   ropes, we ensure each subproblem is solved optimally.

ALGORITHM (GREEDY WITH MIN-HEAP):
----------------------------------
1. Create a min-heap and insert all rope lengths
2. While heap has more than 1 rope:
   a. Extract the two smallest ropes (first and second)
   b. Connect them: cost = first + second
   c. Add this cost to total cost
   d. Insert the combined rope back into heap
3. Return total cost

TIME COMPLEXITY: O(n log n)
  - Building heap: O(n)
  - n-1 extraction/insertion operations: each is O(log n)
  - Total: O(n log n)

SPACE COMPLEXITY: O(n)
  - Heap stores all ropes

WHY NOT SORT AND ITERATE?
--------------------------
Sorting alone is O(n log n) but doesn't reflect the problem well.
When we combine two ropes, we need to maintain order of remaining ropes.
Min-heap automatically maintains this order efficiently.

===============================================================================
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class RopeConnector {
private:
    // Min-heap: priority_queue with greater<> comparator gives min-heap behavior
    priority_queue<long long, vector<long long>, greater<long long>> minHeap;
    
public:
    /*
    OPTIMAL SOLUTION USING MIN-HEAP (GREEDY APPROACH)
    
    Strategy:
    ---------
    1. Create a min-heap containing all rope lengths
    2. Repeatedly extract the two smallest ropes
    3. Connect them and add cost to total
    4. Insert the combined rope back into heap
    5. Continue until only one rope remains
    
    Why min-heap?
    - Automatically maintains ropes in sorted order
    - Efficient O(log n) extraction and insertion
    - No need to resort after each operation
    
    Example walkthrough with [4, 3, 2, 6]:
    ----------------------------------------
    Initial heap: [2, 3, 4, 6]
    
    Iteration 1: Extract 2 and 3
      Cost = 2 + 3 = 5
      Total cost = 5
      Insert 5 back → heap: [4, 5, 6]
    
    Iteration 2: Extract 4 and 5
      Cost = 4 + 5 = 9
      Total cost = 5 + 9 = 14
      Insert 9 back → heap: [6, 9]
    
    Iteration 3: Extract 6 and 9
      Cost = 6 + 9 = 15
      Total cost = 14 + 15 = 29
      Insert 15 back → heap: [15]
    
    Only one rope left, done! Total cost = 29
    */
    long long connectRopesOptimal(vector<int>& ropes) {
        // Edge case: 0 or 1 rope needs no connections
        if (ropes.empty()) return 0;
        if (ropes.size() == 1) return 0;
        
        // Clear heap and populate with all rope lengths
        while (!minHeap.empty()) minHeap.pop();
        for (int rope : ropes) {
            minHeap.push(rope);
        }
        
        long long totalCost = 0;
        vector<long long> steps;
        
        // Keep connecting until one rope remains
        while (minHeap.size() > 1) {
            // Extract two smallest ropes from heap
            long long first = minHeap.top();
            minHeap.pop();
            long long second = minHeap.top();
            minHeap.pop();
            
            // Calculate cost of connecting these two ropes
            long long cost = first + second;
            totalCost += cost;
            steps.push_back(cost);
            
            // Insert the combined rope back into heap for future connections
            minHeap.push(cost);
        }
        
        printSteps(steps);
        return totalCost;
    }
    
    /*
    BRUTE FORCE SOLUTION (FOR COMPARISON - INEFFICIENT)
    
    Strategy:
    ---------
    1. Sort the array each iteration
    2. Connect the two smallest ropes
    3. Remove the two smallest, add the combined rope
    4. Repeat until one rope remains
    
    Why this is inefficient:
    - O(n log n) sorting happens n times = O(n² log n) overall
    - Min-heap approach does this automatically in O(n log n) total
    
    This solution is included ONLY for educational comparison.
    In production, always use the min-heap approach.
    */
    long long connectRopesBruteForce(vector<int> ropes) {
        if (ropes.size() <= 1) return 0;
        
        long long totalCost = 0;
        vector<long long> steps;
        
        // Repeatedly process until one rope remains
        while (ropes.size() > 1) {
            // Sort array to find two smallest - INEFFICIENT!
            sort(ropes.begin(), ropes.end());
            
            // Extract two smallest ropes
            int first = ropes[0];
            int second = ropes[1];
            long long cost = first + second;
            
            totalCost += cost;
            steps.push_back(cost);
            
            // Remove two smallest (must erase twice due to indexing)
            ropes.erase(ropes.begin());
            ropes.erase(ropes.begin());
            
            // Add combined rope back
            ropes.push_back(cost);
        }
        
        printSteps(steps);
        return totalCost;
    }
    
    void printSteps(const vector<long long>& steps) {
        cout << "Connection steps:\n";
        for (size_t i = 0; i < steps.size(); i++) {
            cout << "  Step " << (i + 1) << ": Connect ropes, cost = " << steps[i] << "\n";
        }
    }
};

/*
ALTERNATIVE IMPLEMENTATION USING STL HEAP FUNCTIONS
=====================================================

Strategy:
---------
Instead of priority_queue, manually manage heap using:
- make_heap(): Convert array into heap
- pop_heap(): Extract top element
- push_heap(): Add element while maintaining heap property

This gives more control and shows how heaps work internally.
Performance is identical to priority_queue approach.
*/
class RopeConnectorAlt {
public:
    long long connectRopes(vector<int> ropes) {
        if (ropes.size() <= 1) return 0;
        
        // Convert array into a min-heap (greater<int> makes it min-heap)
        make_heap(ropes.begin(), ropes.end(), greater<int>());
        
        long long totalCost = 0;
        
        while (ropes.size() > 1) {
            // pop_heap() moves smallest element to the end
            pop_heap(ropes.begin(), ropes.end(), greater<int>());
            long long first = ropes.back();
            ropes.pop_back();
            
            // Extract second smallest
            pop_heap(ropes.begin(), ropes.end(), greater<int>());
            long long second = ropes.back();
            ropes.pop_back();
            
            // Combine the two ropes
            long long combined = first + second;
            totalCost += combined;
            
            cout << "Connect " << first << " + " << second << " = " << combined 
                 << " (total cost so far: " << totalCost << ")\n";
            
            // Add combined rope back and restore heap property
            ropes.push_back(combined);
            push_heap(ropes.begin(), ropes.end(), greater<int>());
        }
        
        return totalCost;
    }
};

void printAnalysis() {
    cout << "\n=== ALGORITHM ANALYSIS ===\n";
    cout << "Why greedy approach with min-heap is optimal:\n";
    cout << "1. Always connect the two smallest ropes first\n";
    cout << "2. This minimizes the intermediate rope length\n";
    cout << "3. Smaller intermediate ropes reduce future connection costs\n";
    cout << "4. Each connection affects ALL future operations\n";
    cout << "5. Example: ropes [3,3,9,9] - connect 3+3=6 first (not 3+9=12)\n\n";
    cout << "Time Complexity: O(n log n) for greedy, O(n² log n) for brute force\n";
    cout << "Space Complexity: O(n)\n\n";
}

int main() {
    printAnalysis();
    
    // TEST CASE 1: Standard case
    cout << "=== TEST CASE 1 ===\n";
    vector<int> ropes1 = {4, 3, 2, 6};
    cout << "Ropes: ";
    for (int r : ropes1) cout << r << " ";
    cout << "\n\n";
    
    RopeConnector rc;
    long long cost1 = rc.connectRopesOptimal(ropes1);
    cout << "\nTotal minimum cost: " << cost1 << "\n";
    
    // TEST CASE 2: Another example
    cout << "\n\n=== TEST CASE 2 ===\n";
    vector<int> ropes2 = {1, 2, 3, 4, 5};
    cout << "Ropes: ";
    for (int r : ropes2) cout << r << " ";
    cout << "\n\n";
    
    long long cost2 = rc.connectRopesOptimal(ropes2);
    cout << "\nTotal minimum cost: " << cost2 << "\n";
    
    // TEST CASE 3: Compare greedy vs brute force
    cout << "\n\n=== TEST CASE 3: GREEDY vs BRUTE FORCE ===\n";
    vector<int> ropes3 = {1, 3, 2};
    cout << "Ropes: ";
    for (int r : ropes3) cout << r << " ";
    cout << "\n\n";
    
    cout << "Greedy (Optimal):\n";
    long long greedyCost = rc.connectRopesOptimal(ropes3);
    cout << "Total cost: " << greedyCost << "\n";
    
    cout << "\nBrute Force (for comparison):\n";
    long long bruteCost = rc.connectRopesBruteForce(ropes3);
    cout << "Total cost: " << bruteCost << "\n";
    cout << "Both produce same result: " << (greedyCost == bruteCost ? "YES" : "NO") << "\n";
    
    // TEST CASE 4: Alternative heap implementation
    cout << "\n\n=== TEST CASE 4: ALTERNATIVE HEAP IMPLEMENTATION ===\n";
    vector<int> ropes4 = {10, 20, 30};
    cout << "Ropes: ";
    for (int r : ropes4) cout << r << " ";
    cout << "\n\n";
    
    RopeConnectorAlt rcAlt;
    long long cost4 = rcAlt.connectRopes(ropes4);
    cout << "\nTotal minimum cost: " << cost4 << "\n";
    
    // TEST CASE 5: Edge cases
    cout << "\n\n=== TEST CASE 5: EDGE CASES ===\n";
    vector<int> ropes5a = {5};
    cout << "Single rope [5]: Cost = " << rc.connectRopesOptimal(ropes5a) << "\n";
    
    vector<int> ropes5b = {10, 20};
    cout << "Two ropes [10, 20]: Cost = " << rc.connectRopesOptimal(ropes5b) << "\n";
    
    vector<int> ropes5c = {1, 1, 1, 1, 1};
    cout << "Five ropes [1,1,1,1,1]: Cost = " << rc.connectRopesOptimal(ropes5c) << "\n";
    
    return 0;
}