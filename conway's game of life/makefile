gameOfLife: defs.o zeroPlayer.o twoPlayer.o main.o gameIO.o
	gcc defs.o zeroPlayer.o twoPlayer.o main.o gameIO.o -o gameOfLife 

defs.o: defs.c defs.h
	gcc -c defs.c

zeroPlayer.o: zeroPlayer.c defs.h
	gcc -c zeroPlayer.c

twoPlayer.o: twoPlayer.c defs.h
	gcc -c twoPlayer.c

main.o: main.c defs.h
	gcc -c main.c

gameIO.o: gameIO.c defs.h
	gcc -c gameIO.c

clean: 
	rm -f*.o
