#include <stdio.h> // command line output
#include <string.h> // message navigation

struct Messenger{ // base class
	virtual char* send(char *msg){
		const char *msgAdd = "Message sent: ";
		int msgSize = strlen(msgAdd);
		for(int c = 0; c < msgSize; c++){
			msg[c + msgSize] = msg[c];
			msg[c] = msgAdd[c];
		}
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
	char* send(char *msg){ // converts incoming data
		for(int c = 0; msg[c] != '\0'; c++)
			msg[c] = (char)((int)((msg[c] - 'a') - 3) % 26) + 'a';
		return get()->send(msg);
	}
};

struct MessageMono : MessageEncoder{ // decorator 2
	const char *code;
	MessageMono(Messenger *m, const char *c) : MessageEncoder(m) { code = c; }
	char* send(char *msg){ // converts using passed information
		for(int c = 0; msg[c] != '\0'; c++)
			msg[c] = code[(int)(msg[c] - 'a')];
		return get()->send(msg);
	}
};

struct MessageName : MessageEncoder{ // decorator 3
	const char *name;
	MessageName(Messenger *m, const char *n) : MessageEncoder(m) { name = n; }
	char* send(char *msg){ // processes data in different decorating order
		get()->send(msg);
		const char *msgAdd = ": Sent by ";
		int oldSize = strlen(msg);
		int msgSize = strlen(msgAdd);
		int nameSize = strlen(name);
		for(int c = 0; c < msgSize; c++) msg[c + oldSize] = msgAdd[c];
		for(int c = 0; c < nameSize; c++) msg[c + oldSize + msgSize] = name[c];
		msg[oldSize + msgSize + nameSize] = '\0';
		return msg;
	}
};

int main(int argc, char *argv[]){
	Messenger *messenger = new Messenger();
	const char *code = "qwertyuiopasdfghjklzxcvbnm";
	const char *name = "the sender";
	Messenger *encoder = new MessageName(new MessageMono(new MessageCaesar(messenger), code), name);
	char msg1[30] = "hello";
	printf("%s\n", messenger->send((char*)&msg1));
	char msg2[30] = "hello";
	printf("%s\n", encoder->send((char*)&msg2));
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