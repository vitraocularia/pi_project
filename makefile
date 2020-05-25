build:
	gcc -o o.out main.c modifyingFunctions.c helpers.c -lsndfile 

run: 
	./o.out