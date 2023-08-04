#include <stdio.h> // command line output
#include <stdlib.h> // argument input

struct ToolPower{ // implementation class
	virtual const char* operate(int timeToDo, const char **timeOutcome) = 0;
};

struct JoiningTool{ // base class
	ToolPower *power;
	JoiningTool(ToolPower *p){ power = p; }
	const char* pilot(int timeAvailable, const char **outTime){
		return power->operate(timeAvailable, outTime);
	}
	virtual const char* join(bool isBrittle) = 0;
};

struct FastenerNail : JoiningTool{ // abstraction 1
	FastenerNail(ToolPower *p) : JoiningTool(p) {}
	const char* join(bool isBrittle){ return isBrittle ? "splintered" : "smooth"; }
};

struct FastenerScrew : JoiningTool{ // abstraction 2
	FastenerScrew(ToolPower *p) : JoiningTool(p) {}
	const char* join(bool isBrittle){ return "smooth"; }
};

struct ToolManual : ToolPower{ // implementation 1
	const char* operate(int timeToDo, const char **timeOutcome){
		if(timeToDo < 3) *timeOutcome = "late";
		else *timeOutcome = "on time";
		return "clean";
	}
};

struct ToolElectric : ToolPower{ // implementation 2
	const char* operate(int timeToDo, const char **timeOutcome){
		*timeOutcome =  "on time";
		return "rough";
	}
};

int main(int argc, char *argv[]){
	
	// object permutations
	JoiningTool *hammer = new FastenerNail(new ToolManual());
	JoiningTool *nailgun = new FastenerNail(new ToolElectric());
	JoiningTool *screwdriver = new FastenerScrew(new ToolManual());
	JoiningTool *drill = new FastenerScrew(new ToolElectric());
	
	// instance
	char tool;
	const char *material;
	bool brittleness;
	int timeToDo;
	if(argc >= 5){
		tool = argv[1][0];
		material = argv[2];
		brittleness = (argv[3][0] == 'y' ? true : false);
		timeToDo = atoi(argv[4]);
	}
	else{
		tool = 'h';
		material = "wood";
		brittleness = false;
		timeToDo = 2;
	}
	JoiningTool *currentTool = NULL;
	switch(tool){
		case 'h':
			currentTool = hammer;
			break;
		case 'n':
			currentTool = nailgun;
			break;
		case 's':
			currentTool = screwdriver;
			break;
		case 'd':
			currentTool = drill;
			break;
		default:
			currentTool = hammer;
			break;
		
	}
	
	// usage
	const char *time;
	const char *fit = currentTool->pilot(timeToDo, &time);
	const char *condition = currentTool->join(brittleness);
	printf("Joints of %s have a %s, %s join that was made %s\n", material, condition, fit, time);
	
	return 0;
}