#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"


Array zeroGenerations(Array bord, int numOfGenerations) {
	Array BordArray = bord;
	int i,j,k;
	for (i = 0; i < numOfGenerations; i++) {
		ZeroNeighborsUpdate(BordArray);
		Array evArray = EvolveFunctionArray(BordArray);
		destroyArray(BordArray);
		BordArray = evArray;
     
}
	
	
  Print2DArray(BordArray);	
  return BordArray;
}


void ZeroNeighborsUpdate(Array a){
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



