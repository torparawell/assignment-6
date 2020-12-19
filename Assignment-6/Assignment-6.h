#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

class Sort {
    public:
        // Constructors
        Sort();
        ~Sort(); // delete arr in here

        // Quick Sorting methods
        void QuickSort();
        void recQuickSort(int low, int high);
        int GetArrSize();
        // In aid to sorting
        void swap(double* a, double* b);
        int partition (int low, int high);

        // Merge Sorting Methods
        void Merge(int i, int j, int k);
        void recMergeSort(int i, int k);
        void MergeSort();

        // Selection sort methods 
        void SelectionSort();
        void recSelectionSort(int size);

        // Insertion sort
        void InsertionSort();
        void recInsertionSort(int numbersSize);

        // Bubble sort
        void BubbleSort();
        void recBubbleSort(int size);
        
        // Other methods
        void ReadFile();
        void ToFile();
    private:
        int arrSize; // Gets the size of the array
        void createArray(double data, int index); // For creating the array
        
        //To store time
        double quickSortTime;
        double mergeSortTime;
        double selectionSortTime;
        double insertionSortTime;
        double bubbleSortTime;

        //Arrays
        double *quickSortArr;
        double *mergeSortArr;
        double *selectionSortArr;
        double *insertionSortArr;
        double *bubbleSortArr;
};