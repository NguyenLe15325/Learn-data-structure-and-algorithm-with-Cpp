#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>

// Structure to represent a 2D point
struct Point {
    double x;
    double y;
};

/**
 * @brief Calculates the Euclidean distance between two 2D points.
 * @param p1 The first point.
 * @param p2 The second point.
 * @return The distance between p1 and p2.
 */
double calculateDistance(const Point& p1, const Point& p2) {
    // Euclidean Distance formula: sqrt((x2 - x1)^2 + (y2 - y1)^2)
    return std::hypot(p2.x - p1.x, p2.y - p1.y);
}

/**
 * @brief Implements the brute force algorithm for finding the closest pair of points.
 * * =========================================================================
 * CLOSEST PAIR OF POINTS (BRUTE FORCE)
 * =========================================================================
 * The algorithm checks the distance between every unique pair of points.
 * * * Brute Force Strategy:
 * 1. Initialize min_distance to a very large value (infinity).
 * 2. Use two nested loops to iterate through all distinct pairs (i, j) where i < j.
 * 3. Calculate the distance for each pair.
 * 4. Update min_distance and store the pair if a smaller distance is found.
 * * * Time Complexity: O(N^2)
 * Since every pair of points is compared exactly once, the number of 
 * distance calculations is proportional to N-squared.
 * * @param points A vector of 2D Point structures.
 * @return The minimum distance found between any two points.
 */
double bruteForceClosestPair(const std::vector<Point>& points, Point& pair1, Point& pair2) {
    int N = points.size();

    if (N < 2) {
        // We need at least two points to form a pair.
        return std::numeric_limits<double>::max();
    }

    // Initialize minimum distance to a very large value (effectively infinity).
    double min_distance = std::numeric_limits<double>::max();

    // Outer loop: iterate through all points i from 0 to N-2
    for (int i = 0; i < N - 1; ++i) {
        // Inner loop: iterate through all points j starting from i + 1 (to avoid checking 
        // the same pair twice and comparing a point to itself).
        for (int j = i + 1; j < N; ++j) {
            
            // Calculate distance between points[i] and points[j]
            double current_distance = calculateDistance(points[i], points[j]);

            // If the current distance is smaller than the minimum distance found so far, update.
            if (current_distance < min_distance) {
                min_distance = current_distance;
                pair1 = points[i];
                pair2 = points[j];
            }
        }
    }

    return min_distance;
}

int main() {
    // Set output precision for clean double printing
    std::cout << std::fixed << std::setprecision(4);

    // Test data set of 2D points
    std::vector<Point> test_points = {
        {2.0, 3.0},   // P0
        {12.0, 30.0}, // P1
        {40.0, 50.0}, // P2
        {5.0, 1.0},   // P3
        {1.2, 4.0},   // P4
        {3.0, 3.1}    // P5 (Closest to P0)
    };

    Point closest_p1, closest_p2;
    double min_dist = bruteForceClosestPair(test_points, closest_p1, closest_p2);

    std::cout << "--- Closest Pair of Points Brute Force O(N^2) ---" << std::endl;
    std::cout << "Total points: " << test_points.size() << std::endl;
    
    if (min_dist != std::numeric_limits<double>::max()) {
        std::cout << "\nMinimum distance found: " << min_dist << std::endl;
        std::cout << "Closest pair 1: (" << closest_p1.x << ", " << closest_p1.y << ")" << std::endl;
        std::cout << "Closest pair 2: (" << closest_p2.x << ", " << closest_p2.y << ")" << std::endl;
    } else {
        std::cout << "Error: Not enough points to form a pair." << std::endl;
    }

    return 0;
}
