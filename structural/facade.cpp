#include <stdio.h> // command line output

struct Cafetiere{
	const char *bean;
	bool isInstant;
	void load(float scoops){ printf("cckkk"); isInstant = true; }
	void grind(){ printf("krkrk"); isInstant = false; }
	void press(){ printf("pfsst"); }
	void print(){ printf("%s coffee %s", bean, isInstant ? "grains" : "beans"); }
};

struct Kettle{
	const char *water;
	void heat(float temperature){ printf("blblb"); }
	void pour(float proportion){ printf("pdlll"); }
	void print(){ printf("%s water", water); }
};

struct MilkFrother{
	const char *milk;
	void fill(float proportion){ printf("scooo"); }
	void froth(float steamToFoam){ printf("pfpfp"); if(steamToFoam > .2f) printf("fffff"); }
	void pour(){ printf("hhwhf"); }
	void clean(){ printf("rrbrr"); }
	void print(){ printf("%s milk", milk); }
};

struct Barista{ // facade
	Cafetiere cafe;
	Kettle kettle;
	MilkFrother frother;
	void cappuccino(const char *b, const char *m){
		cafe.bean = b;
		cafe.load(2);
		cafe.grind();
		cafe.press();
		frother.milk = m;
		frother.fill(.3f);
		frother.froth(.5f);
		frother.pour();
		frother.clean();
		printf("\nMade a cappuccino with "); cafe.print(); printf(" and "); frother.print(); printf("\n");
	}
	void latte(const char *b, const char *m){
		cafe.bean = b;
		cafe.load(1);
		cafe.grind();
		cafe.press();
		frother.milk = m;
		frother.fill(.4f);
		frother.froth(.3f);
		frother.pour();
		frother.clean();
		printf("\nMade a latte with "); cafe.print(); printf(" and "); frother.print(); printf("\n");
	}
	void flatWhite(const char *b, const char *m){
		cafe.bean = b;
		cafe.load(1);
		cafe.grind();
		cafe.press();
		frother.milk = m;
		frother.fill(.6f);
		frother.froth(.0f);
		frother.pour();
		frother.clean();
		printf("\nMade a flat white with "); cafe.print(); printf(" and "); frother.print(); printf("\n");
	}
	void black(const char *b, float amount){
		cafe.bean = b;
		cafe.load(amount);
		cafe.grind();
		cafe.press();
		const char *name = amount >= 2.f ? "doppio" : "espresso";
		printf("\nMade a %s with ", name); cafe.print(); printf("\n");
	}
	void americano(const char *b, const char *w){
		cafe.bean = b;
		cafe.load(1);
		cafe.grind();
		cafe.press();
		kettle.water = w;
		kettle.heat(93.f);
		kettle.pour(.6f);
		printf("\nMade an americano with "); cafe.print(); printf(" and "); kettle.print(); printf("\n"); 
	}
	void instant(const char *b, const char *w){
		cafe.bean = b;
		cafe.load(.2f);
		cafe.press();
		kettle.water = w;
		kettle.heat(104.f);
		kettle.pour(1.f);
		printf("\nMade an instant with "); cafe.print(); printf(" and "); kettle.print(); printf("\n");
	}
};

int main(int argc, char *argv[]){
	Barista barista;
	barista.cappuccino("Starbucks", "cow");
	barista.black("Costa", 2);
	barista.americano("Dunkin Donuts", "distilled");
	barista.flatWhite("McCafe", "coconut");
	barista.latte("Tim Hortons", "soy");
	barista.instant("Nescafe", "tap");
	return 0;
}