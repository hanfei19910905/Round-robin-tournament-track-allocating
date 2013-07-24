#!/usr/bin/python
import sys
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
last,recent,vis=[],[],[]
def chk(tmp,shen,qian):
	last,lastline = {},{}
	ans,value = 0,0
	inf = 10**10
	for cnt,a in enumerate(tmp):
		x,y = a[0],a[1]
		if x == 0 :
			continue
		if x not in last:
			last[x] = 0
		elif last[x] == 1:
			last[x] = 0
		else:
			ans += 1
			if x in lastline :
				value += cnt - lastline[x]
		if y not in last:
			last[y] = 1
		elif last[y] == 0:
			last[y] = 1
		else :
			ans += 1
			if y in lastline :
				value += cnt - lastline[y]
	#	print x,y
		shen[x] += 1
		qian[y] += 1
		lastline[x] = cnt
		lastline[y] = cnt
	for i in range(1,N+1):
		if(abs(shen[i] - qian[i]) > 1): return (inf,value)
	return (ans,value)
shen = [0] * (N+1)
qian = [0] * (N+1)
def work(ar):
	maxn = 1 << n
	s = 10**10,0
	ans = 0
	for msk in range(maxn):
		tmp = []
		for i in range(n):
			if ((1 << i) & msk) != 0:
				tmp.append([ar[i][1],ar[i][0]])
			else :
				tmp.append(ar[i])
		value = chk(tmp,shen[:],qian[:])
		if(value[0] < s[0] or (value[0] == s[0] and value[1] > s[1])):
			s = value
			ans = msk
		if(s == 0):
			return ans
	#print 'ans:',s
	return ans
for j in range(m):
	#print 'j',j
	tt = []
	for i in range(n):
		tt.append(a[i][j])
	x = work(tt)
	for i in range(n):
		if ((1 << i) & x) != 0:
			swap(a[i][j])
		shen[a[i][j][0]] += 1
		qian[a[i][j][1]] += 1
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
for i in range(m):
	conf = 0
	for j in range(n):
		x = a[j][i][0]
		if(x == 0) :continue
		for k in range(j+1,n):
			if a[k][i][1] == x: break
			elif a[k][i][0] == x:
#				print j,k
				conf += 1
				break
		y = a[j][i][1]
		for k in range(j+1,n):
			if a[k][i][0] == y : break
			elif a[k][i][1] == y:
#				print j,k
				conf += 1
				break
	print 'column',i,':',conf
shen = [0] * (N+1)
qian = [0] * (N+1)
for i in range(n):
	for j in range(m):
		x,y = a[i][j]
		shen[x] += 1
		qian[y] += 1
print shen[1:]
print qian[1:]
