#include <stdio.h> // command line output

struct Robot{ // retriever
	int x, y, dx, dy; // data
	Robot(){ x = 5; y = 5; dx = 1; dy = 0; printf("Robot placed at position [%i,%i] facing direction [right]\n", x, y); }
	void move(){ x += dx; y += dy; }
	void turn(int d){ int t = dx; dx = dy * d; dy = t * d * -1; }
};

struct Command{ // command interface
	virtual void execute() = 0; // operation execution
};

struct MoveForward : Command{ // command 1
	Robot *robot;
	MoveForward(Robot *r){ robot = r; } // retriever access
	void execute(){ robot->move(); }
};

struct Turn : Command{ // command 2
	Robot *robot;
	int direction;
	Turn(Robot *r, int d){ robot = r; direction = d;} // operation input
	void execute(){ robot->turn(direction); }
};

int main(int argc, char *argv[]){ // client usage
	
	// initialisation
	Robot *robot = new Robot();
	
	// command preparation
	Command *path[10];
	path[0] = new MoveForward(robot);
	path[1] = new Turn(robot, -1);
	path[2] = new MoveForward(robot);
	path[3] = new MoveForward(robot);
	path[4] = new Turn(robot, 1);
	path[5] = new Turn(robot, 1);
	path[6] = new MoveForward(robot);
	path[7] = new MoveForward(robot);
	path[8] = new MoveForward(robot);
	path[9] = new Turn(robot, 1);
	
	// command execution
	for(int c = 0; c < 10; c++) path[c]->execute();
	
	// print final outcome
	const char *dir[4] = { "left", "right", "down", "up" };
	printf("Robot finished at position [%i,%i] facing direction [%s]\n", robot->x, robot->y, dir[(robot->dx + 1) / 2 + (robot->dy + 1) / 2 + robot->dy * robot->dy * 2]);
	
	return 0;
}