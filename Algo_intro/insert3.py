
a = [1,6,5,4,2,3,0]
count = 0

def swap(a, a1, a2):
	print("swaping")
	print(a1)
	print(a2)
	a1_i = a.index(a1)
	a2_i = a.index(a2)
	temp = a[a1_i]
	a[a1_i] = a[a2_i]
	a[a2_i] = temp


def ordered_insert(a, n):
	print("***ORDERED INSERT***")
	if n != 1:
		for i in range(n-2, -1, -1):
			if a[i] > a[i+1]:
				swap(a,a[i],a[i+1])
	return a[:n]

def ins_sort(a, n):
	if n > 1:
		a[:n-1] = ins_sort(a[:n-1], n-1)
		a = ordered_insert(a, n)
	return a

n=len(a)-1
print(a)
ins_sort(a,n)
print(a)


'''
***ORDERED INSERT***
***ORDERED INSERT***
swaping
6
5
***ORDERED INSERT***
swaping
6
4
swaping
5
4
***ORDERED INSERT***
swaping
6
2
swaping
5
2
swaping
4
2
***ORDERED INSERT***
swaping
6
3
swaping
5
3
swaping
4
3
[1, 2, 3, 4, 5, 6, 0]
'''
