def sub_array(a, low, high):
    print(a[low:high])
    return;


def read_array():
    a = [int(x) for x in input().split()]
    return a, len(a)


def minimum(a, low, high):
    b = a[low:high]
    return b.index(min(b))+low  #returning the index with respect to the array a


def swap(a, m, n):
    a[n], a[m] = a[m], a[n]
    return a


def sel_sort(a):
    n = len(a)
    for i in range(n):
        temp = minimum(a, i, n)
        a = swap(a, temp, i)
    return a


a = []
print("SELECTION SORT")
print("\nENTER THE LIST : ")
a, size = read_array()
print("THE SIZE OF ARRAY : ", size)
print("MINIMUM VALUE : ", a[minimum(a, 0, len(a))])
print("AFTER SELECTION SORT: \n")
a = sel_sort(a)
sub_array(a,0,len(a))


'''
(base) C:\Users\sreya\Desktop\9zip>python selection_sort.py
SELECTION SORT

ENTER THE LIST :
10 333 75 99 8 64 321 45
THE SIZE OF ARRAY :  8
MINIMUM VALUE :  8
AFTER SELECTION SORT:

[8, 10, 45, 64, 75, 99, 321, 333]
'''
