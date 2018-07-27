#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"


Array twoGenerations(Array bord, int numOfGenerations) {
	Array BordArray = bord;
	int i,l,k,j,m=1, win;
	Array arr;
	TwoNeighborsUpdate(BordArray);
	Array evArray = EvolveFunctionArray(BordArray);
	destroyArray(BordArray);
	BordArray = evArray;
	printf("Generation number %d\n", m);
	Print2DArray(BordArray);

	for (m =1; m < numOfGenerations; m++) {

		if (m>0 && m%2 !=0){
		
			win = chackP1Win(BordArray);
			if (win!=0){

			printf("%s" ,"Player 1: please choose a cell of player 2 to kill\n" );
			printf("%s", "Enter column: ");
			scanf("%d" , &i);
			printf("%s", "Enter row: ");
			scanf("%d" , &j);

		//go to the cell and change is cell state
			arr=get(BordArray,j);
			if (((Cell)arr->elements[i])->cellState == P2)
			  ((Cell)arr->elements[i])->cellState =DEAD;
			else
				printf("%s" ,"Move is not available, thise is not alive cell of 				player 2.\n");

	   // send to the subFunction to update the Neighbors neighbors array
			//updateMyCellStatAtMyNeighbors((Cell)arr->elements[i],j, i, BordArray);
			TwoNeighborsUpdate(BordArray);
			
			Print2DArray(BordArray);
			printf("\n");
			printf("%s" ,"Choose a dead cell to revive\n" );
			printf("%s", "Enter column: ");
			scanf("%d" , &i);
			printf("%s", "Enter row: ");
			scanf("%d" , &j);

		//go to the cell and change is cell state
			arr=get(BordArray,j);
			if (((Cell)arr->elements[i])->cellState == DEAD)
			  ((Cell)arr->elements[i])->cellState =P1;
			else
				printf("%s" ,"Move is not available, Thise is not a dead cell\n");

	   		// send to the subFunction to update the Neighbors neighbors array
			
			TwoNeighborsUpdate(BordArray);
			Print2DArray(BordArray);
			printf("\n");
			}
			else{
				printf("%s", "THE WINNER IS PLAYER 1!\n");
				Print2DArray(BordArray);
				printf("\n");
				return BordArray;
			}
		}
		if (m>=0 && m%2 ==0){

			win = chackP2Win(BordArray);
			if (win!=0){

			printf("%s" ,"Player 2: please choose a cell of player 1 to kill\n" );
			printf("%s", "Enter column: ");
			scanf("%d" , &i);
			printf("%s", "Enter row: ");
			scanf("%d" , &j);

		//go to the cell and change is cell state
			arr=get(BordArray,j);

			if (((Cell)arr->elements[i])->cellState == P1)
			  ((Cell)arr->elements[i])->cellState =DEAD;
			else
				printf("%s" ,"Move is not available, Thise is not alive cell of 				player 1.\n");

	   // send to the subFunction to update the Neighbors neighbors array
			TwoNeighborsUpdate(BordArray);
			Print2DArray(BordArray);
			printf("\n");
			printf("%s" ,"Choose a dead cell to revive\n" );
			printf("%s", "Enter column: ");
			scanf("%d" , &i);
			printf("%s", "Enter row:");
			scanf("%d" , &j);

			//go to the cell and change is cell state
			arr=get(BordArray,j);
			
			if (((Cell)arr->elements[i])->cellState == DEAD)
			  ((Cell)arr->elements[i])->cellState =P2;
			else
				printf("%s" ,"Move is not available, Thise is not a dead cell\n");

		   // send to the subFunction to update the Neighbors neighbors array
			TwoNeighborsUpdate(BordArray);
			//Print2DArray(BordArray);
			}
		else{
				printf("%s", "THE WINNER IS PLAYER 2!\n");
				Print2DArray(BordArray);
				printf("\n");
				return BordArray;
			}

		}
		

		TwoNeighborsUpdate(BordArray);

		Array evArray = EvolveFunctionArray(BordArray);
		destroyArray(BordArray);
		BordArray = evArray;
		printf("Generation number %d\n", m+1);
		Print2DArray(BordArray);
		
	}
printf("GAME OVER\n");
return BordArray;
		
}


void TwoNeighborsUpdate(Array a){
   int i, j;
   for (i = 0; i < a->size ;i++)
      for (j = 0; j < a->size;j++){
	 Cell currentCell = (Cell)get(get(a, i), j);
	 int di, dj;	 
	 int n = 0; // index of the neighbor
	 for (di = -1; di <= 1; di++ )
	    for (dj = -1; dj <= 1; dj++ )
	    {  
	       if (!(di==0 && dj == 0)){	       
		  int ni = i + di; // neighbor row
		  int nj = j + dj; // neighbor column
		  if (ni < 0 || nj < 0 || ni >= a->size || nj >= a->size ){
		     currentCell->neighbors[n] = BLANK;
		  }
		  else{
		     Cell neighborCell = (Cell)get(get(a, ni), nj);
		     currentCell->neighbors[n] = neighborCell->cellState;
		  }
		  n++;		  
	       }
	    }
}
}


int chackP1Win(Array a){
   int i, j;
	int counter=0; 
	 for (i = 0; i < a->size ;i++){
      for (j = 0; j < a->size;j++){
	 	Cell currentCell = (Cell)get(get(a, i), j);		
		 if(counter ==0){		 
			if (currentCell->cellState == P1){
			counter = counter +1;
			}
		 }
		 else{
			return counter;
		 }

	}
	}
	return counter;
}

int chackP2Win(Array a){
   int i, j;
	int counter=0;
	 for (i = 0; i < a->size ;i++){
      for (j = 0; j < a->size;j++){
		Cell currentCell = (Cell)get(get(a, i), j);
		if(counter ==0){		 
			if (currentCell->cellState == P1){
			counter = counter +1;
			}
		}
		else{
		return counter;
		}

	}
	}
	return counter;
}


