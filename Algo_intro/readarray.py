a=[]
def readarray(a):
	opt=1
	while opt==1:	
		
		x=int(input("Enter the value : "))
		a.append(x)
		
		opt=int(input("Do you want to continue? 1/0 :"))

def subarray(a):
	print("The number of elements entered is : ",len(a))

readarray(a)
subarray(a)

'''
(base) C:\Users\sreya\Desktop\labs\DAA>python readarray.py
Enter the value : 4
Do you want to continue? 1/0 :1
Enter the value : 7
Do you want to continue? 1/0 :1
Enter the value : 11
Do you want to continue? 1/0 :1
Enter the value : 8
Do you want to continue? 1/0 :0
The number of elements entered is :  4
'''
