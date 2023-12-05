#include <iostream> // command line output

struct ChristmasLight{ // object to clone
	std::string setting;
	ChristmasLight(){ setting = "off"; }
	ChristmasLight(std::string s){ setting = s; }
};

struct ChristmasTree{
	ChristmasLight lightSwitch; // original object
	ChristmasLight light[10]; // shallow prototype clone of object
	std::string lightColour[10];
	ChristmasTree(){ for(int i = 0; i < 10; i++) lightColour[i] = "Black"; }
	ChristmasTree(std::string s, std::string c[10]){
		lightSwitch = ChristmasLight(s);
		for(int i = 0; i < 10; i++){
			light[i] = lightSwitch; // shared reference to main prototype
			lightColour[i] = c[i]; // independent information for each clone
		}
	}
	void print(){
		std::cout << "Light settings for all lights:\n";
		for(int i = 0; i < 10; i++)
			std::cout << "\tlight " << i + 1 << ": " << light[i].setting << " " << lightColour[i] << "\n";
	}
};

int main(int argc, char *argv[]){
	
	// initialisation
	std::string colours[10] = {
		"Red", "Blue", "White", "Blue", "Red", 
		"White", "Green", "White", "Red", "Green"};
	ChristmasTree tree("Bright", colours);
	
	// client usage
	tree.print();
	tree.lightSwitch.setting = "Blinking";
	tree.print();
	tree.lightSwitch.setting = "Static";
	tree.print();
	tree.lightSwitch.setting = "Dim";
	tree.print();
	tree.lightSwitch.setting = "Fading";
	tree.print();
	
	return 0;
}