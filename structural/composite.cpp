#include <stdio.h> // command line output
#include <list> // component storage

struct Water{ // component base class
	virtual void flow(float w) = 0;
};

struct River : Water{ // composite
	std::list<Water*> children;
	void add(Water *w){ children.push_back(w); }
	void flow(float w){
		float remaining = w;
		float current = w / 2;
		for(Water *child : children){
			child->flow(current);
			remaining -= current;
			current /= 2;
		}
		printf("%f water evaporated from river\n", remaining);
	}
};

struct Reservoir : Water{ // leaf 1
	void flow(float w){ printf("%f water deposited in pond\n", w); }
};

struct Ocean : Water{ // leaf 2
	void flow(float w){ printf("%f water returns to sea\n", w); }
};

int main(int argc, char *argv[]){
	
	// initialisation
	River *tributary = new River();
	River *delta = new River();
	Reservoir *pond = new Reservoir();
	Ocean *sea = new Ocean();
	tributary->add(pond);
	tributary->add(delta);
	delta->add(sea);
	
	// client usage
	tributary->flow(10);
	delta->flow(5);
	
	delete tributary;
	delete delta;
	delete pond;
	delete sea;
	return 0;
}