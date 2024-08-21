#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

// Windows-specific sleep function
#ifdef _WIN32
#include <windows.h>
void sleep_for_ms(int milliseconds) {
    Sleep(milliseconds);
}
// POSIX-compliant sleep function (Linux, macOS)
#else
#include <unistd.h>
void sleep_for_ms(int milliseconds) {
    usleep(milliseconds * 1000); // usleep takes microseconds
}
#endif

using namespace std;

const int arrSize = 6; // Reduced array size
int arr[arrSize];
int Barr[arrSize]; // Backup array for resetting

// ANSI color codes
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";

// Function to print the array as a bar graph
void printArray(int highlight1 = -1, int highlight2 = -1, bool forcePrint = false) {
    static int previousHighlight1 = -1, previousHighlight2 = -1;

    if (!forcePrint && highlight1 == previousHighlight1 && highlight2 == previousHighlight2) {
        return; // Skip printing if highlights haven't changed
    }

    previousHighlight1 = highlight1;
    previousHighlight2 = highlight2;

    for (int i = 0; i < arrSize; ++i) {
        if (i == highlight1 || i == highlight2) {
            cout << RED << "|"; // Highlighted elements
        } else {
            cout << " ";
        }
        for (int j = 0; j < arr[i]; ++j) {
            if (i == highlight1 || i == highlight2) {
                cout << YELLOW << "#"; // Use color to highlight
            } else {
                cout << GREEN << "#";
            }
        }
        cout << RESET << endl; // Reset color after each row
    }
    cout << CYAN << "----------------------" << RESET << endl; // To separate steps visually
}

// Bubble Sort with visualization
void bubbleSort() {
    cout << BLUE << "Bubble Sort: Swapping adjacent elements if they are in the wrong order.\n" << RESET;
    for (int i = 0; i < arrSize - 1; ++i) {
        for (int j = 0; j < arrSize - i - 1; ++j) {
            printArray(j, j + 1);
            sleep_for_ms(500); // Delay for better visualization
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                printArray(j, j + 1, true); // Force print after a swap
                cout << MAGENTA << "Swapped elements at positions " << j << " and " << j + 1 << "\n" << RESET;
            }
        }
    }
}

// Insertion Sort with visualization
void insertionSort() {
    cout << BLUE << "Insertion Sort: Insert elements into their correct position in the sorted portion.\n" << RESET;
    for (int i = 1; i < arrSize; i++) {
        int j = i - 1;
        int temp = arr[i];
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
            printArray(i, j + 1, true); // Force print after moving an element
            sleep_for_ms(500);
        }
        arr[j + 1] = temp;
        cout << MAGENTA << "Inserted element " << temp << " at position " << j + 1 << "\n" << RESET;
    }
}

// Selection Sort with visualization
void selectionSort() {
    cout << BLUE << "Selection Sort: Selecting the minimum element from the unsorted portion and swapping it.\n" << RESET;
    int minIndex;
    for (int i = 0; i < arrSize - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < arrSize; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
            printArray(i, minIndex);
            sleep_for_ms(500);
        }
        swap(arr[i], arr[minIndex]);
        printArray(i, minIndex, true); // Force print after a swap
        cout << MAGENTA << "Swapped element at position " << i << " with minimum element at position " << minIndex << "\n" << RESET;
    }
}

// Merge Sort helper function to merge two sorted halves
void merge(int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int* left = new int[n1];
    int* right = new int[n2];

    for (int i = 0; i < n1; i++) {
        left[i] = arr[low + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        printArray(k);
        sleep_for_ms(500);
        k++;
    }

    while (i < n1) {
        arr[k] = left[i];
        printArray(k);
        sleep_for_ms(500);
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        printArray(k);
        sleep_for_ms(500);
        j++;
        k++;
    }

    delete[] left;
    delete[] right;
}

// Merge Sort with visualization
void mergeSort(int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        mergeSort(low, mid);
        mergeSort(mid + 1, high);

        merge(low, mid, high);
    }
}

// Quick Sort helper function to partition the array
int partition(int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            printArray(i, j, true);
            sleep_for_ms(500);
        }
    }
    swap(arr[i + 1], arr[high]);
    printArray(i + 1, high, true);
    sleep_for_ms(500);
    return i + 1;
}

// Quick Sort with visualization
void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);

        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

// Heapify function for Heap Sort
void heapify(int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        printArray(i, largest, true);
        sleep_for_ms(500);
        heapify(n, largest);
    }
}

// Heap Sort with visualization
void heapSort() {
    for (int i = arrSize / 2 - 1; i >= 0; i--) {
        heapify(arrSize, i);
    }

    for (int i = arrSize - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        printArray(0, i, true);
        sleep_for_ms(500);
        heapify(i, 0);
    }
}

// Function to randomize the array
void randomizeAndSaveArray() {
    srand((unsigned)time(NULL));
    for (int i = 0; i < arrSize; i++) {
        Barr[i] = rand() % 10 + 1; // Smaller range for better visualization
    }
}

// Function to reset the array to its original randomized state
void loadArr() {
    memcpy(arr, Barr, sizeof(int) * arrSize);
}

int main() {
    cout << "Welcome to the Sorting Visualizer!" << endl;
    cout << "Legend: " << RED << "|" << RESET << " - Comparing elements, " << YELLOW << "#" << RESET << " - Swapping elements" << endl;
    randomizeAndSaveArray();
    loadArr();

    int choice;
    while (true) {
        cout << "\nChoose a sorting algorithm:\n"
             << "0 - Generate New Random Array\n"
             << "1 - Selection Sort\n"
             << "2 - Insertion Sort\n"
             << "3 - Bubble Sort\n"
             << "4 - Merge Sort\n"
             << "5 - Quick Sort\n"
             << "6 - Heap Sort\n"
             << "7 - Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 0:
                randomizeAndSaveArray();
                cout << "\nNew random array generated:\n";
                loadArr();
                printArray();
                break;
            case 1:
                loadArr();
                cout << "\nSelection Sort started:\n";
                selectionSort();
                cout << "\nSelection Sort complete.\n";
                break;
            case 2:
                loadArr();
                cout << "\nInsertion Sort started:\n";
                insertionSort();
                cout << "\nInsertion Sort complete.\n";
                break;
            case 3:
                loadArr();
                cout << "\nBubble Sort started:\n";
                bubbleSort();
                cout << "\nBubble Sort complete.\n";
                break;
            case 4:
                loadArr();
                cout << "\nMerge Sort started:\n";
                mergeSort(0, arrSize - 1);
                cout << "\nMerge Sort complete.\n";
                break;
            case 5:
                loadArr();
                cout << "\nQuick Sort started:\n";
                quickSort(0, arrSize - 1);
                cout << "\nQuick Sort complete.\n";
                break;
            case 6:
                loadArr();
                cout << "\nHeap Sort started:\n";
                heapSort();
                cout << "\nHeap Sort complete.\n";
                break;
            case 7:
                cout << "\nExiting...\n";
                return 0;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
