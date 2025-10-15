/*
===============================================================================
EGYPTIAN FRACTION - GREEDY APPROACH
===============================================================================

PROBLEM STATEMENT:
------------------
Egyptian Fractions are fractions where the numerator is always 1, and the
denominator is a positive integer. For example: 1/2, 1/3, 1/5, 1/7, etc.

Given any fraction p/q (where 0 < p/q < 1), express it as a sum of distinct
Egyptian fractions.

EXAMPLE:
--------
Input: 2/3
Output: 1/2 + 1/6
Verification: 1/2 + 1/6 = 3/6 + 1/6 = 4/6 = 2/3 ✓

Input: 5/7
Output: 1/2 + 1/6 + 1/42
Verification: 1/2 + 1/6 + 1/42 = 21/42 + 7/42 + 1/42 = 29/42... wait that's wrong
Let me recalculate: 5/7 = 1/2 + 3/14 = 1/2 + 1/5 + 1/70

Actually, let me use correct example:
Input: 5/7
Output: 1/2 + 1/5 + 1/70
Verification: 1/2 + 1/5 + 1/70 = 35/70 + 14/70 + 1/70 = 50/70 = 5/7 ✓

GREEDY STRATEGY:
----------------
The greedy approach repeatedly finds the LARGEST Egyptian fraction (smallest
denominator) that is less than or equal to the remaining fraction.

Why this approach?
1. Start with the largest unit fraction ≤ p/q (i.e., the smallest valid denominator)
2. Subtract it from p/q to get a remainder
3. Repeat with the remainder until remainder becomes 0

This is guaranteed to terminate because:
- Each step reduces the numerator
- Eventually we reach a fraction with numerator 1 (Egyptian fraction)

HOW TO FIND THE LARGEST EGYPTIAN FRACTION ≤ p/q:
---------------------------------------------------
We want the smallest denominator d such that 1/d ≤ p/q

Mathematical formula:
  1/d ≤ p/q  →  q ≤ p*d  →  d ≥ q/p

The smallest such d is: d = ceil(q/p) = (q + p - 1) / p

EXAMPLE WALKTHROUGH WITH 2/3:
------------------------------
Start: fraction = 2/3

Step 1: Find largest Egyptian fraction ≤ 2/3
  d = ceil(3/2) = ceil(1.5) = 2
  So largest Egyptian fraction is 1/2
  Add 1/2 to result
  Remaining: 2/3 - 1/2 = 4/6 - 3/6 = 1/6
  
Step 2: Find largest Egyptian fraction ≤ 1/6
  d = ceil(6/1) = 6
  So largest Egyptian fraction is 1/6
  Add 1/6 to result
  Remaining: 1/6 - 1/6 = 0
  
Done! Result: 1/2 + 1/6

TIME COMPLEXITY: O(log q) on average, worst case O(p)
  - Each step at least doubles the denominator
  - Maximum steps is bounded by logarithmic growth

SPACE COMPLEXITY: O(number of Egyptian fractions in result)

INTERESTING FACTS:
-------------------
1. Ancient Egyptians (1600 BC) used this system for practical calculations
2. Every positive rational number can be expressed as sum of distinct
   Egyptian fractions
3. The representation is NOT unique - same fraction can be written multiple ways
4. The Greedy algorithm produces the shortest representation in many cases

===============================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a fraction
struct Fraction {
    long long numerator;
    long long denominator;
    
    Fraction(long long n, long long d) : numerator(n), denominator(d) {}
    
    // Print fraction as text
    void print() const {
        cout << numerator << "/" << denominator;
    }
};

// Structure to represent Egyptian Fraction result
struct EgyptianFraction {
    vector<long long> denominators;  // Store denominators (numerator is always 1)
    
    void print() const {
        for (size_t i = 0; i < denominators.size(); i++) {
            if (i > 0) cout << " + ";
            cout << "1/" << denominators[i];
        }
        cout << "\n";
    }
};

// Helper function to calculate GCD (for fraction reduction)
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Helper function to reduce a fraction to lowest terms
Fraction reduceFraction(long long p, long long q) {
    long long g = gcd(p, q);
    return Fraction(p / g, q / g);
}

/*
GREEDY ALGORITHM FOR EGYPTIAN FRACTIONS
=========================================

Algorithm:
----------
1. While fraction is not zero:
   a. Find the smallest denominator d such that 1/d ≤ p/q
   b. d = ceil(q/p)
   c. Add d to result
   d. Subtract 1/d from p/q to get new remainder
   e. Reduce the remainder fraction

Example: Convert 5/7
- Step 1: d = ceil(7/5) = 2, subtract 1/2: 5/7 - 1/2 = 10/14 - 7/14 = 3/14
- Step 2: d = ceil(14/3) = 5, subtract 1/5: 3/14 - 1/5 = 15/70 - 14/70 = 1/70
- Step 3: d = ceil(70/1) = 70, subtract 1/70: 1/70 - 1/70 = 0
- Result: 1/2 + 1/5 + 1/70
*/
EgyptianFraction egyptianFractionGreedy(long long numerator, long long denominator) {
    EgyptianFraction result;
    
    // Step 0: Reduce fraction to lowest terms
    Fraction frac = reduceFraction(numerator, denominator);
    long long p = frac.numerator;
    long long q = frac.denominator;
    
    cout << "Starting with: " << p << "/" << q << "\n";
    cout << "Decomposition steps:\n";
    
    int step = 1;
    
    // Main greedy loop
    while (p > 0) {
        /*
        FIND LARGEST EGYPTIAN FRACTION ≤ p/q
        ======================================
        We want: 1/d ≤ p/q
        Rearranging: q ≤ p*d
        Therefore: d ≥ q/p
        
        The smallest integer d satisfying this is: d = ceil(q/p)
        
        In integer arithmetic: ceil(q/p) = (q + p - 1) / p
        This avoids floating point and ensures correct rounding up.
        */
        long long d = (q + p - 1) / p;  // Ceiling division
        
        result.denominators.push_back(d);
        
        cout << "  Step " << step << ": Largest Egyptian fraction <= " 
             << p << "/" << q << " is 1/" << d << "\n";
        
        /*
        SUBTRACT 1/d FROM p/q
        =====================
        p/q - 1/d = (p*d - q) / (q*d)
        
        We need to compute this carefully to maintain exact arithmetic.
        */
        p = p * d - q;  // New numerator
        q = q * d;      // New denominator
        
        // Reduce to lowest terms for efficiency and clarity
        if (p > 0) {
            Fraction reduced = reduceFraction(p, q);
            p = reduced.numerator;
            q = reduced.denominator;
            cout << "    Remaining: " << p << "/" << q << "\n";
        }
        
        step++;
    }
    
    return result;
}

