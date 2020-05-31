build:
	gcc -o o.out main.c modifyingFunctions.c helpers.c samplerateModifier.c menu.c quitSave.c -lsndfile 

run: 
	./o.out