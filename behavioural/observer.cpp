#include <stdio.h> // command line output
#include <list> // observer storage

struct Participant{ // observer/listener/subscriber interface
	virtual void update(const char *message) = 0;
};

struct MatchUpdate{ // subject/publisher interface
	std::list<Participant*> observer;
	MatchUpdate(){ observer = {}; }
	virtual void attach(Participant *o) = 0;
	virtual void detach(Participant *o) = 0;
	virtual void notify() = 0;
};

struct Football : MatchUpdate{ // subject concrete
	const char *highlight;
	Football() : MatchUpdate() {}
	void attach(Participant *o){ observer.push_back(o); }
	void detach(Participant *o){ observer.remove(o); }
	void notify(){ printf("Highlight played: %s\n", highlight); for(Participant *o : observer) o->update(highlight); }
};

struct Player : Participant{ // observer 1
	int motivation;
	Player(){ motivation = 5; }
	void update(const char *message){ if(message == "goal"){ motivation++; } }
};

struct Viewer : Participant{ // observer 2
	int interest;
	Viewer(){ interest = 0; }
	void update(const char *message){
		if(message == "goal"){ interest++; }
		else if(message == "penalty"){ interest--; }
	}
};

int main(int argc, char *argv[]){
	
	// initialisation
	Football *match = new Football();
	Player *player[5];
	Viewer *viewer[5];
	for(int p = 0; p < 5; p++){ player[p] = new Player(); viewer[p] = new Viewer(); }
	
	// client usage
	match->attach(player[0]); // listener attaches
	match->attach(player[1]);
	match->attach(player[2]);
	match->attach(viewer[0]);
	match->highlight = "goal"; // can ignore events
	match->attach(viewer[1]);
	match->attach(viewer[2]);
	match->attach(viewer[3]);
	match->highlight = "goal";
	match->notify(); // event notifies listeners
	match->attach(viewer[4]);
	match->attach(player[3]);
	match->attach(player[4]);
	match->detach(player[0]); // listener detaches
	match->detach(viewer[0]);
	match->highlight = "goal";
	match->notify();
	match->detach(viewer[1]);
	match->highlight = "penalty";
	match->notify();
	match->detach(player[1]);
	match->detach(viewer[4]);
	match->highlight = "goal";
	match->notify();
	
	// output
	printf("Final player motivations: %i", player[0]->motivation);
	for(int p = 1; p < 5; p++){ printf(", %i", player[p]->motivation); }
	printf("\nFinal viewer interests: %i", viewer[0]->interest);
	for(int p = 1; p < 5; p++){ printf(", %i", viewer[p]->interest); }
	
	return 0;
}