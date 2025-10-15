#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <list> 

using namespace std;

using duration_ms = std::chrono::milliseconds;

// --- GLOBAL CONSTANTS for Scaling ---
const int N_SLOW = 5000;    
const int N_FAST = 50000;   
const int N_LINEAR = 100000; 
const int K_MAX = 50000;     
const int K_MAX_GENERAL = 100000; 

// --- Test Data Generation Functions ---

vector<int> generateRandomVector(int size, int max_val) {
    vector<int> data(size);
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
    for (int i = 0; i < size; ++i) {
        data[i] = rand() % max_val;
    }
    return data;
}

vector<int> generateNearlySortedVector(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; ++i) {
        data[i] = i;
    }
    int swaps = size / 100;
    for (int i = 0; i < swaps; ++i) {
        int idx1 = rand() % size;
        int idx2 = rand() % size;
        swap(data[idx1], data[idx2]);
    }
    return data;
}

vector<int> generateReverseSortedVector(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; ++i) {
        data[i] = size - i;
    }
    return data;
}

// --- Benchmarking Helper ---

long long benchmarkSort(void (*sortFunc)(vector<int>&), vector<int> data) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(data);
    auto end = chrono::high_resolution_clock::now();
    
    if (!is_sorted(data.begin(), data.end())) {
        cerr << "Error: Algorithm failed to sort correctly." << endl;
        return -1; 
    }

    return chrono::duration_cast<duration_ms>(end - start).count();
}

// ====================================================================
// Sorting Algorithms (O(N^2), O(N log N), O(N+K))
// The quick sort pivot remains fixed to prevent the worst-case O(N^2) on structured data.
// ====================================================================

// --- O(N^2) ---
void bubbleSort(vector<int>& arr) { /* ... implementation ... */
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false) break; 
    }
}
void insertionSort(vector<int>& arr) { /* ... implementation ... */
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void selectionSort(vector<int>& arr) { /* ... implementation ... */
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
    }
}

// --- O(N log N) ---
int partition(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    swap(arr[mid], arr[high]); 
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
void quickSortRecursive(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortRecursive(arr, low, pi - 1);
        quickSortRecursive(arr, pi + 1, high);
    }
}
void quickSort(vector<int>& arr) {
    if (!arr.empty()) quickSortRecursive(arr, 0, arr.size() - 1);
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left; 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { arr[k++] = L[i++]; } else { arr[k++] = R[j++]; }
    }
    while (i < n1) { arr[k++] = L[i++]; }
    while (j < n2) { arr[k++] = R[j++]; }
}
void mergeSortRecursive(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortRecursive(arr, left, mid);
    mergeSortRecursive(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
void mergeSort(vector<int>& arr) { mergeSortRecursive(arr, 0, arr.size() - 1); }

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// --- O(N+K) ---
void countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    int max_val = *max_element(arr.begin(), arr.end());
    vector<int> count(max_val + 1, 0);
    vector<int> output(arr.size());
    for (int x : arr) count[x]++;
    for (int i = 1; i <= max_val; i++) count[i] += count[i - 1];
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    arr = output;
}
int getMax(const vector<int>& arr) {
    if (arr.empty()) return 0;
    int max_val = arr[0];
    for (int x : arr) {
        if (x > max_val) max_val = x;
    }
    return max_val;
}
void countSortByDigit(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0}; 
    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
}
void radixSort(vector<int>& arr) {
    if (arr.empty()) return;
    int m = getMax(arr); 
    for (int exp = 1; m / exp > 0; exp *= 10) countSortByDigit(arr, exp);
}
void bucketSort(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return;
    vector<list<int>> buckets(n);
    int max_val = *max_element(arr.begin(), arr.end());
    int min_val = *min_element(arr.begin(), arr.end());
    if (max_val == min_val) return; 
    double range = (double)(max_val - min_val);
    for (int i = 0; i < n; i++) {
        int bucketIndex = floor(((double)arr[i] - min_val) / range * (n - 1));
        bucketIndex = max(0, min(bucketIndex, n - 1)); 
        buckets[bucketIndex].push_back(arr[i]);
    }
    for (int i = 0; i < n; i++) { buckets[i].sort(); }
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int val : buckets[i]) { arr[index++] = val; }
    }
}

// ====================================================================
// Main Execution and Consolidated Output Logic
// ====================================================================

void printTableHeader() {
    cout << left << setw(20) << "Algorithm" 
         << left << setw(15) << "Complexity" 
         << left << setw(15) << "Time (ms)" << endl;
    cout << "--------------------------------------------------------" << endl;
}

void printResultRow(const string& name, const string& complexity, long long time, int size) {
    cout << left << setw(20) << name
         << left << setw(15) << complexity 
         << left << setw(15) << time << " (" << size << ")" << endl;
}

void runAndPrintGeneral(const string& data_type, vector<int>(*dataGenerator)(int)) {
    cout << "\n--- Test Case: " << data_type << " Data ---" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "O(N^2) Algorithms (N=" << N_SLOW << ")" << endl;
    cout << "O(N log N) Algorithms (N=" << N_FAST << ")" << endl;
    
    // Data Generation
    vector<int> data_slow = dataGenerator(N_SLOW);
    vector<int> data_fast = dataGenerator(N_FAST);

    // Run N^2 Sorts
    long long time_bubble = benchmarkSort(bubbleSort, data_slow);
    long long time_insertion = benchmarkSort(insertionSort, data_slow);
    long long time_selection = benchmarkSort(selectionSort, data_slow);

    // Run N log N Sorts
    long long time_quick = benchmarkSort(quickSort, data_fast);
    long long time_merge = benchmarkSort(mergeSort, data_fast);
    long long time_heap = benchmarkSort(heapSort, data_fast);
    
    // Print Results Table
    printTableHeader();
    printResultRow("Bubble Sort", "O(N^2)", time_bubble, N_SLOW);
    printResultRow("Insertion Sort", "O(N^2)", time_insertion, N_SLOW);
    printResultRow("Selection Sort", "O(N^2)", time_selection, N_SLOW);
    printResultRow("Quick Sort", "O(N log N)", time_quick, N_FAST);
    printResultRow("Merge Sort", "O(N log N)", time_merge, N_FAST);
    printResultRow("Heap Sort", "O(N log N)", time_heap, N_FAST);
    cout << "--------------------------------------------------------" << endl;
    cout.flush();
}


int main() {
    cout << "--- Extended Sorting Algorithm Comparison ---" << endl;
    cout << "Time is reported in milliseconds (ms)." << endl;
    cout.flush();

    // 1. Random Data
    runAndPrintGeneral("Random", [](int size){ return generateRandomVector(size, K_MAX_GENERAL); });

    // 2. Nearly Sorted Data (Adaptive Test)
    runAndPrintGeneral("Nearly Sorted (Adaptive Test)", generateNearlySortedVector);

    // 3. Reverse Sorted Data (Worst Case Test) 
    cout << "\n--- Test Case: Reverse Sorted (Worst Case Test) Data ---" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "O(N^2) Algorithms (N=" << N_SLOW << ")" << endl;
    cout << "O(N log N) Algorithms (N=" << N_FAST << ")" << endl;
    
    // Data Generation for Reverse Sorted
    vector<int> data_reverse_slow = generateReverseSortedVector(N_SLOW);
    vector<int> data_reverse_fast = generateReverseSortedVector(N_FAST);

    // Run N^2 Sorts
    long long time_bubble_r = benchmarkSort(bubbleSort, data_reverse_slow);
    long long time_insertion_r = benchmarkSort(insertionSort, data_reverse_slow);
    long long time_selection_r = benchmarkSort(selectionSort, data_reverse_slow);

    // Run N log N Sorts
    long long time_quick_r = benchmarkSort(quickSort, data_reverse_fast);
    long long time_merge_r = benchmarkSort(mergeSort, data_reverse_fast);
    long long time_heap_r = benchmarkSort(heapSort, data_reverse_fast);


    // --- UNIFIED TABLE START ---
    printTableHeader();
    
    // Print Reverse Sorted Results
    printResultRow("Bubble Sort", "O(N^2)", time_bubble_r, N_SLOW);
    printResultRow("Insertion Sort", "O(N^2)", time_insertion_r, N_SLOW);
    printResultRow("Selection Sort", "O(N^2)", time_selection_r, N_SLOW);
    printResultRow("Quick Sort", "O(N log N)", time_quick_r, N_FAST);
    printResultRow("Merge Sort", "O(N log N)", time_merge_r, N_FAST);
    printResultRow("Heap Sort", "O(N log N)", time_heap_r, N_FAST);
    
    // --- CONTINUOUS LINEAR TIME RESULTS BLOCK ---
    
    // Print a separator and context, keeping the table flow clean
    cout << "--------------------------------------------------------" << endl;
    cout << "Specialized Linear Time Sorts (N=" << N_LINEAR << ", Max K=" << K_MAX << ")" << endl;
    
    // Generate data for O(N+K) sorts (Large N, Small K)
    vector<int> data_linear = generateRandomVector(N_LINEAR, K_MAX);

    // Run Linear Sorts
    long long time_counting = benchmarkSort(countingSort, data_linear);
    long long time_radix = benchmarkSort(radixSort, data_linear);
    long long time_bucket = benchmarkSort(bucketSort, data_linear);
    
    // Re-run an N log N algorithm for a direct comparison on the same N_LINEAR data
    vector<int> data_fast_comp = generateRandomVector(N_LINEAR, K_MAX);
    long long time_quick_comp = benchmarkSort(quickSort, data_fast_comp);
    
    // Print Linear Time Results
    cout << "--------------------------------------------------------" << endl;
    printResultRow("Quick Sort (Comp.)", "O(N log N)", time_quick_comp, N_LINEAR);
    printResultRow("Counting Sort", "O(N+K)", time_counting, N_LINEAR);
    printResultRow("Radix Sort", "O(d(N+b))", time_radix, N_LINEAR);
    printResultRow("Bucket Sort", "O(N+K)", time_bucket, N_LINEAR);

    cout << "--------------------------------------------------------" << endl;
    cout.flush(); 

    return 0;
}
