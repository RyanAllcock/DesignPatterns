#include <stdio.h> // command line output
#include <string.h> // string comparisons

struct Phrase{ // flyweight
	const char *words;
	int popularity;
	Phrase(const char *w){ words = w; popularity = 0; }
	Phrase(const char *w, int p){ words = w; popularity = p; }
};

struct Lexicon{ // factory
	int size;
	Phrase *phrase[3];
	Lexicon(){ size = 0; }
	Phrase* add(Phrase *p){ phrase[size++] = p; return p; } // store objects on-demand
	Phrase* recall(const char *w){
		for(int p = 0; p < size; p++){ // check if exists
			if(!strcmp(phrase[p]->words, w))
				return phrase[p];
		}
		return add(new Phrase(w)); // create objects when needed
	}
};

int main(int argc, char *argv[]){
	const char *knownPhrase = "two birds with one stone";
	const char *unknownPhrase = "bird in the hand worth two in the bush";
	
	// initialisation
	Lexicon *phrases = new Lexicon();
	phrases->add(new Phrase(knownPhrase, 5));
	
	// client usage
	Phrase *checkPhrase;
	printf("%s has a popularity of %i\n", knownPhrase, phrases->recall(knownPhrase)->popularity);
	printf("%s has a popularity of %i\n", unknownPhrase, phrases->recall(unknownPhrase)->popularity);
	return 0;
}
















