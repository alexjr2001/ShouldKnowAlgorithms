//Project: Segment Tree
//Author: Alexander Gómez
//Date: 05/2022
/*
This project tries to receive numbers and build a tree with those numbers as long as it satisfies the segment tree rules 
(The main one is that parent has to be greater than its children).
*/

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
vector<int> merge(int len, int* arr) {
	int end = len;		
	int begin = 1;		
	vector<int> i;
	vector<int> f;
	vector<int> newVec;
	i.push_back(begin);
	f.push_back(end);
	int j = 0;
	double resta = 0;
	int counter = 0;
	int comparative = 0;
	int middle = 0;
	while (counter<len) {
		if (i[j] != 0) {
			resta = f[j] - (i[j] - 1);
			middle = ceil(resta / 2);
			comparative = middle + i[j] - 1;
			if (i[j] != comparative) {
				i.push_back(i[j]);
				f.push_back(comparative);
			}
			else {
				newVec.push_back(arr[comparative - 1]);
				counter++;
				i.push_back(0);
				f.push_back(0);
			}
			if (comparative + 1 != f[j]) {
				i.push_back(comparative + 1);
				f.push_back(f[j]);
			}
			else {
				newVec.push_back(arr[comparative]);
				counter++;
				i.push_back(0);
				f.push_back(0);
			}
		}
		else {
			i.push_back(0);
			f.push_back(0); 
			i.push_back(0);
			f.push_back(0);
		}
		j++;
	}
	return newVec;
}

int main() {
	int len = 8;
	int total = 2 * len - 1;
	int* nums = new int[len];
	int v = 0;
	cout<<"Insert " << len << " values for the tree: \n";
	for(int i = 0; i < len; i++) {			//Initialization of the array
		cin >> v;
		nums[i] = v;
	}

	if (len%2==1) {
		vector<int> newVec;
		newVec= merge(len, nums);
		for(auto i:newVec){
			cout<<i<<" ";
		}
		for (int i = 0; i < len; i++) {
			nums[i] = newVec[i];
		}
		
	}
	
	int* nums2= new int[total];
	for (int i = 0; i < total; i++) {
		if (i < len-1) {
			nums2[i] = 0;
		}
		else {
			nums2[i] = nums[i - (len - 1)];
		}
	}

	int j = 0;
	for (int i = total; i > 1; i-=2) {
		j = floor(i / 2)-1;
		if (nums2[i-1] > nums2[i - 2]) {
			nums2[j] = nums2[i-1];
		}
		else {
			nums2[j] = nums2[i-2];
		}
	}

	//J and K to print a slash every level of the tree (it's a binary tree *2 every level increment)
	j=0;
	int k=0;
	for (int i = 0; i < total; i++) {
		if(k+pow(2,j)==i){
			cout<<"|";
			k+=pow(2,j);
			j++;
		}
		cout << nums2[i] << " ";
	}

	return 0;
}
