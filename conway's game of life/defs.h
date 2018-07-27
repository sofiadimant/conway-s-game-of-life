#ifndef DEFS_H_
#define DEFS_H_

/*
 * Basic definitions
 */
typedef void* Element;
typedef Element (*CopyFunction)(Element);
typedef void (*FreeFunction)(Element);
typedef void (*PrintFunction)(Element);
typedef Element (*EvolveFunction)(Element);

/*
 * Structs and enums
 */
typedef enum e_state{
	DEAD, P1, P2, BLANK
}State;

struct t_cell{
	State cellState;
	State neighbors[8];
};
typedef struct t_cell * Cell;

struct t_array{
	int size;
	Element* elements;
	CopyFunction copyElement;
	FreeFunction freeElement;
	PrintFunction printElement;
	EvolveFunction evolveElement;
};
typedef struct t_array * Array;

/*
 * Function Decleration
 */

Array createArray(int _size, CopyFunction _copy, FreeFunction _free, PrintFunction _print, EvolveFunction _evolve);
void destroyArray(Array array);
void set(Array array, int i, Element element);		//assigns array[i]=element;
Element get(Array array, int i);					//returns array[i]


void FreeCell(Element e); // call for cells

Element CopyFunctionZero (Element e);
 void PrintFunctionZero (Element e);
Element EvolveFunctionZero (Element e);

Element CopyFunctionTwo (Element e);
 void PrintFunctionTwo (Element e);
Element EvolveFunctionTwo (Element e);

Element CopyFunctionArray (Element e);
 void FreeFunctionArray (Element e);  // call both for 2 and 1 dim array
 void PrintFunctionArray (Element e);
Element EvolveFunctionArray (Element e);

int NeighborsCountTwoP2(Cell cell);
int NeighborsCountTwoP1(Cell cell);
int NeighborsCountZero(Cell cell);

//Zero Player functions
void ZeroNeighborsUpdate(Array BordArray);
Array zeroGenerations(Array bord, int numOfGenerations);

//Two Player functions
Array twoGenerations(Array bord, int numOfGenerations);
void TwoNeighborsUpdate(Array a);
int chackP1Win(Array a);
int chackP2Win(Array a);



//IO
Array readBoardFromFile(char* filename, int n, int gameType);
void Print2DArray(Element e);
Array Board(char *p, int size, int type);
char* createBoard(int n, char* filename);


#endif /* DEFS_H_ */

