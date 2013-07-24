#!/usr/bin/python
import asserter
import sys
from itertools import premutations
#sys.stdin = open('out.txt','r')
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
last = [{} for i in m]
def met(x,y):
	lis = [(a,b) for a in x for b in y if a == b]
	return len(lis)
for row in range(n):
	it = permutations(a[row])
	best = 10**9
	temp = []
	for lis in it:
		s = 0
		flag = 1
		for col,pair in enumerate(lis):
			a,b = pair[0],pair[1]
			if row != 0 and met(a[row - 1][col][:],pair[:]) :
				flag = 0
				break
			mp = last[col]
			if a in last and mp[a] == 0:
				s += 1
			if b in last and mp[b] == 1:
				s += 1
		continue if !flag
		if s < best :
			best = s
			temp = lis
	assert len(temp)
	a[j] = temp
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
