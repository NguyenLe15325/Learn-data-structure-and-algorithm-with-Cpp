#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

// 1. Define the structure for an item
struct Item {
    int value;
    int weight;
    double ratio; // Value-to-weight ratio (V/W)
    int id;       // Identifier for easier tracking in output
};

// 2. Custom comparison function for sorting
// This implements the GREEDY CHOICE: always prioritize the item with the highest ratio.
bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio; // Sort in descending order of ratio
}

// 3. Fractional Knapsack solver function
double fractional_knapsack(double capacity, std::vector<Item>& items) {
    // Calculate the ratio for all items first
    for (size_t i = 0; i < items.size(); ++i) {
        items[i].ratio = (double)items[i].value / items[i].weight;
        items[i].id = i + 1; // Assign a simple ID
    }

    // Sort items based on the greedy criterion (highest ratio first)
    std::sort(items.begin(), items.end(), compareItems);

    double current_weight = 0.0;
    double total_value = 0.0;

    std::cout << "\n--- Starting Knapsack Process (Capacity: " << std::fixed << std::setprecision(2) << capacity << "kg) ---" << std::endl;
    std::cout << "Items sorted by V/W ratio:" << std::endl;

    // Iterate through the sorted items
    for (const auto& item : items) {
        // If the knapsack is full, stop
        if (capacity <= 0) {
            break;
        }

        std::cout << "Checking Item " << item.id 
                  << " (V: " << item.value << ", W: " << item.weight 
                  << ", Ratio: " << std::fixed << std::setprecision(2) << item.ratio << ")";

        // Case A: The whole item fits
        if (item.weight <= capacity) {
            // Take the entire item
            capacity -= item.weight;
            total_value += item.value;
            
            std::cout << " -> Took WHOLE item. Remaining Capacity: " 
                      << std::fixed << std::setprecision(2) << capacity << "kg" << std::endl;
        }
        // Case B: Only a fraction of the item fits
        else {
            double fraction = capacity / item.weight;
            double value_added = item.value * fraction;

            // Take the fraction required to fill the knapsack
            total_value += value_added;
            capacity = 0; // Knapsack is now full

            std::cout << " -> Took FRACTION (" << std::fixed << std::setprecision(2) << fraction * 100 
                      << "%). Value Added: $" << std::fixed << std::setprecision(2) << value_added 
                      << ". Knapsack is now FULL." << std::endl;
        }
    }

    return total_value;
}

int main() {
    // Define items: {value, weight}
    // Item 1: V=100, W=20 (Ratio 5.0)
    // Item 2: V=60, W=10 (Ratio 6.0)
    // Item 3: V=120, W=30 (Ratio 4.0)
    std::vector<Item> items = {
        {100, 20},
        {60, 10},
        {120, 30}
    };

    double knapsack_capacity = 50.0;

    // Set output formatting for floating point numbers
    std::cout << std::fixed << std::setprecision(2);

    double max_value = fractional_knapsack(knapsack_capacity, items);

    std::cout << "\n==============================================" << std::endl;
    std::cout << "Final Knapsack Capacity: " << knapsack_capacity << "kg" << std::endl;
    std::cout << "Maximum Total Value: $" << max_value << std::endl;
    std::cout << "==============================================" << std::endl;

    return 0;
}
