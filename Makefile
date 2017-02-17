run:
	./task1
	./task2
	./bonus3

build: task1 task2 bonus3

task1: task1.o
	gcc task1.o -o task1

task1.o: task1.c
	gcc -c task1.c -o task1.o

task2: task2.o
	gcc task2.o -o task2

task2.o: task2.c
	gcc -c task2.c -o task2.o

bonus3: bonus3.o
	gcc bonus3.o -o bonus3

bonus3.o: bonus3.c
	gcc -c bonus3.c -o bonus3.o
	
clean:
	rm -rf task1 task2 task1.o task2.o  bonus3 bonus3.o

