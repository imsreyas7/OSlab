def memoized(f):
	memo={}
	def found(x):
		if x not in memo:
			memo[x]=f(x);
		return memo[x]
	return found

def fibo2(n):
	if n<=1:
		return n
	else:
		return(fibo2(n-1)+fibo2(n-2))

fibo2=memoized(fibo2)

n=int(input("Enter the number: "))
print("The value is : ",fibo2(n-1))

'''
(base) C:\Users\sreya\Desktop\labs\DAA>python fiboM.py
Enter the number: 10
The value is :  34
'''
