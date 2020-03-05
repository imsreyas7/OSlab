def fibo(n):
	f=-1
	s=1
	t=0
	i=1

	while i<=n:
		t=f+s
		f=s
		s=t
		i+=1
	print("The value is",t)

n=int(input("Enter the number : "))
fibo(n)


'''
(base) C:\Users\sreya\Desktop\labs\DAA>python fibo.py
Enter the number : 11
The value is 55
'''