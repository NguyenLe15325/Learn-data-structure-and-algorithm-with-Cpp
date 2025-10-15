#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

// Structure to hold job details
struct Job {
    char id;        // Job ID (e.g., 'A', 'B', 'C')
    int deadline;   // Deadline by which the job must be completed
    int profit;     // Profit earned if the job is completed
};

// Custom comparison function for sorting jobs.
// This implements the GREEDY CHOICE: Sort jobs in DESCENDING order of profit. 
// We prioritize the jobs that give the most return.
bool compareJobs(const Job& a, const Job& b) {
    return a.profit > b.profit;
}

/**
 * @brief Solves the Job Sequencing Problem using the Greedy approach.
 * * The strategy is to select the most profitable job and schedule it in the latest 
 * possible free slot before its deadline to maximize flexibility for later jobs.
 * * @param jobs A vector of Job structures containing ID, deadline, and profit.
 */
void jobSequencing(std::vector<Job>& jobs) {
    
    // 1. Sort the jobs by profit in descending order (The primary greedy step)
    std::sort(jobs.begin(), jobs.end(), compareJobs);

    // 2. Determine the maximum possible time slot needed.
    // This defines the size of our schedule array.
    int max_deadline = 0;
    for (const auto& job : jobs) {
        if (job.deadline > max_deadline) {
            max_deadline = job.deadline;
        }
    }

    // 3. Initialize the schedule array (or time slots).
    // The index represents the time slot (e.g., index 0 is slot 1, index 1 is slot 2).
    // We use a vector of characters, initialized to ' ' (space), indicating the slot is free.
    std::vector<char> schedule(max_deadline, ' ');
    long long total_profit = 0;
    int job_count = 0;

    std::cout << "--- Scheduling Process (Max " << max_deadline << " Slots) ---" << std::endl;
    std::cout << std::left << std::setw(5) << "Job" << std::setw(10) << "Profit" << std::setw(10) << "Deadline" << "Action" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    // 4. Iterate through all sorted jobs (from highest profit to lowest)
    for (const auto& job : jobs) {
        
        // Find a free slot for the current job.
        // We search backward from the job's deadline (index = deadline - 1) down to the first slot (index 0).
        // This is the secondary greedy choice: schedule as late as possible.
        for (int i = job.deadline - 1; i >= 0; --i) {
            
            // Check if the current slot is free (' ' indicates free)
            if (schedule[i] == ' ') {
                
                // Slot found: Schedule the job
                schedule[i] = job.id;
                total_profit += job.profit;
                job_count++;
                
                std::cout << std::left << std::setw(5) << job.id << std::setw(10) << job.profit << std::setw(10) << job.deadline 
                          << "Scheduled in Slot " << (i + 1) << "." << std::endl;
                
                // Break the inner loop since the job is now successfully scheduled
                break;
            }
        }
        
        // If the inner loop finishes without finding a slot, the job is rejected
        if (schedule[job.deadline - 1] != job.id && job.deadline <= max_deadline) {
             std::cout << std::left << std::setw(5) << job.id << std::setw(10) << job.profit << std::setw(10) << job.deadline 
                       << "Rejected (No free slot before deadline)." << std::endl;
        }
    }

    // 5. Output the results
    std::cout << "\n==============================================" << std::endl;
    std::cout << "Total jobs selected: " << job_count << std::endl;
    std::cout << "Maximum achievable profit: " << total_profit << std::endl;
    
    std::cout << "Optimal Job Sequence (Time Slots 1 to " << max_deadline << "):" << std::endl;
    std::cout << "[ ";
    for (int i = 0; i < max_deadline; ++i) {
        // If the slot is empty, show '-' for clarity
        char job_id = (schedule[i] == ' ') ? '-' : schedule[i];
        std::cout << job_id << (i < max_deadline - 1 ? " | " : " ");
    }
    std::cout << "]" << std::endl;
    std::cout << "==============================================" << std::endl;
}

int main() {
    // Example dataset: {ID, Deadline, Profit}
    std::vector<Job> jobs_list = {
        {'a', 2, 100}, // J1: Profit 100, Deadline 2
        {'b', 1, 19},  // J2: Profit 19,  Deadline 1
        {'c', 2, 27},  // J3: Profit 27,  Deadline 2
        {'d', 1, 25},  // J4: Profit 25,  Deadline 1
        {'e', 3, 15},  // J5: Profit 15,  Deadline 3
        {'f', 1, 8},   // J6: Profit 8,   Deadline 1
        {'g', 3, 50}   // J7: Profit 50,  Deadline 3
    };

    jobSequencing(jobs_list);

    return 0;
}
