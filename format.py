#!/usr/bin/python
import sys
sys.stdin =open('out.txt','r')
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
last,recent,vis=[],[],[]
def chg(x,i,j):
	for c in range(i):
		xa = a[c][j][0]
		ya = a[c][j][1]
		if(xa == 0):
			continue
		if xa == x or ya == x:
			swap(a[c][j])
			if recent[xa] == c :
				last[xa] ^= 1
			elif  recent[ya] == c :
				last[ya] ^= 1
for j in range(m):
	vis = [0] * n
	last = [-1] * (N+1)
	recent = [-1] * (N+1)
	for i in range(n):
		x,y = a[i][j][0],a[i][j][1]
		if(x==0):
			continue
		recent[x] = i
		recent[y] = i
		if last[x] == 0 and last[y] == 1:
			last[x] ,last[y] =1, 0
			swap(a[i][j])
		elif last[x] == 0 and last[y] == 0:
			chg(x,i,j)
			last[x] ,last[y] =0, 1
		elif last[x] == 1 and last[y] == 1:
			chg(y,i,j)
			last[x] ,last[y] =0, 1
		elif last[x] == 1 and last[y] == 0:
			last[x] ,last[y] =0, 1
		elif last[x] == 0 or last[y] == 1:
			last[x] ,last[y] =1, 0
			swap(a[i][j])
		else:
			last[x] ,last[y] =0, 1
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
