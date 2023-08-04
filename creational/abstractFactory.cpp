#include <stdio.h> // command line output
#include <stdlib.h> // argument input
#include <math.h> // circle perimeter

#define PI 3.1415 // circle area

struct Shape{ // abstract
	float perimeter = 0; // variable
	virtual float getArea(){ return 0; } // processing method -> called mid-program
	virtual void setPerimeter() = 0; // initialisation method -> called after contruction
};

struct ShapeEquil : Shape{ // abstract 1
	float width;
};

struct ShapeLong : Shape{ // abstract 2
	float length, width;
};

struct Circle : ShapeEquil{ // concrete 1-1
	Circle(float d){ width = d; }
	float getArea(){ return PI * width * width / 4.f; }
	void setPerimeter(){ perimeter = PI * width; }
};

struct Square : ShapeEquil{ // concrete 1-2
	Square(float w){ width = w; }
	float getArea(){ return width * width; }
	void setPerimeter(){ perimeter = 4.f * width; }
};

struct Ellipse : ShapeLong{ // concrete 2-1
	Ellipse(float dHi, float dLo){ length = dHi; width = dLo; }
	float getArea(){ return PI * length * width / 4.f; }
	void setPerimeter(){ perimeter = PI * sqrt((length * length + width * width) / 2.f); }
};

struct Rectangle : ShapeLong{ // concrete 2-2
	Rectangle(float h, float w){ length = h; width = w; }
	float getArea(){ return length * width; }
	void setPerimeter(){ perimeter = 2.f * (length + width); }
};

struct CreatorShape{ // abstract factory
	virtual Shape* makeEquil(float s){ return new Square(1); } // set & finish processing product 1
	virtual Shape* makeLong(float s1, float s2){ return new Rectangle(1, 2); } // set & finish processing product 2
};

struct CreatorRound : CreatorShape{ // concrete factory 1
	Shape* makeEquil(float s){
		Shape *newShape = new Circle(s);
		newShape->setPerimeter();
		return newShape;
	}
	Shape* makeLong(float s1, float s2){
		Shape *newShape = new Ellipse(s1, s2);
		newShape->setPerimeter();
		return newShape;
	}
};

struct CreatorSharp : CreatorShape{ // concrete factory 2
	Shape* makeEquil(float s){
		Shape *newShape = new Square(s);
		newShape->setPerimeter();
		return newShape;
	}
	Shape* makeLong(float s1, float s2){
		Shape *newShape = new Rectangle(s1, s2);
		newShape->setPerimeter();
		return newShape;
	}
};

int main(int argc, char *argv[]){
	for(int i = 3; i < argc; i += 3){
		char typeCreator = (char)argv[i - 2][0];
		char typeProduct = atoi(argv[i - 1]);
		float value = atof(argv[i]);
		CreatorShape *creator = NULL;
		switch(typeCreator){ // determine concrete factory
			case 'r': creator = new CreatorRound(); break;
			case 's': creator = new CreatorSharp(); break;
			default: creator = new CreatorSharp(); value = 1; break;
		}
		Shape *shape = NULL;
		switch(typeProduct){ // determine concrete product
			case 1: shape = creator->makeEquil(value); break;
			case 2: shape = creator->makeLong(value, value / 2.f); break;
			default: shape = creator->makeEquil(1); break;
		}
		printf("Input shape %i area: %f, perimeter: %f\n", i / 3, shape->getArea(), shape->perimeter);
		delete creator;
		delete shape;
	}
	return 0;
}