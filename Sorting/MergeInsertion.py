##Project: Merge insertion sort
##DATE: 18/10/2021
###A combination of Merge sort and the insertion sort, as we know the Merge Sort would be better in time complexity.
##However if we fusion them we get an algorithm which is better because we save memory and, although merge sort is O(nlogn),
##in very small arrays the insertion sort is faster. That's why we give a small number to apply the insertion sort during a 
##Merge sort.

import random
import math

arr = []
size=16
k=math.pow(size,1/2)        ##Size of the small array to apply Insertion sort

for j in range(0,size):
    arr.append(random.randint(0,100))

def swap(i,j,arr):
    temp=arr[i]
    arr[i]=arr[j]
    arr[j]=temp

def insertion(arr):         ##Apply insertion sort to small arrays.
    l=len(arr)
    for i in range(1,l):  ##1 a L
        k=i
        for j in range(i-1,-1,-1):
            if arr[j]>arr[k]:
                swap(k,j,arr)
                k-=1


def merge(l_arr,r_arr,arr):
    p = 0
    q = 0
    r = 0
 
    left_size = len(l_arr)
    right_size = len(r_arr)
    while p < left_size and q < right_size:     ##We start sorting
        if l_arr[p] < r_arr[q]:
            arr[r] = l_arr[p]
            p += 1
        else:
            arr[r] = r_arr[q]
            q += 1
        r += 1
    while p < left_size:            ##If any side has been left
        arr[r] = l_arr[p]
        p += 1
        r += 1

    while q < right_size:
        arr[r]=r_arr[q]
        q += 1
        r += 1

def mergeSort(arr,k):       ##We split in half the array
    size = len(arr)
    if size > 1:        
        middle = size // 2
        l_arr = arr[:middle]
        r_arr = arr[middle:]
         
        mergeSort(l_arr,k)
        mergeSort(r_arr,k)
        if size==k:
            insertion(arr)
        else:
            merge(l_arr,r_arr,arr)

print(arr)
mergeSort(arr,k)        ##We pass the array and the size to apply the insertion sort
print(arr)
