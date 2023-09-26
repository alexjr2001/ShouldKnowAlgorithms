#Project: Binary Search
#Date: 11/07/2023

import random 

arr = []
l=90  #Length
c=0
num=40    #Number we are searching for
i=0       #Initial Position
f=l       #Final positon

##Creating a random array
multiplicando=random.randint(1,10)
for j in range(0,l):
    arr.append(random.randint(j*multiplicando,(j+1)*multiplicando))
    ##print(arr[j])
half=int(l/2)-1

def BB(i,f,arr,c):
    c=c+1
    if(i==f):        #Not Found
        c=c+1
        print("False")         
        print("Lines: ",c)
        return False
    c=c+2
    half=int((i+f)/2)-1
    if(arr[half]==num):        #Found
        c=c+1
        print("True")
        print("Lines: ",c)
        return True
    else:               #Not found yet, let's partition
        c=c+2
        if(arr[half]>num):
            BB(i,half+1,arr,c)      ##To the left
        else:
            BB(half+2,f,arr,c)      ##To the right

BB(i,f,arr,c)
