#include <stdio.h> // command line output

struct Focus;
struct FocusBuy;
struct FocusSell;

struct Company{ // context
	int stock, price, money; // data
	Focus *focus;
	Company();
	void changeFocus(Focus *f);
};

struct Focus{ // state interface
	Company *company;
	virtual void business() = 0; // handle
};

struct FocusBuy : Focus{ // state 1
	void business();
};

struct FocusSell : Focus{ // state 2
	void business();
};

Company::Company(){ stock = 0; price = 5; money = 50; changeFocus(new FocusBuy()); }

void Company::changeFocus(Focus *f){ focus = f; focus->company = this; printf("Switching focus at %i money and %i price\n", money, price); }

void FocusBuy::business(){
	if(company->money < company->price * 10){
		printf("Out of money: start selling stock... ");
		company->changeFocus(new FocusSell());
		delete this;
	}
	else{ company->stock += 10; company->money -= company->price * 10; }
}

void FocusSell::business(){
	if(company->stock < 10){
		printf("Out of stock: start buying stock... ");
		company->changeFocus(new FocusBuy());
		delete this;
	}
	else{ company->stock -= 10; company->money += company->price * 10; }
}

int main(int argc, char *argv[]){ // client usage
	Company retail = Company();
	printf("Money before: %i\n", retail.money);
	printf("Normal business...\n"); retail.focus->business(); retail.focus->business(); retail.focus->business(); retail.focus->business(); // automatic state changes
	printf("Money now: %i\n", retail.money);
	printf("Opportunistic business...\n"); // external state changes
		retail.price = 1; retail.changeFocus(new FocusBuy()); retail.focus->business();
		retail.price = 10; retail.changeFocus(new FocusSell()); retail.focus->business();
	printf("Money after: %i\n", retail.money);
	return 0;
}