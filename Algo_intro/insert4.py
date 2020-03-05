

def insertionSortShiftMethod(arr,n): 
    # base case 
    if n<=1: 
        return
    insertionSortShiftMethod(arr,n-1) 

    last = arr[n-1] 
    j = n-2  
    while (j>=0 and arr[j]>last): 
        arr[j+1] = arr[j] 
        j = j-1
  
    arr[j+1]=last 
  
 
arr = [77,11,138,57,6] 
n = len(arr) 
insertionSortShiftMethod(arr, n) 
print(arr)

'''
(base) C:\Users\sreya\Desktop\9zip>python insert4.py
[6, 11, 57, 77, 138]
'''