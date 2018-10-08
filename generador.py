import random

n = 5
print '{0:d}'.format(n) #n
for i in range(0,n): #veces
	x = random.randint(1, 10)
	y = random.randint(1, 10)
	print '{0:d} {1:d}'.format(x,y)
print '{0:d} {1:d}'.format(0,0)