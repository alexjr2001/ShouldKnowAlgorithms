#Project: Quick sort 
#Date: 24/01/2023
from random import randrange as rd

arr = []
a = 0

for i in range(20):
    arr.append(rd(100))

def swap(a,b):
    temp=arr[a]
    arr[a]=arr[b]
    arr[b]=temp

def partition(begin=0,end=len(arr)):                ##Partition recursively with left and right side
    i = begin-1
    pivot = end-1           ##Pivot starts at the end
    for j in range(begin,pivot+1):
        if arr[j] < arr[pivot]:         ##We move the i (middle for partition) in case the pivot is greater than current value
            i+=1                        
            swap(i,j)
    swap(pivot,i+1)

    #printArr(begin,end)

    if begin<i+1: 
        partition(begin,i+1)
    if i+2<end: 
        partition(i+2,end)


def printArr(begin,end):
    if begin+1<end: print(arr[begin:end])

print(arr)
partition()
print(arr)
        
