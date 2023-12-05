#include <iostream> // command line output
#include <string> // message navigation

struct Messenger{ // base class
	virtual std::string send(std::string msg){
		msg.insert(0, "Message sent: ");
		return msg;
	}
};

struct MessageEncoder : Messenger{ // decorator class
	Messenger *messenger;
	MessageEncoder(Messenger *m){ messenger = m; }
	Messenger* get(){ return messenger; }
};

struct MessageCaesar : MessageEncoder{ // decorator 1
	MessageCaesar(Messenger *m) : MessageEncoder(m) {}
	std::string send(std::string msg){ // converts incoming data
		for(int c = 0; c < msg.size(); c++)
			msg[c] = (char)((int)((msg[c] - 'a') - 3) % 26) + 'a';
		return get()->send(msg);
	}
};

struct MessageMono : MessageEncoder{ // decorator 2
	const char *code;
	MessageMono(Messenger *m, const char *c) : MessageEncoder(m) { code = c; }
	std::string send(std::string msg){ // converts using passed information
		for(int c = 0; c < msg.size(); c++)
			msg[c] = code[(int)(msg[c] - 'a')];
		return get()->send(msg);
	}
};

struct MessageName : MessageEncoder{ // decorator 3
	const char *name;
	MessageName(Messenger *m, const char *n) : MessageEncoder(m) { name = n; }
	std::string send(std::string msg){ // processes data in different decorating order
		msg = get()->send(msg);
		msg.append(": Sent by ");
		msg.append(name);
		return msg;
	}
};

int main(int argc, char *argv[]){
	Messenger *messenger = new Messenger();
	const char *code = "qwertyuiopasdfghjklzxcvbnm";
	const char *name = "the sender";
	Messenger *encoder = new MessageName(new MessageMono(new MessageCaesar(messenger), code), name);
	std::string msg1 = "hello";
	std::cout << messenger->send(msg1) << "\n";
	std::string msg2 = "hello";
	std::cout << encoder->send(msg2) << "\n";
	return 0;
}








































// struct Meat{ // base class
// 	virtual void make(){
// 		printf("Meat cooked\n");
// 	}
// };

// struct MeatPreparer{ // decorator class
// 	Meat *meat;
// 	MeatPreparer(Meat *m){ meat = m; }
// 	Meat* get(){ return meat; }
// };

// struct MeatTenderiser{ // decorator 1
// 	const char *
// 	MeatTenderiser(Meat *m, float choice) : MeatPreparer(m) {}
// 	void make(){
// 		get()->make();
// 	}
// };

// struct MeatSausager{ // decorator 2
	
// };



























// struct Recipe{ // base class
	
// 	virtual void 
// }

// struct RecipeStep{ // decorator base
// 	Meal *meal;
// 	RecipeStep(Meal *m){ meal = m; }
// 	Meal* get(){ return meal; }
// }

// struct StepSandwich : RecipeStep{ // decorator 1
// 	StepSandwich(){}
// 	const char *bread;
// }

// struct StepMeat : RecipeStep{ // decorator 2
// 	StepMeat(){}
// 	float mass;
// }