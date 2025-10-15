/**
 * @file greedy_change_maker.cpp
 * @brief Implementation of the Change-Making Problem using a Greedy Algorithm.
 * * The greedy strategy works optimally when the coin system is canonical (like USD or EUR).
 * The algorithm attempts to use the largest possible coin denomination first.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

/**
 * @brief Finds the minimum number of coins needed to make a specific amount using a greedy strategy.
 * * NOTE: This function assumes the coins vector is already sorted in descending order, 
 * which is critical for the greedy approach to work correctly.
 * * @param denominations A vector of available coin values (must be sorted descending).
 * @param amount The target amount to make change for.
 * @return A map containing the count of each coin used.
 */
std::map<int, int> solveChangeMaking(std::vector<int> denominations, int amount) {
    // 1. Sort denominations in descending order. 
    // This is the core requirement for the greedy algorithm.
    std::sort(denominations.rbegin(), denominations.rend());

    int remaining_amount = amount;
    std::map<int, int> result_coins;
    int total_coins_used = 0;

    std::cout << "--- Change Calculation for Amount: $" << amount << " ---" << std::endl;

    // 2. Iterate through the sorted denominations
    for (int coin : denominations) {
        // As long as the current coin can be used, take it
        while (remaining_amount >= coin) {
            remaining_amount -= coin;
            result_coins[coin]++;
            total_coins_used++;
        }
        
        // Optional: Print progress for clarity
        if (result_coins.count(coin)) {
            std::cout << "Used " << result_coins[coin] << " x $" << coin 
                      << " coins. Remaining: $" << remaining_amount << std::endl;
        }

        // Optimization: if remaining_amount is 0, we are done
        if (remaining_amount == 0) {
            break;
        }
    }

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Total Coins Used: " << total_coins_used << std::endl;
    
    if (remaining_amount > 0) {
        std::cout << "WARNING: Could not make exact change. $" 
                  << remaining_amount << " remaining." << std::endl;
    }

    return result_coins;
}

int main() {
    // Standard US Coin Denominations (Quarters, Dimes, Nickels, Pennies)
    std::vector<int> us_coins = {1, 5, 10, 25}; 
    
    // Example 1: Standard case
    int target_amount_1 = 63;
    std::map<int, int> change_1 = solveChangeMaking(us_coins, target_amount_1);

    std::cout << "\n--- Final Result for $" << target_amount_1 << " ---" << std::endl;
    for (const auto& pair : change_1) {
        std::cout << pair.second << " x $" << pair.first << " coin(s)" << std::endl;
    }
    std::cout << "===================================\n" << std::endl;
    
    
    // Example 2: Amount requiring many coins
    int target_amount_2 = 94;
    std::map<int, int> change_2 = solveChangeMaking(us_coins, target_amount_2);

    std::cout << "\n--- Final Result for $" << target_amount_2 << " ---" << std::endl;
    for (const auto& pair : change_2) {
        std::cout << pair.second << " x $" << pair.first << " coin(s)" << std::endl;
    }
    std::cout << "===================================\n" << std::endl;


    // Example 3: Edge case where greedy fails (Non-Canonical System)
    // If coins were {1, 5, 9} and target was 10.
    // Greedy would pick: 9 (1 coin) + 1 (1 coin) = 2 coins.
    // Optimal is: 5 (2 coins).
    std::vector<int> tricky_coins = {1, 5, 9};
    int target_amount_3 = 10;
    std::cout << "--- Testing Non-Canonical System {1, 5, 9} ---" << std::endl;
    solveChangeMaking(tricky_coins, target_amount_3);
    std::cout << "Note: For this system, the greedy algorithm is NOT optimal (2 coins vs optimal 2x$5)." << std::endl;
    std::cout << "===================================" << std::endl;


    return 0;
}
