#include "Board.h"

void Board::create_board2() {

	BlankPiece blank;

	for(int i = 0; i < 16; i++) {
		for(int j = 0; j < 16; j++) {
			board2[i][j] = blank;
		}
	}
}


void Board::setPiece(Tetris_Shape &shape) {
	int startpos = 7;
	int rowPost = 0;
	shape.isFalling = true;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 2; j++) {
			if(shape.layout[i][j]==1){
				board2[rowPost][startpos] = shape;
				startpos++;
			}	
		}

		if(board2[rowPost][startpos].filled == true || board2[rowPost][startpos-1].filled == true) {
			rowPost++;
		}

		startpos=7;
	}
}

