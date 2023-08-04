#include <stdio.h> // command line output

struct Chessboard{ // adaptee original
	char piece[8 * 8]; // data
	Chessboard(){
		char layout[8 * 8] = {
			'r', 'k', 'b', 'q', 'k', 'b', 'k', 't', 
			'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 
			'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 
			'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 
			'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 
			'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 
			'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 
			'R', 'K', 'B', 'Q', 'K', 'B', 'K', 'R'};
		for(int i = 0; i < 8 * 8; i++) piece[i] = layout[i];
	}
	char pieceAtPosition(int x, int y){ // method
		if(x >= 0 && x < 8 && y >= 0 && y < 8)
			return piece[x + y * 8];
		return '\0';
	}
};

struct ChessboardAdapter{ // adaptor alternative
	Chessboard *board; // interact with adaptee
	ChessboardAdapter(Chessboard *b){ board = b; }
	char pieceAtCoordinate(char col, char row){ // enable algebraic notation
		int x, y;
		if(col >= 'a' && col <= 'h')
			x = (int)(col - 'a');
		else if(col >= 'A' && col <= 'H')
			x = (int)(col - 'A');
		else x = -1;
		y = 8 - (int)(row - '0');
		return board->pieceAtPosition(x, y);
	}
};

int main(int argc, char *argv[]){
	Chessboard *board = new Chessboard(); // original usage
	ChessboardAdapter *adapter = new ChessboardAdapter(board); // client usage
	printf("Piece at [%i,%i]: %c\n", 2, 7, board->pieceAtPosition(2, 7)); // legacy method unfit for desired usage
	printf("Piece at [%c,%c]: %c\n", 'C', '1', adapter->pieceAtCoordinate('C', '1')); // adaptor suitable for client's intended usage
	return 0;
}