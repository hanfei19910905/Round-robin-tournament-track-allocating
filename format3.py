#!/usr/bin/python
import sys
sys.stdin = open('out.txt','r')
a = []
n=0
flag = map(int,raw_input().split())
N = sum(flag)
ans = 1
ev = [0]*(N+1)
for x in flag:
	for i in range(x):
		if x % 2 == 0 and i % 2 == 0:
			ev[i + ans] = 1
	ans += x
for ch in sys.stdin:
	b = ch.split()
	n += 1
	for i in range(len(b)):
		b[i] = map(int,b[i].split(','))
	a.append(b)
m = len(a[0])
hs = [[0] * m for i in range(N)]
for i in range(n):
	for j in range(m):
		if a[i][j][0] != 0:
			hs[a[i][j][0]-1][j]+=1
			hs[a[i][j][1]-1][j]+=1
def swap(x):
	x[0],x[1] = x[1],x[0]
for i in range(n):
	for j in range(m):
		x,y = a[i][j]
		if x == 0 or (ev[min(x,y)] and abs(x-y)==1):
			print '{0:3},{1:3}'.format(x,y),
		elif abs(x-y) % 2 == 0:
			if	x > y:
				print '*{0:2},{1:3}'.format(x,y),
			else:
				print '{0:3},*{1:2}'.format(x,y),
		else:
			if x > y:
				print '{0:3},*{1:2}'.format(x,y),
			else :
				print '*{0:2},{1:3}'.format(x,y),
		print ' | ',
	print ''
for i in range(N):
	print hs[i]
def met(a,b):
	ans = 0
	if a[0] == 0 or b[0] == 0: return 0
	if a[0]==b[0]:ans += 1
	if a[1]==b[1]:ans += 1
	return ans
for i in range(m):
	conf = 0
	for j in range(n):
		x = a[j][i][0]
		if(x == 0) :continue
		for k in range(j+1,n):
			if a[k][i][1] == x: break
			elif a[k][i][0] == x:
	#			print j,k
				conf += 1
				break
		y = a[j][i][1]
		for k in range(j+1,n):
			if a[k][i][0] == y : break
			elif a[k][i][1] == y:
	#			print j,k
				conf += 1
				break
	print 'column',i,':',conf
