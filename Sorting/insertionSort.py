#Insertion sort  25/01/2023
from random import randrange as rd

arr = []

for i in range(10):
    arr.append(rd(100))


def insertionSort(a):
    for i in range(1,len(a)):
        change=i
        for j in range(i-1,-1,-1):
            if a[change]<a[j]:
                swap(a,change,j)
                change=j
            else: break
    

def swap(arr,a,b):
    temp=arr[a]
    arr[a]=arr[b]
    arr[b]=temp

print(arr)
insertionSort(arr)
print(arr)