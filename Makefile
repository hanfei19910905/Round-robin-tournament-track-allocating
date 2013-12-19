all: 
	g++ -o main.exe main.cc 
posix:
	g++ -o main.exe main.cc -D POSIX