/*
ALTERNATIVE: VERBOSE VERSION WITH DETAILED EXPLANATIONS
=========================================================
This version shows step-by-step what's happening in the algorithm.
*/
void egyptianFractionVerbose(long long numerator, long long denominator) {
    cout << "\n=== DETAILED EXPLANATION ===\n";
    cout << "Converting " << numerator << "/" << denominator << " to Egyptian Fraction\n\n";
    
    Fraction frac = reduceFraction(numerator, denominator);
    long long p = frac.numerator;
    long long q = frac.denominator;
    
    cout << "After reduction: " << p << "/" << q << "\n\n";
    
    int step = 1;
    
    while (p > 0) {
        cout << "STEP " << step << ":\n";
        cout << "  Current fraction: " << p << "/" << q << "\n";
        
        long long d = (q + p - 1) / p;
        
        cout << "  Calculate smallest denominator:\n";
        cout << "    d = ceil(q/p) = ceil(" << q << "/" << p << ")\n";
        cout << "    d = (" << q << " + " << p << " - 1) / " << p << "\n";
        cout << "    d = " << (q + p - 1) << " / " << p << " = " << d << "\n";
        cout << "  → Add 1/" << d << " to result\n";
        
        cout << "  Subtract 1/" << d << " from " << p << "/" << q << ":\n";
        cout << "    " << p << "/" << q << " - 1/" << d << "\n";
        cout << "    = (" << p << "*" << d << " - " << q << ") / (" << q << "*" << d << ")\n";
        cout << "    = (" << (p*d) << " - " << q << ") / " << (q*d) << "\n";
        cout << "    = " << (p*d - q) << " / " << (q*d) << "\n";
        
        p = p * d - q;
        q = q * d;
        
        if (p > 0) {
            Fraction reduced = reduceFraction(p, q);
            long long oldP = p, oldQ = q;
            p = reduced.numerator;
            q = reduced.denominator;
            cout << "    = " << oldP << "/" << oldQ << " (reduced to " << p << "/" << q << ")\n";
        } else {
            cout << "    = 0 (DONE!)\n";
        }
        
        cout << "\n";
        step++;
    }
}

