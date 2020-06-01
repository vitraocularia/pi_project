build:
	gcc -o o.out main.c modifyingFunctions.c helpers.c samplerateModifier.c menuHandler.c fileHandler.c -lsndfile 

run: 
	./o.out