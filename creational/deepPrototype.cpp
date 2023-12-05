#include <stdio.h> // command line output

struct Tribble{
	const char *colour;
	Tribble(const char *c){ colour = c; } // basic constructor
	Tribble(Tribble *clone){ colour = clone->colour; } // deep copy constructor
};

int main(int argc, char *argv[]){
	
	// initialisation
	Tribble *family[5];
	family[0] = new Tribble("Red"); // original instance
	family[1] = new Tribble(family[0]); // cloned instance
	family[2] = new Tribble(family[0]); family[2]->colour = "Blue"; // clone with mutated data
	family[3] = new Tribble(family[2]); // mutated instance clone
	family[4] = new Tribble(family[2]);
	
	// client usage
	printf("Tribble family colours:");
	for(int i = 0; i < 5; i++) printf(" %s", family[i]->colour);
	printf("\n");
	
	return 0;
}