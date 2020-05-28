build:
	gcc -o o.out main.c modifyingFunctions.c helpers.c samplerateModifier.c -lsndfile 

run: 
	./o.out