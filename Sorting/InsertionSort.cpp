//Insertion sort 31/03/2023 in C++ with stl vector and a good random.
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>

using namespace std;

//Generates random numbers
	std::random_device rd;  
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distrib(1, 100);

int main(){
    vector<int> unsorted;
    for (int i = 0; i < 100; i++)
    {
        unsorted.push_back(distrib(gen));
        cout<<unsorted[i]<<" ";
    }
    
    for(int i=1;i<unsorted.size();i++){
        for(int j=i;j-1>=0 && unsorted[j-1]>unsorted[j];j--){
            swap(unsorted[j-1],unsorted[j]);
        }
    }
    cout<<endl<<endl<<endl<<endl;
    for (int i = 0; i < unsorted.size(); i++)
    {
        cout<<unsorted[i]<<" ";
    }
    
}