#include "assignment-6.h"
using namespace std;

int main(int argc, char** argv){
    Sort *sort = new Sort();
    sort->ReadFile();
    //sort->PrintArray();

    // Preparation for quick sort.
    int arrSize = sort->GetArrSize();
    sort->QuickSort();
    sort->MergeSort();
    sort->InsertionSort();
    sort->SelectionSort();
    sort->BubbleSort();

    // Preparation for other sort type;
    delete sort;
}