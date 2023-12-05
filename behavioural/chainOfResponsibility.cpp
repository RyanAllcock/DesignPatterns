#include <iostream> // command line output
#include <string> // string manipulation

struct TagHandler{ // receiver interface
	TagHandler *successor;
	TagHandler(){ successor = NULL; }
	virtual int scan(std::string m){ if(successor != NULL && m.size() > 0) return successor->scan(m); else return -1; } // request
};

struct AddHandler : TagHandler{ // output receiver
	AddHandler(TagHandler *s){ successor = s; }
	int scan(std::string m){
		std::string next = m.substr(0, m.size() - 1);
		if(m.find("+") != std::string::npos) return TagHandler::scan(next) + 5;
		return TagHandler::scan(next);
	}
};

struct PrintHandler : TagHandler{ // data receiver
	std::string tag;
	PrintHandler(std::string t, TagHandler *s){ tag = t; successor = s; }
	int scan(std::string m){
		int t = 0;
		for(int p = 0; (p = m.find(tag, p)) != std::string::npos; t++, p++);
		std::cout << "found " << tag << " " << t << " times\n";
		return TagHandler::scan(m.substr(0, m.size() - 1));
	}
};

struct StopHandler : TagHandler{ // halting receiver
	StopHandler(TagHandler *s){ successor = s; }
	int scan(std::string m){
		if(m.find("x") != std::string::npos){ std::cout << "quitting\n"; return 1; }
		return TagHandler::scan(m.substr(0, m.size() - 1));
	}
};

int main(int argc, char *argv[]){
	
	// initialisation
	TagHandler *chain = new PrintHandler("h", new StopHandler(new AddHandler(NULL)));
	
	// client usage
	int scan;
	scan = chain->scan("hh+hx");
	std::cout << "hh+hx" << " produced " << scan << "\n";
	scan = chain->scan("h++xh");
	std::cout << "h++xh" << " produced " << scan << "\n";
	
	return 0;
}