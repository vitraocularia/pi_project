build:
	gcc -o o.out main.c modifyingFunctions.c -lsndfile 

run: 
	./o.out