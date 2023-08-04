#include <stdio.h> // command line output
#include <string.h> // string comparisons

struct Library{ // interface
	virtual const char* fetchBookByTopic(const char *topic) = 0;
};

struct Shelf : Library{ // base class
	const char* fetchBookByTopic(const char *topic){
		if(!strcmp(topic, "gossip")) return "Magazines: nothing of value at all";
		else if(!strcmp(topic, "science")) return "Papers: making weird shapes with maths";
		else if(!strcmp(topic, "secret plans")) return "Terrible Plans: the cover-up";
		else if(!strcmp(topic, "military")) return "Schematics: how to build a tank";
		else return "there're no books in that topic";
	}
};

struct Keeper : Library{ // proxy
	Shelf *shelf;
	Keeper(Shelf *s){ shelf = s; }
	const char* fetchBookByTopic(const char *topic){
		if(!strcmp(topic, "secret plans")) return "Everything's Fine: the documentary"; // dummy subversion
		else if(!strcmp(topic, "military")) return "you shouldn't be reading that"; // error
		else return shelf->fetchBookByTopic(topic); // default
	}
};

int main(int argc, char *argv[]){ // client
	Library *library = new Shelf(); // normal access
	printf("Fetching %s book from shelf: %s\n", "science", library->fetchBookByTopic("science"));
	printf("Fetching %s book from shelf: %s\n", "secret plans", library->fetchBookByTopic("secret plans"));
	printf("Fetching %s book from shelf: %s\n", "military", library->fetchBookByTopic("military"));
	delete library;
	library = new Keeper(new Shelf()); // proxy access
	printf("Fetching %s book from book keeper: %s\n", "science", library->fetchBookByTopic("science"));
	printf("Fetching %s book from book keeper: %s\n", "secret plans", library->fetchBookByTopic("secret plans"));
	printf("Fetching %s book from book keeper: %s\n", "military", library->fetchBookByTopic("military"));
	delete library;
	return 0;
}