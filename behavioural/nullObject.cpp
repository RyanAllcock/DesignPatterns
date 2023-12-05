#include <stdio.h> // command line output

struct Plant{ // interface
	virtual const char* pick() = 0;
};

struct PlantFruit : Plant{ // concrete 1
	const char *bounty; // data
	PlantFruit(const char *f){ bounty = f; }
	const char* pick(){ return bounty; } // normal functionality
};

struct PlantStem : Plant{ // null object
	const char* pick(){ return "stem where something should be"; } // null functionality
};

int main(int argc, char *argv[]){ // client usage
	Plant *plant = new PlantStem(); // initial assignment
	printf("A %s is picked from the plant\n", plant->pick());
	plant = new PlantFruit("strawberry"); // concrete assignment
	printf("A %s is picked from the plant\n", plant->pick());
	return 0;
}