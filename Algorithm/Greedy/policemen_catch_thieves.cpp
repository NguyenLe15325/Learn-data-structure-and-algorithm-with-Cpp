/**
 * @file policemen_thieves.cpp
 * @brief Solution for the Policemen Catch Thieves Problem using a Greedy Two-Pointer Strategy.
 * * =========================================================================
 * PROBLEM DESCRIPTION:
 * We are given an arrangement of Policemen ('P') and Thieves ('T') along a line
 * (represented by a string or array). Each policeman has a fixed catching range K.
 * A policeman at index 'i' can catch a thief at index 'j' if and only if:
 * 1. The thief has not already been caught.
 * 2. The policeman has not already made a catch.
 * 3. The distance between them is within the range: |i - j| <= K.
 * * GOAL: Find the maximum number of thieves that can be caught.
 * * =========================================================================
 * GREEDY STRATEGY (Two-Pointer Approach):
 * The greedy choice is to always match the current, available policeman with the 
 * closest, available thief *within their range K*. 
 * * Why this works:
 * 1. By always matching the closest pair, we maximize the chances of catching the 
 * thief, while minimizing the distance used by the policeman.
 * 2. This effectively saves the "far-reaching" capacity of other policemen for 
 * thieves that might be harder to reach.
 * 3. By processing the policemen and thieves in sorted order of their positions, 
 * the two-pointer technique ensures we quickly check the best potential matches 
 * in O(N) time complexity (after the initial O(N) extraction).
 * =========================================================================
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

/**
 * @brief Calculates the maximum number of thieves caught using a greedy two-pointer approach.
 *
 * @param arrangement A string representing the line of policemen ('P') and thieves ('T').
 * @param K The maximum catching distance (range).
 * @return The maximum number of thieves that can be caught.
 */
int maxThieves(const std::string& arrangement, int K) {
    // 1. DATA PREPARATION: Extract and store the indices of all Policemen and Thieves.
    // Since we iterate sequentially, both vectors 'policemen' and 'thieves' 
    // will be naturally sorted by their position index.
    std::vector<int> policemen;
    std::vector<int> thieves;

    for (int i = 0; i < arrangement.length(); ++i) {
        if (arrangement[i] == 'P') {
            policemen.push_back(i);
        } else if (arrangement[i] == 'T') {
            thieves.push_back(i);
        }
    }

    // 2. INITIALIZATION
    int catches = 0;
    size_t p_ptr = 0; // Pointer for the next available policeman
    size_t t_ptr = 0; // Pointer for the next available thief

    // 3. CORE GREEDY MATCHING LOOP
    while (p_ptr < policemen.size() && t_ptr < thieves.size()) {
        int p_pos = policemen[p_ptr];
        int t_pos = thieves[t_ptr];
        int distance = std::abs(p_pos - t_pos);

        if (distance <= K) {
            // SCENARIO A: CATCH MADE (The Greedy Choice)
            // The current thief and policeman are within range K.
            // This is the optimal, local, greedy choice: take the catch and proceed.
            catches++;
            p_ptr++; // This policeman is used up, move to the next.
            t_ptr++; // This thief is caught, move to the next.

        } else if (p_pos < t_pos) {
            // SCENARIO B: POLICEMAN IS TOO FAR LEFT (P ........ T)
            // The policeman is far to the left of the thief, and the distance is > K.
            // Since the policeman pointer (`p_ptr`) represents the earliest available 
            // policeman, this specific policeman at `p_pos` can *never* catch the 
            // current thief at `t_pos` (or any thief to its right).
            // We must advance to the next policeman to find a valid match.
            p_ptr++;

        } else { // t_pos < p_pos
            // SCENARIO C: THIEF IS TOO FAR LEFT (T ........ P)
            // The thief is far to the left of the policeman, and the distance is > K.
            // Since the thief pointer (`t_ptr`) represents the earliest available 
            // thief, this specific thief at `t_pos` is now too far away from the 
            // current policeman at `p_pos` (and all subsequent policemen).
            // We must advance to the next thief to find a valid match.
            t_ptr++;
        }
    }

    return catches;
}

int main() {
    // Example 1: K=1 (Adjacent catch only)
    // PTPT -> P(0) catches T(1), P(2) catches T(3). Total: 2.
    int K1 = 1;
    std::string arr1 = "PTPT";
    std::cout << "Arrangement: " << arr1 << ", K=" << K1 << std::endl;
    std::cout << "Max Catches: " << maxThieves(arr1, K1) << std::endl; 
    std::cout << "-----------------------------------" << std::endl;

    // Example 2: K=2 (Demonstrates non-adjacent catch and pointer movement)
    // Indices: 012345
    // P(0), T(1), P(3), P(4), T(5)
    // 1. P(0) vs T(1): Distance 1 (<= 2). CATCH! Used: P(0), T(1).
    // 2. Next P(3) vs Next T(5): Distance 2 (<= 2). CATCH! Used: P(3), T(5).
    int K2 = 2;
    std::string arr2 = "PTPPTT";
    std::cout << "Arrangement: " << arr2 << ", K=" << K2 << std::endl;
    std::cout << "Max Catches: " << maxThieves(arr2, K2) << std::endl; 
    std::cout << "-----------------------------------" << std::endl;

    // Example 3: K=3 (More complex overlapping)
    // T(0), P(2), P(3), T(4), T(5), P(6)
    // 1. P(2) vs T(0): Distance 2 (<= 3). CATCH! Used: P(2), T(0).
    // 2. Next P(3) vs Next T(4): Distance 1 (<= 3). CATCH! Used: P(3), T(4).
    // 3. Next P(6) vs Next T(5): Distance 1 (<= 3). CATCH! Used: P(6), T(5).
    int K3 = 3;
    std::string arr3 = "TPPTTPT";
    std::cout << "Arrangement: " << arr3 << ", K=" << K3 << std::endl;
    std::cout << "Max Catches: " << maxThieves(arr3, K3) << std::endl; 
    std::cout << "-----------------------------------" << std::endl;
    
    return 0;
}
