execute: node.o testPlayground.o translator.o
	gcc -o test node.o translator.o testPlayground.o -lpython

node.o: node.c node.h
	gcc -c node.c

testPlayground.o: testPlayground.c testPlayground.h
	gcc -c testPlayground.c -I /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7

translator.o: translator.c translator.h
	gcc -c translator.c -I /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7