#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int bubble_sort_count(int array[], int n) {
    int comparisonCount = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisonCount++;
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
    return comparisonCount;
}

int selection_sort_count(int array[], int n) {
    int comparisonCount = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisonCount++;
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        swap(array[i], array[minIndex]);
    }
    return comparisonCount;
}

int insertion_sort_count(int array[], int n) {
    int comparisonCount = 0;
    for (int i = 1; i < n; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            comparisonCount++;
            array[j + 1] = array[j];
            j--;
        }
        comparisonCount++;
        array[j + 1] = key;
    }
    return comparisonCount;
}

int heapify(int arr[], int size, int index) {
    int smallest = index;
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;
    int comparisons = 0;

    if (left < size && arr[left] < arr[smallest]) {
        comparisons++;
        smallest = left;
    }

    if (right < size && arr[right] < arr[smallest]) {
        comparisons++;
        smallest = right;
    }

    if (smallest != index) {
        swap(arr[index], arr[smallest]);
        comparisons += heapify(arr, size, smallest);
    }

    return comparisons;
}

int heap_sort_count(int array[], int n) {
    int comparisonCount = 0;

    for (int i = (n / 2) - 1; i >= 0; i--) {
        comparisonCount += heapify(array, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(array[0], array[i]);
        comparisonCount += heapify(array, i, 0);
    }

    return comparisonCount;
}

void generate_array(int array[], int n, int type) {
    for (int i = 0; i < n; i++) {
        if (type == 0) {
            array[i] = rand() % 100;
        }
        else if (type == 1) {
            array[i] = i;
        }
        else {
            array[i] = n - i;
        }
    }
}

void test_comparisons() {
    srand(time(0));

    ofstream results("sorting_results.csv");
    results << "Size,Type,Algorithm,Comparisons,Time (\u00b5s)\n";

    int array[30];

    cout << left << setw(10) << "Size" << setw(15) << "Type" << setw(20) << "Algorithm"
        << setw(15) << "Comparisons" << "Time (\u00b5s)" << endl;
    cout << string(70, '-') << endl;

    for (int n = 1; n <= 30; n++) {
        for (int type = 0; type < 3; type++) {
            generate_array(array, n, type);

            string type_str = (type == 0) ? "Random" : (type == 1) ? "Sorted" : "Reverse Sorted";

            int temp[30];
            copy(array, array + n, temp);

            auto startTime = high_resolution_clock::now();
            int heap_comp = heap_sort_count(temp, n);
            auto endTime = high_resolution_clock::now();
            auto heap_time = duration_cast<microseconds>(endTime - startTime).count();

            cout << setw(10) << n << setw(15) << type_str << setw(20) << "Heap Sort"
                << setw(15) << heap_comp << heap_time << endl;
            results << n << "," << type_str << "," << "Heap Sort," << heap_comp << "," << heap_time << "\n";

            copy(array, array + n, temp);
            startTime = high_resolution_clock::now();
            int bubble_comp = bubble_sort_count(temp, n);
            endTime = high_resolution_clock::now();
            auto bubble_time = duration_cast<microseconds>(endTime - startTime).count();

            cout << setw(10) << n << setw(15) << type_str << setw(20) << "Bubble Sort"
                << setw(15) << bubble_comp << bubble_time << endl;
            results << n << "," << type_str << "," << "Bubble Sort," << bubble_comp << "," << bubble_time << "\n";

            copy(array, array + n, temp);
            startTime = high_resolution_clock::now();
            int selection_comp = selection_sort_count(temp, n);
            endTime = high_resolution_clock::now();
            auto selection_time = duration_cast<microseconds>(endTime - startTime).count();

            cout << setw(10) << n << setw(15) << type_str << setw(20) << "Selection Sort"
                << setw(15) << selection_comp << selection_time << endl;
            results << n << "," << type_str << "," << "Selection Sort," << selection_comp << "," << selection_time << "\n";

            copy(array, array + n, temp);
            startTime = high_resolution_clock::now();
            int insertion_comp = insertion_sort_count(temp, n);
            endTime = high_resolution_clock::now();
            auto insertion_time = duration_cast<microseconds>(endTime - startTime).count();

            cout << setw(10) << n << setw(15) << type_str << setw(20) << "Insertion Sort"
                << setw(15) << insertion_comp << insertion_time << endl;
            results << n << "," << type_str << "," << "Insertion Sort," << insertion_comp << "," << insertion_time << "\n";
        }
    }
    results.close();
    cout << "Results saved to sorting_results.csv" << endl;
}

int main() {
    test_comparisons();
}
