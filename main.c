#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// function to find the partition position
int partitionForQuickSort(int array[], int low, int high) {

    // select the rightmost element as pivot
    int pivot = array[high];

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {

            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j
            swap(&array[i], &array[j]);
        }
    }

    // swap the pivot element with the greater element at i
    swap(&array[i + 1], &array[high]);

    // return the partition point
    return (i + 1);
}

int quickSortAlgorithm(int array[], int low, int high, int k) {
    if (low < high) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi = partitionForQuickSort(array, low, high);

        // recursive call on the left of pivot
        quickSortAlgorithm(array, low, pi - 1, k);

        // recursive call on the right of pivot
        quickSortAlgorithm(array, pi + 1, high, k);
    }
    return array[k-1];
}
//insertion sort
int insertionSortAlgorithm(int arr[], int n,int k)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    return arr[k-1];
}
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
int mergeSortAlgorithm(int arr[], int l, int r, int k)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSortAlgorithm(arr, l, m, k);
        mergeSortAlgorithm(arr, m + 1, r, k);

        merge(arr, l, m, r);
    }

    return arr[k-1];
}
// A utility function to print an array of size n
int selectionSort(int array[], int kthElement,int size) {

        for (int step = 0; step < kthElement ; step++) {
            int min_idx = step;
            for (int i = step + 1; i < size; i++) {
                // Select the minimum element in each loop.
                if (array[i] < array[min_idx]) {
                    min_idx = i;

                }
                //if(kthElement <= 0)break;


            }

            // put min at the correct position
            swap(&array[min_idx], &array[step]);
        }

     return array[kthElement-1];

}

void heapify(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int leftChild = 2 * i + 1; // left child = 2*i + 1
    int rightChild = 2 * i + 2; // right child = 2*i + 2

// If left child is greater than root

    if (leftChild < n && arr[leftChild] > arr[largest])
        largest = leftChild;

// If right child is greater than new largest

    if (rightChild < n && arr[rightChild] > arr[largest])
        largest = rightChild;

// If largest is not the root

    if (largest != i)
    {
// swap root with the new largest

        swap(&arr[i], &arr[largest]);

// Recursively heapify the affected sub-tree i.e, subtree with root as largest
        heapify(arr, n, largest);
    }
}
void deleteRoot(int arr[], int n)
{
// Get the last element
int lastElement = arr[n - 1];

// Replace root with last element
arr[0] = lastElement;

// Decrease size of heap by 1
n = n - 1;

// heapify the root node
heapify(arr, n, 0);
}

// Function to build a Max-Heap from a given array

