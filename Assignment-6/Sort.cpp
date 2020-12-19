#include "Assignment-6.h"
#include "time.h"
#include <iomanip>

using namespace std;

Sort::Sort() {}

Sort::~Sort() {
    // Since we allocated memory dynamically, we have to delete it.
    delete quickSortArr; 
    delete selectionSortArr;
    delete insertionSortArr;
    delete mergeSortArr;
    delete bubbleSortArr;
}

int Sort::GetArrSize() {
    return arrSize; // Returns the size of all arrays
}
void Sort::ReadFile() {
    fstream inputFile; // Creates fstream
    string filename; // Filename
    int index = 0;
    double data;
    int lineNumber = 0;
    cout << "Enter filename: "; // Get's the users filename
    cin >> filename;

    inputFile.open(filename, ios::in);
    if (inputFile.is_open()) {
        string line;
        while(getline(inputFile, line)) {
            if (lineNumber == 0) { // Get's the first line to get the size of the array.
                arrSize = stoi(line);
                // Creates new arrays
                quickSortArr = new double[arrSize];
                mergeSortArr = new double[arrSize];
                selectionSortArr = new double[arrSize];
                insertionSortArr = new double[arrSize];
                bubbleSortArr = new double[arrSize];

                // Adds to linenumber
                lineNumber++;
            }
            else { // If the line count is 1, then it creates the array 
                data = stod(line); // Initializes data as a double
                createArray(data, index); // Calls create array
                index++; // Adds to the index, starts at 0.
            }
        }
    }
}

void Sort::ToFile() { //===== FOR TESTING =====
    ofstream outfile; // Creates outfile
    outfile.open("out.txt");
    double data;
    for (int i = 0; i < arrSize; ++i) { // Prints just one of the sorted arrays for testing purposes.
        data = quickSortArr[i];
        outfile << data << endl;
    }
}

void Sort::createArray(double data, int index) {
    // Adds data to the current index.
    quickSortArr[index] = data; 
    mergeSortArr[index] = data;
    selectionSortArr[index] = data;
    insertionSortArr[index] = data;
    bubbleSortArr[index] = data;
}

void Sort::swap(double* a, double* b)  // Swaps two double pointers in the array.
{ 
    double t = *a; 
    *a = *b; 
    *b = t; 
}
//========================= QUICK SORT =======================
void Sort::QuickSort() {
    // Start timer
    clock_t start, end; 
    start = clock();

    int highIndex = sizeof(quickSortArr);
    // Call quicksort method
    recQuickSort(0, highIndex-1);

    // End timer
    end = clock(); 
    quickSortTime = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Quick Sort Time : " << fixed << quickSortTime << setprecision(6); 
    cout << " sec " << endl; 

}
void Sort::recQuickSort(int low, int high)
{
    int pivotIndex; // Creates the pivot index

    if (low < high) // If it is low
    {
        pivotIndex = partition(low, high); // Finds the partition

        recQuickSort(low, pivotIndex - 1); // Uses recursion to quicksort.
        recQuickSort(pivotIndex + 1, high);
    }
}

int Sort::partition (int low, int high) 
{ 
    int pivot = quickSortArr[high];
    int i = (low - 1); 
  
    for (int j = low; j <= high - 1; j++) 
    {  
        if (quickSortArr[j] <= pivot) 
        { 
            i++;
            swap(&quickSortArr[i], &quickSortArr[j]); 
        } 
    } 
    swap(&quickSortArr[i + 1], &quickSortArr[high]); 
    return (i + 1); 
} 

