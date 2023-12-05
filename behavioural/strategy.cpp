#include <stdio.h> // command line output

struct Boat{ // strategy/policy interface
	virtual int move() = 0; // algorithm
};

struct Speedboat : Boat{ // strategy 1
	int move(){ return 20; }
};

struct Gondola : Boat{ // strategy 2
	int rowerEnergy; // data
	Gondola(int e){ rowerEnergy = e; } // input
	int move(){ return rowerEnergy--; }
};

struct Traveller{
	int position;
	Boat *boat;
	Traveller(Boat *b){ position = 0; boat = b; }
	void go(){ position += boat->move(); } // operation
};

int main(int argc, char *argv[]){ // client usage
	Traveller traveller = Traveller(new Speedboat());
	printf("Traveller starts at position %i\n", traveller.position);
	traveller.go(); traveller.go(); traveller.go();
	printf("Traveller goes to position %i\n", traveller.position);
	traveller.boat = new Gondola(5);
	printf("Traveller changes boat\n");
	traveller.go(); traveller.go(); traveller.go();
	printf("Traveller finishes at position %i\n", traveller.position);
	return 0;
}