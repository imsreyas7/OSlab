
a = [1,3,4,2]

def swap(a, a1, a2):
	print("swap")
	a1_i = a.index(a1)
	a2_i = a.index(a2)
	temp = a[a1_i]
	a[a1_i] = a[a2_i]
	a[a2_i] = temp


def ordered_insert(a):
	print("***ORDERED INSERT***")
	n = len(a)-1
	for i in range(n-1,-1,-1):
		if(a[n] < a[i]):
			swap(a, a[n], a[i])
			n = i
	return a

n=len(a)-1
print(a)
print(ordered_insert(a))

'''
(base) C:\Users\sreya\Desktop\9zip>python insert1.py
[1, 3, 4, 2]
***ORDERED INSERT***
swap
swap
[1, 2, 3, 4]
'''