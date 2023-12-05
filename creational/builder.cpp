#include <stdio.h> // command line output
#include <stdlib.h> // argument input

struct BuilderNumber{ // abstract producer
	virtual int task1(int data, int in){ return 0; }
	virtual int task2(int data, int in){ return 0; }
};

struct BuilderAdd : BuilderNumber{ // concrete 1
	int task1(int data, int in){ return data + in; }
	int task2(int data, int in){ return data - in; }
};

struct BuilderMultiply : BuilderNumber{ // concrete 2
	int task1(int data, int in){ return data * in; }
	int task2(int data, int in){ return data / in; }
};

struct DirectorNumber{ // abstract composer
	int data;
	DirectorNumber(int i){ data = i; }
	int construct(BuilderNumber *b){
		int dataMid = b->task1(data, data / 2);
		data = b->task2(dataMid, data / 4);
		return data;
	}
};

int main(int argc, char *argv[]){
	
	// argument input
	for(int i = 2; i < argc; i += 2){
		char build = (char)argv[i - 1][0];
		int value = atoi(argv[i]);
		BuilderNumber *builder = NULL;
		switch(build){
			case 'a': builder = new BuilderAdd(); break;
			case 'm': builder = new BuilderMultiply(); break;
			default: builder = new BuilderAdd(); break;
		}
		DirectorNumber *director = new DirectorNumber(value);
		int output = director->construct(builder);
		printf("Input data %i: value %i produced %i\n", i / 2, value, output);
		delete director;
		delete builder;
	}
	
	// initialisation
	int value = 10;
	BuilderNumber *builder = new BuilderMultiply();
	DirectorNumber *director = new DirectorNumber(value);
	
	// client usage
	int output = director->construct(builder);
	printf("Value %i produced %i\n", value, output);
	
	delete director;
	delete builder;
	return 0;
}