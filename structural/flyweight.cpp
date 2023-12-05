#include <stdio.h> // command line output
#include <string.h> // string comparisons
#include <list> // flyweight storage
#include <algorithm> // flyweight search

struct Phrase{ // flyweight interface
	const char *words; // extrinsic state
	virtual const char* response() = 0; // operation
};

struct Meme : Phrase{
	int popularity; // intrinsic state
	Meme(const char *w, int p){ words = w; popularity = p; }
	const char* response(){ popularity++; if(popularity > 3) return "I get it"; else return "I don't get it"; }
};

struct Lexicon{ // flyweight factory
	std::list<Phrase*> phrase;
	Lexicon(){ phrase = {}; }
	Phrase* add(Phrase *p){ phrase.push_back(p); return p; } // store objects on-demand
	Phrase* recall(const char *key){ // get flyweight
		std::list<Phrase*>::iterator pi = std::find_if(phrase.begin(), phrase.end(), [&](const Phrase *p){ return !strcmp(key, p->words); }); // check if exists
		if(pi == phrase.end()) return add(new Meme(key, 0)); // create objects when needed
		return *pi;
	}
};

int main(int argc, char *argv[]){
	const char *knownPhrase = "two birds with one stone";
	const char *unknownPhrase = "bird in the hand worth two in the bush";
	const char *randomPhrase = "birds fly into sliding doors";
	
	// initialisation
	Lexicon phrases = Lexicon();
	phrases.add(new Meme(knownPhrase, 5));
	phrases.add(new Meme(unknownPhrase, 1));
	
	// client usage
	printf("Said: %s, Response: %s\n", knownPhrase, phrases.recall(knownPhrase)->response()); // shared invariable non-contextual phrase, hidden variable contextual popularity
	printf("Said: %s, Response: %s\n", unknownPhrase, phrases.recall(unknownPhrase)->response()); // alternative response based on intrinsic state
	printf("Said: %s, Response: %s\n", randomPhrase, phrases.recall(randomPhrase)->response()); // new flyweight generated & added upon unsuccessful search
	
	return 0;
}