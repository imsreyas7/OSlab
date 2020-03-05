
a = [4,1,2,3]

def swap(a, a1, a2):
	print("swap")
	a1_i = a.index(a1)
	a2_i = a.index(a2)
	temp = a[a1_i]
	a[a1_i] = a[a2_i]
	a[a2_i] = temp


def ordered_insert_rev(a,n):
	print("***ORDERED INSERT***")
	pos = 0
	for i in range(0,n):
		if(a[pos]>a[pos+1]):
			swap(a, a[pos], a[pos+1])
			pos+=1
	return a

n=len(a)-1
print(a)
print(ordered_insert_rev(a,n))

'''
(base) C:\Users\sreya\Desktop\9zip>python insert5.py
[4, 1, 2, 3]
***ORDERED INSERT***
swap
swap
swap
[1, 2, 3, 4]
'''