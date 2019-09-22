//
//  main.cpp
//  chessAI
//
//  Created by Davide Fassio on 19/09/2019.
//  Copyright © 2019 Davide Fassio. All rights reserved.
//

/*
 
 To run in the terminal for a better use go in the directory:
    Desktop/Programmazione/C++/chessAI/chessAI
 
 Then write this 2 commands:
    g++ main.cpp -w -o chessAI
    ./chessAI
 
 */

#include <iostream>
#include "chess.h"
using namespace std;


int main(int argc, const char * argv[]) {
    Board board;
    
    // board.displayBoard_terminal();
    board.displayBoard_console();
    cout << "################################" << endl << endl;

    
    int turn = 1; //  Start the white
    
    while(true){
        char move[6];
        
        (board.isCheck(board.board, turn) == 1) ? cout << "You are under check" << endl: cout << "No checks" << endl;
        
        (turn == 1) ? cout << "White to move: " : cout << "Black to move: ";
        cin >> move;
        
        board.move(board.board, move, 0, turn, board.captured_enpasant, board.castling_rights);
        turn = turn == 1 ? 0 : 1; // Change the move from white to black and viceversa
        
        cout << "Board evaluation: " <<board.evaluate(board.board) << endl;
        
        // board.displayBoard_terminal();
        board.displayBoard_console();
        
        cout << "################################" << endl << endl;
    }
    
    // End
    return 0;
}
