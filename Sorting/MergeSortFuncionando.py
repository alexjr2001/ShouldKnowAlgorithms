##Project: Merge Sort
##Date: 20/09/2021
##In this project we analize the complexity of the merge sort O(nlogn) and we print the number of executed lines.

import random

arr = []
l=170  ##170000 to see the duration time   
c=0

for j in range(0,l):
    arr.append(random.randint(0,100))

def merge(l_arr,r_arr,arr):         ##We start sorting
    global c
    c+=6
    p = 0
    q = 0
    r = 0
 
    left_size = len(l_arr)
    right_size = len(r_arr)
    while p < left_size and q < right_size:
        c+=4
        if l_arr[p] < r_arr[q]:
            arr[r] = l_arr[p]
            p += 1
        else:
            
            arr[r] = r_arr[q]
            q += 1
             
        r += 1
    c+=2
    while p < left_size:
        c+=3
        arr[r] = l_arr[p]
        p += 1
        r += 1

    while q < right_size:
        c+=3
        arr[r]=r_arr[q]
        q += 1
        r += 1

def mergeSort(arr):     ##We split in half        
    global c
    c+=2
    size = len(arr)
    if size > 1:
        c+=6
        middle = size // 2
        l_arr = arr[:middle]
        r_arr = arr[middle:]
 
        mergeSort(l_arr)
        mergeSort(r_arr)
        merge(l_arr,r_arr,arr)
        

print(arr)
mergeSort(arr)
print(arr)
print("Lines: ",c)          ##We print the number of executed lines