/*
VERIFY RESULT
=============
Check if sum of Egyptian fractions equals original fraction.
*/
bool verifyEgyptianFraction(long long originalNum, long long originalDen,
                           const vector<long long>& denominators) {
    // Start with 0
    long long sumNum = 0, sumDen = 1;
    
    // Add each Egyptian fraction 1/d
    for (long long d : denominators) {
        // sumNum/sumDen + 1/d = (sumNum*d + sumDen) / (sumDen*d)
        sumNum = sumNum * d + sumDen;
        sumDen = sumDen * d;
        
        // Reduce to avoid overflow
        long long g = gcd(sumNum, sumDen);
        sumNum /= g;
        sumDen /= g;
    }
    
    // Reduce original fraction
    long long g = gcd(originalNum, originalDen);
    originalNum /= g;
    originalDen /= g;
    
    // Check if equal
    return (sumNum == originalNum && sumDen == originalDen);
}

int main() {
    cout << "===== EGYPTIAN FRACTION - GREEDY ALGORITHM =====\n\n";
    
    // TEST CASE 1: 2/3
    cout << "TEST CASE 1: 2/3\n";
    cout << "===============\n";
    EgyptianFraction result1 = egyptianFractionGreedy(2, 3);
    cout << "\nResult: ";
    result1.print();
    cout << "Verified: " << (verifyEgyptianFraction(2, 3, result1.denominators) ? "YES" : "NO") << "\n";
    
    // TEST CASE 2: 5/7
    cout << "\n\nTEST CASE 2: 5/7\n";
    cout << "===============\n";
    EgyptianFraction result2 = egyptianFractionGreedy(5, 7);
    cout << "\nResult: ";
    result2.print();
    cout << "Verified: " << (verifyEgyptianFraction(5, 7, result2.denominators) ? "YES" : "NO") << "\n";
    
    // TEST CASE 3: 3/4
    cout << "\n\nTEST CASE 3: 3/4\n";
    cout << "===============\n";
    EgyptianFraction result3 = egyptianFractionGreedy(3, 4);
    cout << "\nResult: ";
    result3.print();
    cout << "Verified: " << (verifyEgyptianFraction(3, 4, result3.denominators) ? "YES" : "NO") << "\n";
    
    // TEST CASE 4: 7/12
    cout << "\n\nTEST CASE 4: 7/12\n";
    cout << "================\n";
    EgyptianFraction result4 = egyptianFractionGreedy(7, 12);
    cout << "\nResult: ";
    result4.print();
    cout << "Verified: " << (verifyEgyptianFraction(7, 12, result4.denominators) ? "YES" : "NO") << "\n";
    
    // TEST CASE 5: Verbose example
    cout << "\n\nTEST CASE 5: VERBOSE WALKTHROUGH OF 5/7\n";
    cout << "========================================\n";
    egyptianFractionVerbose(5, 7);
    
    // TEST CASE 6: Edge cases
    cout << "\nTEST CASE 6: EDGE CASES\n";
    cout << "======================\n";
    cout << "1/2: ";
    EgyptianFraction result6a = egyptianFractionGreedy(1, 2);
    result6a.print();
    
    cout << "1/5: ";
    EgyptianFraction result6b = egyptianFractionGreedy(1, 5);
    result6b.print();
    
    cout << "1/1 (if allowed): ";
    EgyptianFraction result6c = egyptianFractionGreedy(1, 1);
    result6c.print();
    
    return 0;
}