def fibo2(n):
	if n<=1:
		return n
	else:
		return(fibo2(n-1)+fibo2(n-2))

n=int(input("Enter a number: "))
print("The value is : ",fibo2(n-1))

"""
(base) C:\Users\sreya\Desktop\labs\DAA>python fibo2.py
Enter a number: 9
The value is :  21
"""