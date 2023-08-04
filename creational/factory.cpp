#include <stdio.h> // command line output
#include <stdlib.h> // argument input

#define PI 3.1415

struct Shape{ // abstract
	float perimeter = 0;
	virtual float getArea(){ return 0; }
	virtual void setPerimeter() = 0;
};

struct Circle : Shape{ // concrete 1
	float radius;
	Circle(float r){ radius = r; }
	float getArea(){ return PI * radius * radius; }
	void setPerimeter(){ perimeter = 2.f * PI * radius; }
};

struct Square : Shape{ // concrete 2
	float width, height;
	Square(float w){ width = height = w; }
	float getArea(){ return width * height; }
	void setPerimeter(){ perimeter = 2.f * (width + height); }
};

struct ShapeCreator{ // non-abstract factory
	static Shape* make(char id, float s){
		Shape *newShape = NULL;
		switch(id){ // determine concrete instance
			case 'c': newShape = new Circle(s); break;
			case 's': newShape = new Square(s); break;
			default: newShape = new Square(1); break;
		}
		newShape->setPerimeter(); // finish processing instance
		return newShape;
	}
};

int main(int argc, char *argv[]){
	for(int i = 2; i < argc; i += 2){
		Shape *shape = ShapeCreator::make((char)argv[i - 1][0], atof(argv[i]));
		printf("Input shape %i area: %f, perimeter: %f\n", i / 2, shape->getArea(), shape->perimeter);
		delete shape;
	}
	
	Shape *shape1, *shape2;
	shape1 = ShapeCreator::make('c', 1.5f);
	shape2 = ShapeCreator::make('s', 3);
	printf("Shape 1 area: %f, perimeter: %f\n", shape1->getArea(), shape1->perimeter);
	printf("Shape 2 area: %f, perimeter: %f\n", shape2->getArea(), shape2->perimeter);
	delete shape1;
	delete shape2;
	return 0;
}