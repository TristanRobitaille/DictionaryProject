execute: node.o main.o translator.o dict.o user_interaction.o
	gcc -o test node.o translator.o main.o dict.o user_interaction.o -lpython

node.o: node.c node.h
	gcc -c node.c
	
dict.o: dict.c dict.h
	gcc -c dict.c
	
main.o: main.c
	gcc -c main.c -I /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7

user_interaction.o: user_interaction.c user_interaction.h
	gcc -c user_interaction.c

testPlayground.o: testPlayground.c testPlayground.h
	gcc -c testPlayground.c -I /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7

translator.o: translator.c translator.h
	gcc -c translator.c -I /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7