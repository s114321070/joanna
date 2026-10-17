#include <iostream>
#include <string>
#include <fstream>
#ifndef N
#define N       2000
#endif

using std::ifstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;

// Function Prototypes
void selectionSort(int data[], int size);
void insertionSort(int data[], int size);
void bubbleSort(int data[], int size);
void countingSort(int data[], int size);
void straightradixSort(int data[], int size);
void radixexchangeSort(int data[], int size,int left, int right, int bit);
void quick_sort(int data[], int size);

struct sortingAlgorithm {
    string title;
    void (*algorithm)(int data[], int size);    // pointer to function
};

struct sortingAlgorithm SortingAlgorithm[] = {
    { "Selection Sort", selectionSort },
    { "Insertion Sort", insertionSort },
    { "Bubble Sort", bubbleSort },
    { "Counting Sort", countingSort },
    {"Straight Radix Sort", straightradixSort},
    {"Radix Exchange Sort", [](int data[], int size) {
    radixexchangeSort(data, size, 0, -1, -1);}},
    {"Quick Sort", quick_sort}
};

int menu() {
    int n;
    cout << endl;
    // Automatically count how many algorithms are there in the array.
    for (size_t i=0; i<sizeof(SortingAlgorithm)/sizeof(SortingAlgorithm[0]); ++i)
        cout << i+1 << ". " << SortingAlgorithm[i].title << endl;
    cout << "0. Exit" << endl;
    cout << "Choose a sorting algorithm: ";
    cin >> n;
    return n;
}

void initArray(int data[], int n, string filename="integer.txt") {
    ifstream f(filename);
    if (f.good()) { // File exists.
        for (int i=0; i<n; ++i)
            f >> data[i];
    } else {
        f.close();
        std::ofstream outfile(filename);
        for (int i=0; i<n; ++i) {
            data[i] = n - i;
            outfile << data[i] << endl;
        }
        outfile.close();
    }
}

void copyArray(int dst[], int src[], int n) {
    for (int i=0; i<n; ++i)
        dst[i] = src[i];
}

void showArray(int a[], int n) {
    for (int i=0; i<n; ++i)
        cout << a[i] << (i==n-1?'\n':' ');
}

#include "gettimeofday.h"
void measure(void (*algorithm)(int data[], int size), int src[], int n, int iteration=1) {
    time_t sec, usec;
    struct timeval t0, t1;
    int* A = new int[n];
    copyArray(A, src, n);
    //showArray(A, n);        // Before sorting
    gettimeofday(&t0, nullptr);
    for (int i=0; i<iteration; ++i) {
        copyArray(A, src, n);
        algorithm(A, n);
    }
    gettimeofday(&t1, nullptr);
    //showArray(A, n);        // After sorting
    usec = (t1.tv_sec * 1000000 + t1.tv_usec) - 
           (t0.tv_sec * 1000000 + t0.tv_usec);
    sec = usec / 1000000;
    usec %= 1000000;
    printf("%ld.%06ld seconds\n", sec, usec);
}

int main(int argc, char* argv[])
{
    
    int nChoice;
    // int A[N];
    int B[N];
    string FILENAME;
    if (argc == 2)
        FILENAME = argv[1];
    else
        FILENAME = "integer.txt";
    initArray(B, N, FILENAME);
    while (true) {
        nChoice = menu();
        if (nChoice == 0) break;
        
        //copyarray(a, b, n);
        //showarray(a, n);        // before sorting
        //sortingalgorithm[nchoice-1].algorithm(a, n);
        //showarray(a, n);        // after sorting
        
        measure(SortingAlgorithm[nChoice-1].algorithm, B, N, 2000);
    }
    return 0;
}

//void selectionSort(int data[], int size) {}
//void insertionSort(int data[], int size) {}
//void bubbleSort(int data[], int size) {}
//void countingSort(int data[], int size) {}
