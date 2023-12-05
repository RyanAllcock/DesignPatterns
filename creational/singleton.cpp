#include <iostream>  // command line output

struct Gossip{
	static Gossip* get(){ // one static instance
		static Gossip instance;
		return &instance;
	}
	static std::string listen(){ return get()->message; }
	static void tell(std::string m){ get()->message = m; }
private:
	std::string message;
	Gossip(){ message = "Nothing to tell"; }
};

int main(int argc, char *argv[]){ // client usage: chinese whispers
	{ // event 1
		std::cout << "Message: " << Gossip::listen() << "\n"; // retrieve
		Gossip::tell("Something to tell"); // update
	}
	{ // event 2
		std::cout << "Message: " << Gossip::listen() << "\n";
		Gossip::tell("Something else to tell");
	}
	
	return 0;
}