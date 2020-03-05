a=[2,3,5,7,11,13,17,19,23,29,31,37,41,43]

def print_array(a,low,high):
	print(a[low:high])

l=int(input("Enter the lower limit: "))
h=int(input("Enter the higher limit: "))
print_array(a,l,h)

'''
(base) C:\Users\sreya\Desktop\labs\DAA>python printarray.py
Enter the lower limit: 3
Enter the higher limit: 7
[7, 11, 13, 17]
'''
