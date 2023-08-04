#include <stdio.h> // command line output

struct ChristmasLight{ // object to clone
	const char *setting;
	ChristmasLight(const char *s){ setting = s; }
};

struct ChristmasTree{
	ChristmasLight *lightSwitch; // original object
	ChristmasLight *light[10]; // shallow prototype clone of object
	const char *lightColour[10];
	ChristmasTree(const char *s, const char **c){
		lightSwitch = new ChristmasLight(s);
		for(int i = 0; i < 10; i++){
			light[i] = lightSwitch; // shared reference to main prototype
			lightColour[i] = c[i]; // independent information for each clone
		}
	}
	void print(){
		printf("Light settings for all lights:\n");
		for(int i = 0; i < 10; i++)
			printf("\tlight %i: %s %s\n", i + 1, light[i]->setting, lightColour[i]);
	}
	~ChristmasTree(){ delete lightSwitch; }
};

int main(int argc, char *argv[]){
	const char *colours[10] = {
		"Red", "Blue", "White", "Blue", "Red", 
		"White", "Green", "White", "Red", "Green"};
	ChristmasTree *tree = new ChristmasTree("Bright", colours);
	tree->print();
	tree->lightSwitch->setting = "Blinking";
	tree->print();
	tree->lightSwitch->setting = "Static";
	tree->print();
	tree->lightSwitch->setting = "Dim";
	tree->print();
	tree->lightSwitch->setting = "Fading";
	tree->print();
	delete tree;
	return 0;
}