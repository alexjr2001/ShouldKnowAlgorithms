//Project: SegmentTreeSuma
//Date: 05/2023
//A code where a segment Tree of sums is implemented. It is used to know the total of a sum of a range of numbers in
//an array

#include <iostream>
#include <cmath>

using namespace std;

void build(int arr[], int tam) {          //We build the "tree" it is going to be an array
    int index = 0;
    for (int i = tam * 2 - 1; i > 1; i -= 2) {      //The size is 2*numberOfElement - 1 to represent the tree
        index = floor(i / 2) - 1;
        arr[index] = arr[i - 1] + arr[i - 2];
    }
    return;
}

void update(int arr[], int i, int v, int tam) {     //In case we update an value
    i = i + tam - 1;                    //The actual index,it goes to the leaves
    int diferencia = v-arr[i];          //Store what is the difference with the previous value
    arr[i]+=diferencia;
    while (i>0) {
        i = floor(i / 2);               //We update the values walking in reverse, if we divide between two we get the parent index
        arr[i] += diferencia;
    }
    return;
}

int STSuma(int arr[], int b0, int b1, int i, int f, int index, int lim1=0, int lim0=0) {  //We walk thru the tree with recursion
    //b0,b1: range of where we want a sum
    //i,f: where we search for the sum
    //index: Where the result will be
    
    //Base case
    if (i == b0 && f == b1) {
        return arr[index];
    }
    else if (b0>f || b1<i) {
        return 0;
    }

    //Recursive step
    lim1 = b1;
    lim0 = b0;
    if (b1 > i+((f-i+1) / 2)-1) {
        lim1 = i + ((f - i + 1) / 2)-1;
    }
    if (b0 < i + ((f - i + 1) / 2)) {
        lim0 = i + ((f - i + 1) / 2);
    }

    //We send two ranges where will be a part of the solution
    return STSuma(arr, b0, lim1, i, i + ((f - i + 1) / 2)-1,index*2+1) + STSuma(arr, lim0, b1, i + ((f - i + 1) / 2), f, index*2+2);
}

int main() {
    int tam = 8;
    int total = tam * 2 - 1;
    int* values = new int[total];
    for (int i = 0; i < total; i++) {           //We get the input
        if (i < tam - 1) {
            values[i] = 0;
        }
        else {
            cin >> values[i];
        }
    }

    build(values, tam);         //We build the tree (array)

    for (int i = 0; i < total; i++) {
        cout << values[i] << " ";
    }
    cout << endl;
    update(values, 0, 100, 8);      //New value

    for (int i = 0; i < total; i++) {
        cout << values[i] << " ";
    }

    int ran[2] = { 5, 7 };          //The range which we want to know its total
    cout << STSuma(values, ran[0], ran[1],1,8,0);           //We pass (array, lower limit, upper limit, range where we search lower, upper, index where will be the result)



    return 0;
}