//Project: Merge Sort with Threads
//Date: 25/08/2021
#include <iostream>
#include <ctime>
#include <thread>
#include <vector>

using namespace std;

int cant_th = thread::hardware_concurrency(), i_thread = 0;   //Make global the number of threads and its vector
vector<thread> th(cant_th);

void merge(unsigned long arr[], unsigned long l, unsigned long m, unsigned long r)
{
    unsigned long n1 = m - l + 1;
    unsigned long n2 = r - m;

    // Create temp arrays
    unsigned long* L = new unsigned long[n1];
    unsigned long* R = new unsigned long[n2];

    // Copy data to temp arrays L[] and R[]
    for (unsigned long i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (unsigned long j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]

    // Initial index of first subarray
    unsigned long i = 0;

    // Initial index of second subarray
    unsigned long j = 0;

    // Initial index of merged subarray
    unsigned long k = l;

    while (i < n1 && j < n2) {
        if (L[i] < R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete L;
    delete R;
}

void mergeSort(unsigned long arr[], unsigned long l, unsigned long r) {
    if (l >= r) {
        return;
    }
    unsigned long m = l + (r - l) / 2;
    mergeSort(arr, l, m);        //We pass the class
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

void thread_parts(unsigned long arr[], unsigned long l, unsigned long r, int cuts) {
    if (l >= r || cuts == 1) {                   //We make cuts until the array is divided in the same quantity of the cores and those blocks will be sorted and it will be more effective when the arrays are bigger.
        th[i_thread] = thread(mergeSort, arr, l, r); i_thread++;    //We send the block in merge sort
        return;             //We lean in recursion to make effective the division
    }
    unsigned long m = l + (r - l) / 2;
    cuts = cuts / 2;
    thread_parts(arr, l, m, cuts);
    thread_parts(arr, m + 1, r, cuts);
}

void thread_end(unsigned long arr[], unsigned long l, unsigned long r, int cuts) { //This function helps to join the sorted blocks
    if (l >= r || cuts == 1) {        
        return;
    }
    unsigned long m = l + (r - l) / 2;
    cuts = cuts / 2;
    thread_end(arr, l, m, cuts);
    thread_end(arr, m + 1, r, cuts);
    merge(arr, l, m, r);
}

void mergeParalelo(unsigned long arr[], unsigned long cant_elem) {
    if (cant_elem <= cant_th) { cant_th = cant_elem; thread_end(arr, 0, cant_elem - 1, cant_th); return; } //If the amount of data is the same as the number of cores, it is not required to call the function.
    thread_parts(arr, 0, cant_elem - 1, cant_th);
    for (unsigned long i = 0; i < cant_th; i++) {
        th[i].join();
    }
    thread_end(arr, 0, cant_elem - 1, cant_th);
}

void printArray(unsigned long A[], int size)        //We print the array
{
    for (unsigned long i = 0; i < 10; i++) { cout << A[i] << " "; }
    cout << "...";
    for (unsigned long i = size - 10; i < size; i++) { cout << A[i] << " "; }
}

int main()
{
    srand(time(0));
    unsigned long cantidad_datos = 500000;

    unsigned long* arr = new unsigned long[cantidad_datos];
    for (unsigned long i = 0; i < cantidad_datos; i++) {
        arr[i] = 1 + (rand() % 1000000);
    }

    arr[40000] = 500000;          //It seems that random generation helps until 32 767 that's why so many elements are repeated
    arr[45000] = 0;               //to verify it works we send unsorted numbers.
    arr[100] = 500001;

    cout << "Given array is \n";
    printArray(arr, cantidad_datos);

    clock_t t;

    t = clock();
    mergeParalelo(arr, cantidad_datos);     //We call the function
    t = clock() - t;

    cout << "\nSorted array is \n";
    printArray(arr, cantidad_datos);

    cout << "\nEjecution Time: " << double(t) / CLOCKS_PER_SEC;
    delete[] arr;
    return 0;
}