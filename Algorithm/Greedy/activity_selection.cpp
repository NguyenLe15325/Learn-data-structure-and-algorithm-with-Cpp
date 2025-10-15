/**
 * Title: Activity Selection Problem (Greedy Algorithm)
 * File: activity_selector.cpp
 * * THE PROBLEM:
 * The Activity Selection Problem is a classic optimization problem. Given a set of 
 * activities, each with a defined start and finish time, the goal is to select 
 * the maximum number of activities such that no two selected activities overlap. 
 * This is a common scheduling problem where you want to maximize the use of a resource 
 * (like a conference room or a single processor) that can only handle one task at a time.
 *
 * THE GREEDY STRATEGY:
 * This problem can be solved optimally using a greedy algorithm. The key greedy choice 
 * property is: Always select the activity that has the **earliest finish time** * among the available, non-overlapping activities.
 * * WHY IT WORKS (Optimality):
 * By selecting the activity that finishes earliest, we free up the shared resource 
 * as quickly as possible. This leaves the maximum possible time interval open for 
 * subsequent, compatible activities, guaranteeing the optimal solution (the maximum 
 * count of scheduled activities).
 * * ALGORITHM STEPS:
 * 1. Sort all activities in non-decreasing order of their finish times.
 * 2. Select the first activity (which finishes earliest).
 * 3. Iterate through the remaining sorted activities:
 * If the current activity's start time is greater than or equal to the finish time 
 * of the previously selected activity, select the current activity.
 *
 * This implementation uses C++ structs and std::sort for efficiency.
 */

#include <iostream>
#include <vector>
#include <algorithm>

// 1. Define the structure for an activity, holding its time slots and identifier.
struct Activity {
    int start;
    int finish;
    int id; // Identifier for easy tracking
};

// 2. Custom comparison function for sorting.
// This implements the core GREEDY CHOICE: sort by the earliest finish time.
bool compareActivities(const Activity& a, const Activity& b) {
    return a.finish < b.finish;
}

// 3. Activity Selection solver function
void activitySelection(std::vector<Activity>& activities) {
    
    // STEP 1: Sort activities based on the greedy criterion (earliest finish time first)
    std::sort(activities.begin(), activities.end(), compareActivities);

    std::cout << "--- Activities Sorted by Finish Time ---" << std::endl;
    for (const auto& act : activities) {
        std::cout << "Activity " << act.id 
                  << ": Start=" << act.start 
                  << ", Finish=" << act.finish << std::endl;
    }

    if (activities.empty()) {
        std::cout << "\nNo activities to select." << std::endl;
        return;
    }

    // STEP 2: Select the first activity (it finishes earliest by definition after sorting)
    std::vector<Activity> selected_activities;
    selected_activities.push_back(activities[0]);
    int last_finish_time = activities[0].finish;

    std::cout << "\n--- Selection Process ---" << std::endl;
    std::cout << "Selected Activity " << activities[0].id 
              << ": [" << activities[0].start << ", " << activities[0].finish 
              << "] (Initial choice)" << std::endl;

    // STEP 3: Iterate through the remaining sorted activities
    for (size_t i = 1; i < activities.size(); ++i) {
        
        const auto& current_activity = activities[i];
        
        // Check for compatibility: 
        // If the current activity starts at or after the last selected activity finished, select it.
        if (current_activity.start >= last_finish_time) {
            selected_activities.push_back(current_activity);
            last_finish_time = current_activity.finish; // Update the completion time boundary
            
            std::cout << "Selected Activity " << current_activity.id 
                      << ": [" << current_activity.start << ", " << current_activity.finish 
                      << "] (Compatible)" << std::endl;
        } else {
            // Activity overlaps, so we discard it and look at the next one
            std::cout << "Skipped Activity " << current_activity.id 
                      << ": [" << current_activity.start << ", " << current_activity.finish 
                      << "] (Overlaps with last finish time " << last_finish_time << ")" << std::endl;
        }
    }

    std::cout << "\n==============================================" << std::endl;
    std::cout << "Maximum number of activities selected: " << selected_activities.size() << std::endl;
    std::cout << "Selected Activity IDs (Start, Finish):" << std::endl;
    
    for (const auto& act : selected_activities) {
        std::cout << "- Activity " << act.id << " (Slot: " << act.start << " to " << act.finish << ")" << std::endl;
    }
    std::cout << "==============================================" << std::endl;
}

int main() {
    // Example activities: {start, finish, id}
    std::vector<Activity> activity_list = {
        {1, 4, 1},  // A
        {3, 5, 2},  // B
        {0, 6, 3},  // C
        {5, 7, 4},  // D
        {8, 9, 5},  // E
        {5, 9, 6}   // F
    };

    activitySelection(activity_list);

    return 0;
}
