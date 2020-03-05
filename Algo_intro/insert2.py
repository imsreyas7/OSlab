
a = [1,3,5,2,4]

def swap(a, a1, a2):
	a1_i = a.index(a1)
	a2_i = a.index(a2)
	temp = a[a1_i]
	a[a1_i] = a[a2_i]
	a[a2_i] = temp

def ordered_insert(a, n):
	print("***ORDERED INSERT***")
	pos = n-1
	for j in range(0,2):
		for i in range(pos-1,-1,-1):
			if(a[pos] < a[i]):
				swap(a, a[pos], a[i])
				pos = i
		pos = n
	return a

n=len(a)-1
print(a)
print(ordered_insert(a, n))



'''
(base) C:\Users\sreya\Desktop\9zip>python insert2.py
[1, 3, 5, 2, 4]
***ORDERED INSERT***
[1, 2, 3, 4, 5]
'''