from numpy.random import uniform

n = 5
print n
for i in range(n): #veces
	v = ['{:0.2f}'.format(uniform(.01, 2)) if j != i  else '1' for j in range(n)]
	print ' '.join(v)
#print '{0:d} {1:d}'.format(0,0)