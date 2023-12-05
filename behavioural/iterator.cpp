#include <stdio.h> // command line output
#include <string.h> // string manipulation

struct Solver{ // iterator interface
	const char *data; // aggregate structure
	int nextStep; // status
	char clue[256]; int size; // element data
	virtual void nextClue() = 0;
	virtual bool isSolved() = 0;
};

struct Puzzle{ // aggregate interface
	virtual Solver* getSolver() = 0;
};

struct SeekSolver : Solver{ // iterator concrete
	SeekSolver(const char *d){ data = d; nextStep = 0; strcpy(clue, "Preparing for puzzle\0"); size = strlen("Preparing for puzzle\0"); }
	void nextClue(){
		const char *next = &data[nextStep];
		nextStep = (int)next++[0];
		for(size = 0; next[size] != '\0' && next[size] != ' '; size++);
		strncpy(clue, next, size);
		clue[size] = '\0';
	}
	bool isSolved(){ return ((const char*)data)[nextStep] == '-' || nextStep >= 128; }
};

struct SeekPuzzle : Puzzle{ // aggregate concrete
	const char *data;
	SeekPuzzle(const char *d){ data = d; }
	Solver* getSolver(){ return new SeekSolver(data); }
};

int main(int argc, char *argv[]){
	
	// initialisation
	SeekPuzzle puzzle = SeekPuzzle("0StartOfPuzzle                  -AMidwayThrough !NextStepFound   aNearlyThere                     FinishedThePuzzle              ");
	
	// client usage
	Solver *solver = puzzle.getSolver(); printf("%s\n", solver->clue);
	while(!solver->isSolved()){ solver->nextClue(); printf("%s\n", solver->clue); }
	
	return 0;
}