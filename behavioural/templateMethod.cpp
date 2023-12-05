#include <iostream> // command line output
#include <string> // word manipulation

struct WordGame{ // abstract class
	virtual void welcome() = 0; // initialisation primitive
	virtual bool gameOver() = 0; // termination primitive
	virtual bool guess() = 0; // conditional primitive
	virtual void congratulate() = 0; // logic primitive 1
	virtual void penalty() = 0; // logic primitive 2
	std::string word; // context/data
	WordGame(const char *w){ word = w; }
	void play(){ // template method
		welcome();
		while(!gameOver()){
			if(guess()) congratulate();
			else penalty();
		}
	}
};

struct Hangman : WordGame{ // concrete class 1
	int sticks;
	std::string midword;
	Hangman(const char *w) : WordGame(w) { sticks = 0; midword = word; for(int i = 0; i < midword.size(); i++) midword[i] = '_'; }
	void welcome(){ std::cout << "Welcome to Hangman\n"; }
	bool gameOver(){
		if(sticks >= 6){
			std::cout << "Stickman complete: You Lose\n";
			return true;
		}
		else if(!word.compare(midword)){
			std::cout << "Word complete: You Win\n";
			return true;
		}
		return false;
	}
	bool guess(){
		char c;
		std::cin.get(c);
		if(c == '\n') return true;
		else if(word.find(c) < word.size()){
			for(int i = 0; i < word.size(); i++){
				if(word[i] == c) midword[i] = word[i];
			}
			std::cout << "Character " << c << " found, word guessed so far: " << midword << "\n";
			return true;
		}
		std::cout << "Character " << c << " not found, adding stick\n";
		return false;
	}
	void congratulate(){}
	void penalty(){ sticks++; }
};

struct GuessTheWord : WordGame{ // concrete class 2
	int tries;
	bool won;
	GuessTheWord(const char *w) : WordGame(w) { tries = 3; won = false; }
	void welcome(){ std::cout << "Guess the word\n"; }
	bool gameOver(){ 
		if(tries <= 0){
			std::cout << "Out of guesses: You Lose\n";
			return true;
		}
		return won;
	}
	bool guess(){ std::string s; std::cin >> s; return !word.compare(s); }
	void congratulate(){ std::cout << "Correct guess: You Win\n"; won = true; }
	void penalty(){ std::cout << "Incorrect guess\n"; tries--; }
};

int main(int argc, char *argv[]){
	
	// initialisation
	Hangman *hangman;
	GuessTheWord *guessword;
	if(argc != 3){
		hangman = new Hangman("hangman");
		guessword = new GuessTheWord("guess");
	}
	else{
		hangman = new Hangman(argv[1]);
		guessword = new GuessTheWord(argv[2]);
	}
	
	// client usage
	hangman->play();
	guessword->play();
	
	delete hangman;
	delete guessword;
	return 0;
}