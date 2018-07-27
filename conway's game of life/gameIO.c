#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#include "defs.h"

Array Board(char *p, int size, int type) {
	
	int i, j, counter = 0;
	Array Arr = createArray(size, CopyFunctionArray, FreeFunctionArray,
			PrintFunctionArray, EvolveFunctionArray);

	Array curr;
	for (i = 0; i < size; i++) {
		if (type == 1) {
			curr = createArray(size, CopyFunctionZero, FreeCell,
					PrintFunctionZero, EvolveFunctionZero);
		} //iftype1
		if (type == 2) {
			curr = createArray(size, CopyFunctionTwo, FreeCell,
					PrintFunctionTwo, EvolveFunctionTwo);
		} //iftype1

		set(Arr, i, curr);
		//cell for
		for (j = 0; j < size; j++) {
			Cell m = (Cell) malloc(sizeof(struct t_cell));

			if (type == 1) {
				if (p[counter] == 'X') {
					m->cellState = P1;
				}

				if (p[counter] == '.') {
					m->cellState = DEAD;

				}
			} //ifType1
			if (type == 2) {
				if (p[counter] == '.') {
					m->cellState = DEAD;
				}

				if (p[counter] == 'X') {
					m->cellState = P1;
				}

				if (p[counter] == 'Y') {
					m->cellState = P2;
				}

			} //ifType2

			set(curr, j, m);
			counter++;
		}
	}
	return Arr;
}


Array readBoardFromFile(char* filename, int n, int gameType)
{
	FILE* myFile = fopen(filename, "r");
	//read file into array

	char* board;

	//numberArray = (char*) calloc(2 * n * n, sizeof(char));
	board = (char*) calloc(n * n, sizeof(char));
	int l, i;

	int k,h=0;


	if (myFile == NULL) {
		printf("Error Reading File\n");
		return NULL;
	}
	else{
		char c;
		//int count =0;
		do{
		  // count++;
		   //if (count % 100 ==0)		
			//printf("%d \n",count)

		   c=getc(myFile);
			if (c != ' ' && c!= '\n' && (int)c!=EOF) {
						board[h] = (char)c;
						h++;
			}
		}while ((int)c != EOF && h<n*n);
	}
	fclose(myFile);



	Array gameBoard = Board(board, n, gameType);
	
	//free(numberArray);
	free(board);
	return gameBoard;
}

void Print2DArray(Element e) {
		Array PArray = (Array)e;
		int i;
		for (i = 0; i < PArray->size; i++) {
			PArray->printElement(PArray->elements[i]);
		}
}
