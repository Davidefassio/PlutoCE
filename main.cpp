//
//  main.cpp
//  PlutoCE
//
//  Created by Davide Fassio on 19/09/2019.
//  GNU GENERAL PUBLIC LICENSE v3.0
//

/*
 
 To run in the terminal for a better use go in the directory:
 ~/Desktop/Programmazione/C++/PlutoCE/PlutoCE
 
 Then write this 2 commands:
 g++ main.cpp -w -o PlutoCE
 ./PlutoCE
 
 */

#include <iostream>
#include "chess.h"


int main(int argc, const char * argv[]) {
    // Define a board object and some variables
    Board board;
    int turn = 1; // Always starts white
    char move[6];
    
    // Choose the mode the settings
    int mode = 0;
    int view = 0;
    
    std::cout << "Select a board view:" << std::endl;
    std::cout << "1. Console (all OS)" << std::endl;
    std::cout << "2. Mac OS terminal" << std::endl;
    std::cout << "> ";
    std::cin >> view;
    std::cout << std::endl;
    
    std::cout << "Select the mode you want to play:" << std::endl;
    std::cout << "1. 1 vs 1" << std::endl;
    std::cout << "2. 1 vs AI" << std::endl;
    std::cout << "3. AI vs 1" << std::endl;
    std::cout << "4. AI vs AI" << std::endl;
    std::cout << "> ";
    std::cin >> mode;
    std::cout << std::endl;
    
    // Start the game
    switch (mode) {
        case 1:
            board.displayBoard(view);
            std::cout << "################################" << std::endl << std::endl;
            
            while(true){
                (board.isCheck(board.get_board(), turn) == 1) ? std::cout << "You are under check" << std::endl : std::cout << "No checks" << std::endl;
                
                (turn == 1) ? std::cout << "White to move: " : std::cout << "Black to move: ";
                std::cin >> move;
                
                board.move(move, turn);
                turn = turn == 1 ? 0 : 1; // Change the move from white to black and viceversa
                
                board.displayBoard(view);
                
                std::cout << "################################" << std::endl << std::endl;
            }
            break;
            
        case 2:
            board.displayBoard(view);
            std::cout << "################################" << std::endl << std::endl;
            
            while(true){
                (board.isCheck(board.get_board(), turn) == 1) ? std::cout << "You are under check" << std::endl : std::cout << "No checks" << std::endl;
                
                if(turn == 1){
                    std::cout << "White to move: ";
                    std::cin >> move;
                    
                    board.move(move, turn);
                }
                else{
                    board.AImove(turn);
                }
                turn = turn == 1 ? 0 : 1; // Change the move from white to black and viceversa
                board.displayBoard(view);
                
                std::cout << "################################" << std::endl << std::endl;
            }
            break;
            
        case 3:
            board.displayBoard(view);
            std::cout << "################################" << std::endl << std::endl;
            
            while(true){
                (board.isCheck(board.get_board(), turn) == 1) ? std::cout << "You are under check" << std::endl : std::cout << "No checks" << std::endl;
                
                if(turn == 0){
                    std::cout << "Black to move: ";
                    std::cin >> move;
                    
                    board.move(move, turn);
                }
                else{
                    board.AImove(turn);
                }
                turn = turn == 1 ? 0 : 1; // Change the move from white to black and viceversa
                board.displayBoard(view);
                
                std::cout << "################################" << std::endl << std::endl;
            }
            break;
        
        case 4:
            fflush(stdin);
            
            while(true){
                board.AImove(turn);
                
                turn = turn == 1 ? 0 : 1; // Change the move from white to black and viceversa
                board.displayBoard(view);
                
                std::cout << "################################" << std::endl << std::endl;
                
                std::cout << "Press ENTER to continue...";
                getchar();
            }
            break;
            
        default:
            std::cout << "Select an existing mode!" << std::endl;
            break;
    }
    
    // End
    return 0;
}
