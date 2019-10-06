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
 g++ main.cpp -w -o PlutoCE
 ./PlutoCE
 
 */

#include <iostream>
#include "chess.h"
using namespace std;


int main(int argc, const char * argv[]) {
    // Define a board object and some variables
    Board board;
    int turn = 1; // Always starts white
    char move[6];
    
    // Choose the mode the settings
    int mode = 0;
    int view = 0;
    
    cout << "Select a board view:" << endl;
    cout << "1. Console (all OS)" << endl;
    cout << "2. Mac OS terminal" << endl;
    cout << "> ";
    cin >> view;
    cout << endl;
    
    cout << "Select the mode you want to play:" << endl;
    cout << "1. 1 vs 1" << endl;
    cout << "2. 1 vs AI" << endl;
    cout << "3. AI vs 1" << endl;
    cout << "> ";
    cin >> mode;
    cout << endl;
    
    // Start the game
    switch (mode) {
        case 1:
            board.displayBoard(view);
            cout << "################################" << endl << endl;
            
            while(true){
                (board.isCheck(board.board, turn) == 1) ? cout << "You are under check" << endl: cout << "No checks" << endl;
                
                (turn == 1) ? cout << "White to move: " : cout << "Black to move: ";
                cin >> move;
                
                board.move(move, turn);
                turn = turn == 1 ? 0 : 1; // Change the move from white to black and viceversa
                
                board.displayBoard(view);
                
                cout << "################################" << endl << endl;
            }
            break;
            
        case 2:
            board.displayBoard(view);
            cout << "################################" << endl << endl;
            
            while(true){
                (board.isCheck(board.board, turn) == 1) ? cout << "You are under check" << endl: cout << "No checks" << endl;
                
                if(turn == 1){
                    cout << "White to move: ";
                    cin >> move;
                    
                    board.move(move, turn);
                }
                else{
                    board.AImove(turn);
                }
                turn = turn == 1 ? 0 : 1; // Change the move from white to black and viceversa
                board.displayBoard(view);
                
                cout << "################################" << endl << endl;
            }
            break;
            
        case 3:
            board.displayBoard(view);
            cout << "################################" << endl << endl;
            
            while(true){
                (board.isCheck(board.board, turn) == 1) ? cout << "You are under check" << endl: cout << "No checks" << endl;
                
                if(turn == 0){
                    cout << "White to move: ";
                    cin >> move;
                    
                    board.move(move, turn);
                }
                else{
                    board.AImove(turn);
                }
                turn = turn == 1 ? 0 : 1; // Change the move from white to black and viceversa
                board.displayBoard(view);
                
                cout << "################################" << endl << endl;
            }
            break;
            
        default:
            cout << "Select an existing mode!" << endl;
            break;
    }

    // End
    return 0;
}
