#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include "defs.h"

int main(int argc, char *argv[]) {
 	if (argc < 5){
	   printf ("to few arguments\n");
	   return -1;
        } 
	int n;
	int gameType, generations;



	char * filename = argv[3];
	sscanf(argv[1], "%d", &gameType);
	sscanf(argv[2], "%d", &n);
	sscanf(argv[4], "%d", &generations);



	
        Array gameBoard = readBoardFromFile(filename, n, gameType);
	if (gameType==1){

		gameBoard = zeroGenerations(gameBoard,generations);
	}
	if (gameType==2)
		gameBoard=twoGenerations(gameBoard,generations);
	
	//free(filename);
	destroyArray(gameBoard);
	
	//free(board);



}



