all:static

static:main.o Hash-Table.o
	gcc main.o Hash-Table.o -o static

dynamic:main.o libmht.so
	gcc main.o -L. -lmht -o dynamic

Hash-Table.o:Hash-Table.c
	gcc -std=c99 -c Hash-Table.c

main.o:main.c
	gcc -std=c99 -c main.c

libmht.so:Hash-TableD.o
	gcc -shared -o libmht.so Hash-TableD.o

Hash-TableD.o:Hash-Table.c
	gcc -std=c99 -fPIC -c Hash-Table.c -o Hash-TableD.o

Hash-Table.c:

main.c:
