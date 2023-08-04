#include <stdio.h>  // command line output

struct Gossip{
	static Gossip* get(){ // one static instance
		static Gossip instance;
		return &instance;
	}
	static const char* listen(){ return get()->message; }
	static void tell(const char *m){ get()->message = m; }
private:
	const char *message;
	Gossip(){ message = "Nothing to tell"; }
};

int main(int argc, char *argv[]){ // calculating chinese whispers
	{ // event 1
		printf("Message: %s\n", Gossip::listen()); // retrieve
		Gossip::tell("Something to tell"); // update
	}{ // event 2
		printf("Message: %s\n", Gossip::listen());
		Gossip::tell("Something else to tell");
	}
	return 0;
}