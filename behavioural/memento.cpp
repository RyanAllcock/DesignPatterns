#include <stdio.h> // command line output
#include <list> // growing data storage
#include <vector> // memento storage caretaking

struct Designer{ // originator
	std::list<const char*> features; // state
	Designer(){ features = {}; }
	
	struct Plan{ // memento
		std::list<const char*> features;
		Plan(std::list<const char*> f){ features = std::list<const char*>(f);}
	};
	Plan* create(){ return new Plan(features); }
	void restore(Plan *m){ features = m->features; }
};

struct Planner{ // caretaker
	std::vector<Designer::Plan*> options;
	Planner(){ options = {}; }
	void save(Designer::Plan *m){ options.push_back(m); }
	Designer::Plan* load(int x){ return options.at(x) ;}
};

int main(int argc, char *argv[]){
	
	// initialisation
	Designer plan = Designer();
	Planner designs = Planner();
	
	// client usage
	plan.features.push_back("Kitchen and dining room");
	plan.features.push_back("Garage and parking space");
	designs.save(plan.create());
	plan.features.push_back("Extension with sitting area");
	designs.save(plan.create());
	plan.restore(designs.load(0));
	plan.features.push_back("Garden with orchard");
	designs.save(plan.create());
	plan.restore(designs.load(0));
	
	// final output
	std::list<const char*>::iterator fi;
	fi = plan.features.begin(); printf("Plan 0: %s", *fi); for(fi++; fi != plan.features.end(); fi++) printf(", %s", *fi); printf("\n");
	plan.restore(designs.load(1));
	fi = plan.features.begin(); printf("Plan 1: %s", *fi); for(fi++; fi != plan.features.end(); fi++) printf(", %s", *fi); printf("\n");
	plan.restore(designs.load(2));
	fi = plan.features.begin(); printf("Plan 2: %s", *fi); for(fi++; fi != plan.features.end(); fi++) printf(", %s", *fi); printf("\n");
	
	return 0;
}