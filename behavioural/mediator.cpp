#include <stdio.h> // command line output
#include <string.h> // string comparisons

struct Portal; // colleague/component

struct Mediator{ // mediator interface
	virtual void notify(const char *event) = 0;
};

struct Portal{ // component interface
	Mediator *mediator;
	Portal(){ mediator = NULL; }
};

struct Entrance : Portal{ // requesting component
	Entrance() : Portal() {}
	void approach(){ mediator->notify("arrivingToPark"); }
};

struct Exit : Portal{ // releasing component
	Exit() : Portal() {}
	void depart(){ mediator->notify("maneuveringToLeave"); }
};

struct Carpark : Mediator{ // mediator concrete
	Entrance *entrance;
	Exit *exit;
	bool hasSpace; // resource
	int queue; // data
	Carpark(Entrance *c1, Exit *c2){
		entrance = c1; exit = c2; // allocate components
		entrance->mediator = this; exit->mediator = this; // allocate mediator
		hasSpace = true; queue = 0;
	}
	void notify(const char *event){
		if(event == "arrivingToPark"){ if(hasSpace) hasSpace = false; else queue++; }
		else if(event == "maneuveringToLeave"){ if(queue > 0) queue--; else hasSpace = true; }
		printf("Event %s: parking space is %s, queue of %i cars at entrance\n", event, hasSpace ? "free" : "taken", queue);
	}
};

int main(int argc, char *argv[]){ // client usage
	Entrance *entrance = new Entrance();
	Exit *exit = new Exit();
	Carpark *park = new Carpark(entrance, exit);
	entrance->approach();
	entrance->approach();
	entrance->approach();
	exit->depart();
	exit->depart();
	exit->depart();
	entrance->approach();
	exit->depart();
	return 0;
}