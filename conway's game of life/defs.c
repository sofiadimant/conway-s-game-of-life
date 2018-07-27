#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"


Element CopyFunctionZero(Element e)
{
	Cell newCell = (Cell)malloc(sizeof(struct t_cell));
	Cell oldCell = (Cell)e;

	if (newCell != NULL) {
		memcpy(newCell, oldCell, sizeof(struct t_cell));
		return newCell;
	}
	else
		return NULL;
}

void FreeCell(Element e) {
	if (e == NULL) {
		return;
	}
	free((Cell)e);
}


void PrintFunctionZero(Element e) {
	Cell oldCell = (Cell)e;
	if (oldCell->cellState == DEAD) {
		printf("%s", ". ");
	}
	if (oldCell->cellState == P1) {
		printf("%s", "X ");
	}

}

Element EvolveFunctionZero(Element e) {
	Cell tCell = (Cell)e;
	Cell evCell = CopyFunctionZero(tCell);
	int counter = NeighborsCountZero(tCell);
	if (evCell->cellState == P1) {
		if (counter == 0 || counter == 1) {
			evCell->cellState = DEAD;
		}
		if (counter > 3) {
			evCell->cellState = DEAD;
		}
	}
	else {
		if (counter == 3) {
			evCell->cellState = P1;
		}
	}
	return evCell;
}

int NeighborsCountZero(Cell cell) {
	int i;
	int counter = 0;
	for (i = 0; i < 8; i++) {
		if (cell->neighbors[i] == P1) {
			counter = counter + 1;
		}
	}
	return counter;
}

Element CopyFunctionTwo(Element e)
{
	Cell newCell = (Cell)malloc(sizeof(struct t_cell));
	Cell oldCell = (Cell)e;
	if (newCell != NULL) {
		memcpy(newCell, oldCell, sizeof(struct t_cell));
		return newCell;
	}
	else
		return NULL;
}


void PrintFunctionTwo(Element e) {
	Cell oldCell = (Cell)e;
	if (oldCell->cellState == DEAD) {
		printf("%s", ". ");
	}
	if (oldCell->cellState == P1) {
		printf("%s", "X ");
	}
	if (oldCell->cellState == P2) {
		printf("%s", "Y ");
	}
}

Element EvolveFunctionTwo(Element e) {
	Cell tCell = (Cell)e;
	Cell evCell = CopyFunctionZero(tCell);
	int counterP1 = NeighborsCountTwoP1(evCell);
	int counterP2 = NeighborsCountTwoP2(evCell);
	if (evCell->cellState == P1 || evCell->cellState == P2) {
		if ((counterP1 + counterP2) == 0 || (counterP1 + counterP2) == 1) {
			evCell->cellState = DEAD;
		}
		if ((counterP1 + counterP2) > 3) {
			evCell->cellState = DEAD;
		}
		if (evCell->cellState == P1) {
			if (counterP2 == 2 || counterP2 == 3) {
				evCell->cellState = P2;
			}
		}
		if (evCell->cellState == P2) {
			if (counterP1 == 2 || counterP1 == 3) {
				evCell->cellState = P1;
			}
		}
	}
	else {
		if (counterP1 + counterP2 == 3) {
			if (counterP1 > counterP2) {
				evCell->cellState = P1;
			}
			if (counterP2 > counterP1) {
				evCell->cellState = P2;
			}
		}
	}
	return evCell;
}

int NeighborsCountTwoP1(Cell cell) {
	int counterp1 = 0;
	int i;
	for (i = 0; i < 8; i++) {
		if (cell->neighbors[i] == P1) {
			counterp1 = counterp1 + 1;
		}
	}
	return counterp1;
}

int NeighborsCountTwoP2(Cell cell) {
	int counterp2 = 0;
	int i;
	for (i = 0; i < 8; i++) {
		if (cell->neighbors[i] == P2) {
			counterp2 = counterp2 + 1;
		}
	}
	return counterp2;
}



Element CopyFunctionArray(Element e) {
	int i;
	Array OldArray = (Array)e;
	Array newArray = createArray(OldArray->size, OldArray->copyElement, OldArray->freeElement, OldArray->printElement, OldArray->evolveElement);
	for (i = 0; i < OldArray->size; i++) {
		Element temp = OldArray->copyElement(OldArray->elements[i]);
		set(newArray,i,temp);
	}
	return newArray;
}


void FreeFunctionArray(Element e) {
	destroyArray((Array)e);
}

void PrintFunctionArray(Element e) {
		Array PArray = (Array)e;
		int i;
		for (i = 0; i < PArray->size; i++) {
			PArray->printElement(PArray->elements[i]);
		}
		printf("\n");
}

Element EvolveFunctionArray(Element e) {
	Array EArray = (Array)e;
	Array evArr = CopyFunctionArray(e);
	int i;
	for (i = 0; i < EArray->size; i++) {
		Element evElem = EArray->evolveElement(EArray->elements[i]);
		set(evArr,i,evElem);
	}
	return evArr;
}

//creats new Array
Array createArray(int _size, CopyFunction _copy, FreeFunction _free, PrintFunction _print, EvolveFunction _evolve) {
	if (_size <= 0)
		return NULL;
	Array arr = (Array)malloc(sizeof(struct t_array));
	arr->elements = (Element*)calloc(_size, sizeof(Element));
	arr->size = _size;
	arr->copyElement = _copy;
	arr->freeElement = _free;
	arr->printElement = _print;
	arr->evolveElement = _evolve;


	return arr;
}


//returns free all the Arral cells and the array it self
void destroyArray(Array array) {
        // printf("call to destroy\n");
	int i;
	if (array == NULL)
		return;
	
	for (i = array->size - 1; i >= 0; i--) {
		if (array->elements[i] != NULL) {
			array->freeElement(array->elements[i]);
			array->elements[i] = NULL;
		}
	}
	// printf("elements destroyed\n");
	if (array->elements != NULL){
	       free(array->elements);
	       array->elements = NULL; 
        }
	if (array != NULL) {
		free(array);
		//(*(Array*)array) = NULL;
	}
	// printf("arr destroyed\n");
}

//assigns array[i]=element;
void set(Array array, int i, Element element) {
	if(array->elements[i] != NULL){
		array->freeElement(array->elements[i]);
	}
	array->elements[i] = element;
}

//returns array[i]
Element get(Array array, int i) {
	return(array->elements[i]);
}

char stateToChar(State state){
	if (state == DEAD)
	   return '.';
	else if (state == P1) {
	   return('X');
	}
	else if (state == P2) {
	   return('Y');
	}
	else return ' ';
}


