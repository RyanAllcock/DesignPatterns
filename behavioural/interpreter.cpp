#include <iostream> // command line output

struct Expression{ // expression
	virtual int interpret(int *var) = 0; // interpret using each expression's language-based inference
};

struct Literal : Expression{ // terminal 1 "x"
	int value;
	Literal(int v){ value = v; }
	int interpret(int *var){ return value; }
};

struct Variable : Expression{ // terminal 2 "a"
	int interpret(int *var){ return *var; }
};

struct Add : Expression{ // non-terminal 1 "a+b"
	Expression *augend;
	Expression *addend;
	Add(Expression *e1, Expression *e2){ augend = e1; addend = e2; }
	int interpret(int *var){ return augend->interpret(var) + addend->interpret(var); }
};

struct Assign : Expression{ // non-terminal 2 "a=b c"
	Expression *value;
	Expression *next;
	Assign(Expression *v, Expression *n){ value = v; next = n; }
	int interpret(int *var){ *var = value->interpret(var); return next->interpret(var); }
};

struct Ternary : Expression{ // non-terminal 3 "a?b:c"
	Expression *condition;
	Expression *pass;
	Expression *fail;
	Ternary(Expression *c, Expression *p, Expression *f){ condition = c; pass = p; fail = f; }
	int interpret(int *var){ if(condition->interpret(var)) return pass->interpret(var); return fail->interpret(var); }
};

int main(int argc, char *argv[]){
	
	// initialisation
	const char *sentence1 = "2+3"; // produces no-context expression of numerical notation for a calculator
	const char *sentence2 = "v=3 3+v+2"; // produces context-altering expression for a state-machine
	const char *sentence3 = "v?v+v+2:v"; // produces runtime-non-deterministic context-reliant expression for an interpreter
	int variable = 0; // context and respective expressions for sentences... 
	Expression *expression1 = new Add(new Literal(2), new Literal(3));
	Expression *expression2 = new Assign(new Literal(3), new Add(new Literal(3), new Add(new Variable(), new Literal(2))));
	Expression *expression3 = new Ternary(new Variable(), new Add(new Variable(), new Add(new Variable(), new Literal(2))), new Variable());
	
	// client usage
	std::cout << "Sentence " << sentence1 << " variable " << variable << " produces output " << expression1->interpret(&variable) << " variable " << variable << "\n";
	std::cout << "Sentence " << sentence2 << " variable " << variable << " produces output " << expression2->interpret(&variable) << " variable " << variable << "\n";
	std::cout << "Sentence " << sentence3 << " variable " << variable << " produces output " << expression3->interpret(&variable) << " variable " << variable << "\n";
	
	return 0;
}