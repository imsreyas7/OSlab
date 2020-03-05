def swap(a, m, n):
    a[m], a[n] = a[n], a[m]
    return a


def PNF(a, low, high ):
    b = []
    for num in a[low:high]:
        if(num < a[low]):  # pivoting at low
            b.append(num)

    for num in b:
        a.remove(num)

    b = b + a
    a = b
    return a


a = [int(x) for x in input("ENTER THE LIST : ").split()]
a = PNF(a, 0, len(a))
print(a)

'''
(base) C:\Users\sreya\Desktop\9zip>python pnf1.py
ENTER THE LIST: 88 65 477 32 3 98 17
[88, 65, 477, 32, 3, 98, 17]
'''
