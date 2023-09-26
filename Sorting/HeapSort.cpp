//Project: HeapSort
//Date: 30/06/2023
#include <iostream>
#include <deque> 
#include <random> 
using namespace std;


void swap(deque<int> &arr, int a, int b){
    cout<<"\nSwap: "<< arr[a] << arr[b] << endl;
    int temp= arr[b];
    arr[b] = arr[a];
    arr[a] = temp;
    return;
}


//The following the option are the iterative version
void max_heap(deque<int>* p_arr){
    int nodes = p_arr->size();
    int non_leaf = nodes/2;
    int last_non_leaf_index = non_leaf-1;

    for(int j=last_non_leaf_index;j>=0;j--){        //We sort the heap 
        cout<<(*p_arr)[j]<<" ";
        for(int i=j;i*2+1<nodes;){
            if(i*2+1==nodes-1 || (*p_arr)[i*2+1]>(*p_arr)[i*2+2]){
                if((*p_arr)[i*2+1]>(*p_arr)[i]){ 
                    swap(*p_arr,i,i*2+1);
                    i=i*2+1;
                }
                else break;
            }
            else if(i*2+2<nodes && (*p_arr)[i*2+2]>(*p_arr)[i]){ 
                swap(*p_arr,i,i*2+2);    
                i=i*2+2;
            }
            else break;
        }          
    }

    return;
}
deque<int> heap_sort(deque<int>* p_arr){
    deque<int> sorted;
    max_heap(p_arr);
    while(p_arr->size()){
        sorted.push_front((*p_arr)[0]);
        swap(*p_arr,0,(*p_arr).size()-1);
        p_arr->pop_back();
        max_heap(p_arr);
    }

    return sorted;
}

int main(){
    //Generation of a random number
    std::random_device rd;  
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distrib(1, 100);


    int number;
    deque<int> arr = {33,68,43,19,64,36,6,64,66,86};
    //for(int i=0;i<10;i++) arr.push_back(distrib(gen));  //Random numbers option
    cout<<"Insert the number (to escape press -1): \n";
    cin >> number;
    while(number!=-1){
        arr.push_back(number);
        cin>> number;
    }
    for (int i = 0; i < arr.size(); i++) cout << arr[i]<<" ";
    cout << endl;
    arr=heap_sort(&arr);
    cout << endl;
    for (int i = 0; i < arr.size(); i++) cout << arr[i] << " ";

    return 0;
}