void buildHeap(int arr[], int n)
{
// Index of last non-leaf node
    int lastNonLeafNode = (n / 2) - 1;

// Perform level order traversal in reverse from last non-leaf node to the root node and heapify each node
    for (int i = lastNonLeafNode; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
}

int partialHeapSortAlgorithm(int arr[], int n, int kthelement){
    int smallest = n-kthelement;
    buildHeap(arr,n);
    for (int i = 0; i< smallest;i++){
        deleteRoot(arr,n);
        n--;
        buildHeap(arr,n);

    }
    return arr[0];
}

// quick select with the first element as pivot
int partition(int a[], int left, int right, int pIndex)
{
   int pivot = a[pIndex];

   for (int i = left + 1; i <= right; i++)
   {
      if (a[i] <= pivot)
      {
         pIndex++;
         swap((a+i), (a+pIndex));
      }
    }

    swap((a+pIndex), (a+left));

    return pIndex;
}

int quickSelectAlgorithm(int nums[], int left, int right, int k)
{
    if (left == right) {
        return nums[left];
    }

    int pIndex = left;

     pIndex = partition(nums, left, right, pIndex);

    if (k == pIndex) {
       return nums[k];
    }

    else if (k < pIndex) {
        return quickSelectAlgorithm(nums, left, pIndex - 1, k);
    }

    else {
        return quickSelectAlgorithm(nums, pIndex + 1, right, k);
    }
}


int *medianOfThree(int *nums, int left, int right){
      int mid = (left + right) / 2;
      if (nums[left] > nums[mid])
         swap(&nums[left], &nums[mid]);
      if (nums[left] > nums[right])
         swap(&nums[left], &nums[right]);
      if (nums[mid] > nums[right])
         swap(&nums[mid], &nums[right]);
      swap(&nums[mid], &nums[right - 1]);
      return &nums[right - 1];
}

// quick select with median of three

int partitionMedianOfThree(int *nums, int left, int right){
        int *pivot = medianOfThree(nums, left, right);
        int pivotValue = *pivot;
        int i = left;
        int j = right - 1;
        while (1) {
            while (nums[++i] < pivotValue) {}
            while (nums[--j] > pivotValue) {}
            if (i < j)
                swap(&nums[i], &nums[j]);
            else
                break;
        }
        swap(&nums[i], &nums[right - 1]);
        return i;
}




int quickSelectMedianOfThreeAlgorithm(int nums[], int left, int right, int k)
{

    if (left == right) {
        return nums[left];
    }



    int pIndex = partitionMedianOfThree(nums, left, right);

    if (k == pIndex) {
       return nums[k];
    }

    else if (k < pIndex) {
        return quickSelectMedianOfThreeAlgorithm(nums, left, pIndex - 1, k);
    }

    else {
        return quickSelectMedianOfThreeAlgorithm(nums, pIndex + 1, right, k);
    }
}


int partialSelectionSortAlgorithm(int nums[], int n, int k) {
    for (int i = 0; i< k; i++) {
        int minIndex = i;
        int minValue = nums[i];
        for (int j = i + 1; j < n; j++)
        {
            if (nums[j] < minValue) {
                minIndex = j;
                minValue = nums[j];
                swap(&nums[minIndex], &nums[i]);
            }
        }

    }

    return nums[k-1];
}


void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


void copyArray (int *arrFrom, int *arrTo, int size){
    for (int i = 0; i < size; i++){
        arrTo[i] = arrFrom[i];
    }
}


typedef enum {
    INSERTION,
    MERGE,
    QUICK_SORT,
    PARTIAL_SELECTION_SORT,
    PARTIAL_HEAP_SORT,
    QUICK_SELECT,
    QUICK_SELECT_MEDIAN_OF_THREE,
}Algorithms_t;

typedef enum
{
    SORTED,
    REVERSED,
    DUPLICATES,
    RANDOM,
    SAME,
} Order_t;

typedef struct {
    Order_t order;
    char name[255];
} Order_s;

void buildArr(Order_t order, int *arr, int size){

    if (order == SORTED){
        for (int i = 0; i < size; i++){
            arr[i] = i+1;
        }
    }
    else if (order == REVERSED){
        for (int i = 0; i < size; i++){
            arr[i] = size - i;
        }
    }
    else if (order == DUPLICATES){
        for(int i = 0; i < size; i++){
        arr[i] = i+1;
    }
        // random number between %25 and %75 of the size

    int randomNumber = rand() % (size / 4) + size / 8;

    for(int i = 0; i < randomNumber; i++){
        int randomIndex = rand() % size;
        arr[i] = arr[randomIndex];
        }
    }
    else if (order == RANDOM){
        for(int i = 0; i < size; i++){
        arr[i] = i+1;
    }
        for(int i = 0; i < size; i++){
        int randomIndex = rand() % size;
        swap(&arr[i], &arr[randomIndex]);
    }
    }
    else if (order == SAME){
        for (int i = 0; i < size; i++){
            arr[i] = 5;
        }
    }


}

void executionTime(int size, int kthElement){
    double time_spent = 0.0;

    clock_t begin;
    clock_t end;

    Order_s *orders = malloc(sizeof(Order_s) * 5);

    orders[0].order = SORTED;
    orders[1].order = REVERSED;
    orders[2].order = DUPLICATES;
    orders[3].order = RANDOM;
    orders[4].order = SAME;

    strcpy(orders[0].name, "Ascending Order\0");
    strcpy(orders[1].name, "Descending Order\0");
    strcpy(orders[2].name, "Duplicates Order\0");
    strcpy(orders[3].name, "Random Order\0");
    strcpy(orders[4].name, "Same Order\0");


    printf("\n nk = %d size = %d\n\n", kthElement, size);


    for (int i = 0; i<5; i++)
    {
        int *temp = malloc(sizeof(int) * size);
        buildArr(orders[i].order, temp, size);

        printf("%s\n", orders[i].name);
            int *num1 = malloc(sizeof(int)*size);
            copyArray(temp, num1, size);

            begin = clock();
            time_spent = 0.0;
            int n = insertionSortAlgorithm(num1, size, kthElement);
            end = clock();
            time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
            printf("%f\n", time_spent);



            int *num2 = malloc(sizeof(int)*size);
            time_spent = 0.0;
            copyArray(temp, num2, size);
            begin = clock();
            int n2 =  mergeSortAlgorithm(num2, 0,  size-1, kthElement);
            end = clock();
            time_spent += (double)(end - begin)/ CLOCKS_PER_SEC;
            printf("%f\n", time_spent);

            int *num3 = malloc(sizeof(int)*size);
            time_spent = 0.0;
            copyArray(temp, num3, size);
            begin = clock();
            int n3 = quickSortAlgorithm(num3, 0,  size-1, kthElement);
            end = clock();
            time_spent += (double)(end - begin)/ CLOCKS_PER_SEC;
            printf("%f\n", time_spent);

            int *num4 = malloc(sizeof(int)*size);
            time_spent = 0.0;
            copyArray(temp, num4, size);
            begin = clock();
            int n4 = partialSelectionSortAlgorithm(num4, size, kthElement);
            end = clock();
            time_spent += (double)(end - begin)/ CLOCKS_PER_SEC;
            printf("%f\n", time_spent);


            int *num5 = malloc(sizeof(int)*size);
            time_spent = 0.0;
            copyArray(temp, num5, size);
            begin = clock();
             int n5 = partialHeapSortAlgorithm(num5, size, kthElement);
            end = clock();
            time_spent += (double)(end - begin)/ CLOCKS_PER_SEC;
            printf("%f\n", time_spent);

            int *num6 = malloc(sizeof(int)*size);
            time_spent = 0.0;
            copyArray(temp, num6, size);
            begin = clock();
            int n6 = quickSelectAlgorithm(num6,0 ,  size-1, kthElement-1);
            end = clock();
            time_spent += (double)(end - begin)/ CLOCKS_PER_SEC;
             printf("%f\n", time_spent);

            int *num7 = malloc(sizeof(int)*size);
            time_spent = 0.0;
            copyArray(temp, num7, size);
            begin = clock();
            int n7 =  quickSelectMedianOfThreeAlgorithm(num7,0 ,  size-1, kthElement-1);
            end = clock();
            time_spent += (double)(end - begin)/ CLOCKS_PER_SEC;
             printf("%f\n", time_spent);



        free(temp);
        free(num1);
        free(num2);
        free(num3);
        free(num4);
        free(num5);
        free(num6);
        free(num7);
    }

}


int main()
{

    /*
        Mehmet Fatih Erdem – 150119054
        Talha Sezer - 150119022

    */



    executionTime(100, 3);

    executionTime(100, 10);
    executionTime(100, 90);

    executionTime(500, 50);
    executionTime(500, 450);

    executionTime(5000, 500);
    executionTime(5000, 4500);

    executionTime(10000, 1000);
    executionTime(10000, 9000);

    executionTime(100000, 10000);
    executionTime(100000, 90000);




    return 0;

}