// ------------------------------- MERGE SORT -------------------------------
void Sort::Merge(int i, int j, int k) {
   int mergedSize = k - i + 1;               // Size of merged partition
   int mergePos = 0;                          // Position to insert merged number
   int leftPos = 0;                           // Position of elements in left partition
   int rightPos = 0;                          // Position of elements in right partition
   double *mergedNumbers = new double[mergedSize];   // Dynamically allocates temporary array
   // for merged numbers
   
   leftPos = i;                           // Initialize left partition position
   rightPos = j + 1;                      // Initialize right partition position
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if (mergeSortArr[leftPos] <= mergeSortArr[rightPos]) {
         mergedNumbers[mergePos] = mergeSortArr[leftPos];
         ++leftPos;
      }
      else {
         mergedNumbers[mergePos] = mergeSortArr[rightPos];
         ++rightPos;
         
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = mergeSortArr[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = mergeSortArr[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      mergeSortArr[i + mergePos] = mergedNumbers[mergePos];
   }
}

void Sort::recMergeSort(int i, int k) {
   int midpoint = 0;
   
   if (i < k) {
      midpoint = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      recMergeSort(i, midpoint);
      recMergeSort(midpoint + 1, k);
      
      // Merge left and right partition in sorted order
      Merge(i, midpoint, k);
   }
}

void Sort::MergeSort() {
    // Start timer
    clock_t start, end; 
    start = clock();

    int size = sizeof(mergeSortArr);
    recMergeSort(0, size - 1);

    // End timer
    end = clock(); 
    mergeSortTime = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Merge Sort Time : " << fixed << mergeSortTime << setprecision(6); 
    cout << " sec " << endl; 
}

// ------------------------------- INSERTION SORT -------------------------------

void Sort::recInsertionSort(int numbersSize) {
   int i = 0;
   int j = 0;
   double temp = 0;  // Temporary variable for swap
   
   for (i = 1; i < numbersSize; ++i) {
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
      while (j > 0 && insertionSortArr[j] < insertionSortArr[j - 1]) {
         
         // Swap numbers[j] and numbers[j - 1]
         temp = insertionSortArr[j];
         insertionSortArr[j] = insertionSortArr[j - 1];
         insertionSortArr[j - 1] = temp;
         --j;
      }
   }
}

void Sort::InsertionSort() {
    // Start timer
    clock_t start, end; 
    start = clock();
   int size = sizeof(insertionSortArr);
  
   recInsertionSort(size);

   // End timer
    end = clock(); 
    insertionSortTime = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Insertion Sort Time : " << fixed << insertionSortTime << setprecision(6); 
    cout << " sec " << endl; 
}

// ------------------------------- SELECTION SORT -------------------------------

void Sort::recSelectionSort(int numbersSize) {
   int i = 0;
   int j = 0;
   int indexSmallest = 0;
   double temp = 0; // Temporary variable for swap
   
   for (i = 0; i < numbersSize - 1; ++i) {
      
      // Find index of smallest remaining element
      indexSmallest = i;
      for (j = i + 1; j < numbersSize; ++j) {
         
         if (selectionSortArr[j] < selectionSortArr[indexSmallest] ) {
            indexSmallest = j;
         }
      }
      
      // Swap numbers[i] and numbers[indexSmallest]
      temp = selectionSortArr[i];
      selectionSortArr[i] = selectionSortArr[indexSmallest];
      selectionSortArr[indexSmallest] = temp;
   }
}

void Sort::SelectionSort() {
   int size = sizeof(selectionSortArr);
   // Start timer
    clock_t start, end; 
    start = clock();
   
   recSelectionSort(size);

   // End timer
    end = clock(); 
    selectionSortTime = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Selection Sort Time : " << fixed << selectionSortTime << setprecision(6); 
    cout << " sec " << endl; 
}

// ------------------------------- BUBBLE SORT -------------------------------
void Sort::recBubbleSort(int size) 
{ 
    int n = size; 
    for (int i = 0; i < n - 1; i++) 
        for (int j = 0; j < n - i - 1; j++) 
            if (bubbleSortArr[j] > bubbleSortArr[j + 1]) 
            { 
                // swap temp and arr[i] 
                int temp = bubbleSortArr[j]; 
                bubbleSortArr[j] = bubbleSortArr[j + 1]; 
                bubbleSortArr[j + 1] = temp; 
            } 
} 

void Sort::BubbleSort() 
{  
    int size = sizeof(bubbleSortArr);
    // Start timer
    clock_t start, end; 
    start = clock();
    
    recBubbleSort(size);

    // End timer
    end = clock(); 
    bubbleSortTime = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Bubble Sort Time : " << fixed << bubbleSortTime << setprecision(6); 
    cout << " sec " << endl; 
} 