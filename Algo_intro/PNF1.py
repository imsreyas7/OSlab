
def PNF(a, low, high):
    b = []
    for num in a:
        if(num < 0):  # appending negative elements to another array
            b.append(num)

    for num in b:
        a.remove(num)

    b = b + a
    a = b
    return a


def swap(a, m, n):
    a[m], a[n] = a[n], a[m]
    return a

a = [int (x) for x in input("ENTER THE LIST: ").split()]
a = PNF(a, 0, len(a))
print(a)

'''
(base) C:\Users\sreya\Desktop\9zip>python pnf1.py
ENTER THE LIST: 88 65 477 32 3 98 17
[88, 65, 477, 32, 3, 98, 17]
'''
