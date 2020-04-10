execute: node.o main2.o translator.o dict.o user_interaction2.o
	gcc -o test node.o translator.o main2.o dict.o user_interaction2.o -lpython

node.o: node.c node.h
	gcc -c node.c
	
dict.o: dict.c dict.h
	gcc -c dict.c
	
main2.o: main2.c
	gcc -c main2.c -I /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7

user_interaction2.o: user_interaction2.c user_interaction2.h
	gcc -c user_interaction2.c

testPlayground.o: testPlayground.c testPlayground.h
	gcc -c testPlayground.c -I /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7

translator.o: translator.c translator.h
	gcc -c translator.c -I /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7