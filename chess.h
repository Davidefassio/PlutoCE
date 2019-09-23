//
//  chess.h
//  chessAI
//
//  Created by Davide Fassio on 19/09/2019.
//  Copyright © 2019 Davide Fassio. All rights reserved.
//

#ifndef chess_h
#define chess_h

#include <cmath>


class Board{
public:
    // Variables
    
    // Pieces and the board
    const int whitePawn = 100;
    const int whiteKnight = 310; // Add the reamining point in the table
    const int whiteBishop = 320;
    const int whiteRook = 500;
    const int whiteQueen = 900;
    const int whiteKing = 1000000;
    
    const int blackPawn = -100;
    const int blackKnight = -310; // Subtract the reamining point in the table
    const int blackBishop = -320;
    const int blackRook = -500;
    const int blackQueen = -900;
    const int blackKing = -1000000;
    
    // Pieces on the board
    int board[64] = {
        500, 310, 320, 900, 1000000, 320, 310, 500,
        100, 100, 100, 100, 100, 100, 100, 100,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        -100, -100, -100, -100, -100, -100, -100, -100,
        -500, -310, -320, -900, -1000000, -320, -310, -500
    };
    
    // Right to castel: 1 = castel is possible, 0 = castel not possible
    // 0: white kingside
    // 1: white queenside
    // 2: black kingside
    // 3: black kingside
    int castling_rights[4] = {1, 1, 1, 1};
    
    // Capture en-pasant: 1 = can be captured en pasant, 0 = can't be captured en-pasant
    int captured_enpasant[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };
    
    // Piece-square table for better evaluation
    const int whitePawn_eval[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        5, 10, 10,-20,-20, 10, 10, 5,
        5, -5,-10, 0, 0,-10, -5, 5,
        0, 0, 0, 20, 20, 0, 0, 0,
        5, 5, 10, 25, 25, 10, 5, 5,
        10, 10, 20, 30, 30, 20, 10, 10,
        50, 50, 50, 50, 50, 50, 50, 50,
        0, 0, 0, 0, 0, 0, 0, 0,
    };
    const int whiteKnight_eval[64] = {
        -50, -40, -30, -30, -30, -30, -40, -50,
        -40, -20, 0, 5, 5, 0, -20, -40,
        -30, 5, 10, 15, 15, 10, 5, -30,
        -30, 0, 15, 20, 20, 15, 0, -30,
        -30, 5, 15, 20, 20, 15, 5, -30,
        -30, 0, 10, 15, 15, 10, 0, -30,
        -40, -20, 0, 0, 0, 0, -20, -40,
        -50, -40, -30, -30, -30, -30, -40, -50
    };
    const int whiteBishop_eval[64] = {
        -20, -10, -10, -10, -10, -10, -10, -20,
        -10, 5, 0, 0, 0, 0, 5, -10,
        -10, 10, 10, 10, 10, 10, 10, -10,
        -10, 0, 10, 10, 10, 10, 0, -10,
        -10, 5, 5, 10, 10, 5, 5, -10,
        -10, 0, 5, 10, 10, 5, 0, -10,
        -10, 0, 0, 0, 0, 0, 0, -10,
        -20, -10, -10, -10, -10, -10, -10, -20
    };
    const int whiteRook_eval[64] = {
        0, 0, 0, 5, 5, 0, 0, 0,
        -5, 0, 0, 0, 0, 0, 0, -5,
        -5, 0, 0, 0, 0, 0, 0, -5,
        -5, 0, 0, 0, 0, 0, 0, -5,
        -5, 0, 0, 0, 0, 0, 0, -5,
        -5, 0, 0, 0, 0, 0, 0, -5,
        5, 10, 10, 10, 10, 10, 10, 5,
        0, 0, 0, 0, 0, 0, 0, 0
    };
    const int whiteQueen_eval[64] = {
        -20, -10, -10, -5, -5, -10, -10, -20,
        -10, 0, 5, 0,  0, 0, 0, -10,
        -10, 5, 5, 5, 5, 5, 0, -10,
        0, 0, 5, 5, 5, 5, 0, -5,
        -5, 0, 5, 5, 5, 5, 0, -5,
        -10, 0, 5, 5, 5, 5, 0, -10,
        -10, 0, 0, 0, 0, 0, 0, -10,
        -20, -10, -10, -5, -5, -10, -10, -20
    };
    const int whiteKing_middleGame_eval[64] = {
        20, 30, 10, 0, 0, 10, 30, 20,
        20, 20, 0, 0, 0, 0, 20, 20,
        -10, -20, -20, -20,-20, -20, -20, -10,
        -20, -30, -30, -40,-40, -30, -30, -20,
        -30, -40, -40, -50,-50, -40, -40, -30,
        -30, -40, -40, -50,-50, -40, -40, -30,
        -30, -40, -40, -50,-50, -40, -40, -30,
        -30, -40, -40, -50,-50, -40, -40, -30
    };
    const int whiteKing_endGame_eval[64] = {
        -50, -30, -30, -30, -30, -30, -30, -50,
        -30, -30, 0, 0, 0, 0, -30, -30,
        -30, -10, 20, 30, 30, 20, -10, -30,
        -30, -10, 30, 40, 40, 30, -10, -30,
        -30, -10, 30, 40, 40, 30, -10, -30,
        -30, -10, 20, 30, 30, 20, -10, -30,
        -30, -20, -10, 0, 0, -10, -20, -30,
        -50, -40, -30, -20, -20, -30, -40, -50
    };
    
    const int blackPawn_eval[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        -50, -50, -50, -50, -50, -50, -50, -50,
        -10, -10, -20, -30, -30, -20, -10, -10,
        -5, -5, -10, -25, -25, -10, -5, -5,
        0, 0, 0, -20, -20, 0, 0, 0,
        -5, 5, 10, 0, 0, 10, 5, -5,
        -5, -10, -10, 20, 20, -10, -10, -5,
        0, 0, 0, 0, 0, 0, 0, 0
    };
    const int blackKnight_eval[64] = {
        50, 40, 30, 30, 30, 30, 40, 50,
        40, 20, 0, 0, 0, 0, 20, 40,
        30, 0, -10, -15, -15, -10, 0, 30,
        30, -5, -15, -20, -20, -15, -5, 30,
        30, 0, -15, -20, -20, -15, 0, 30,
        30, -5, -10, -15, -15, -10, -5, 30,
        40, 20, 0, -5, -5, 0, 20, 40,
        50, 40, 30, 30, 30, 30, 40, 50
    };
    const int blackBishop_eval[64] = {
        20, 10, 10, 10, 10, 10, 10, 20,
        10, 0, 0, 0, 0, 0, 0, 10,
        10, 0, -5, -10, -10, -5, 0, 10,
        10, -5, -5, -10, -10, -5, -5, 10,
        10, 0, -10, -10, -10, -10, 0, 10,
        10, -10, -10, -10, -10, -10, -10, 10,
        10, -5, 0, 0, 0, 0, -5, 10,
        20, 10, 10, 10, 10, 10, 10, 20
    };
    const int blackRook_eval[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        -5, -10, -10, -10, -10, -10, -10, -5,
        5, 0, 0, 0, 0, 0, 0, 5,
        5, 0, 0, 0, 0, 0, 0, 5,
        5, 0, 0, 0, 0, 0, 0, 5,
        5, 0, 0, 0, 0, 0, 0, 5,
        5, 0, 0, 0, 0, 0, 0, 5,
        0, 0, 0, -5, -5, 0, 0, 0
    };
    const int blackQueen_eval[64] = {
        20, 10, 10, 5, 5, 10, 10, 20,
        10, 0, 0, 0, 0, 0, 0, 10,
        10, 0, -5, -5, -5, -5, 0, 10,
        5, 0, -5, -5, -5, -5, 0, 5,
        0, 0, -5, -5, -5, -5, 0, 5,
        10, -5, -5, -5, -5, -5, 0, 10,
        10, 0, -5, 0, 0, 0, 0, 10,
        20, 10, 10, 5, 5, 10, 10, 20
    };
    const int blackKing_middleGame_eval[64] = {
        30, 40, 40, 50, 50, 40, 40, 30,
        30, 40, 40, 50, 50, 40, 40, 30,
        30, 40, 40, 50, 50, 40, 40, 30,
        30, 40, 40, 50, 50, 40, 40, 30,
        20, 30, 30, 40, 40, 30, 30, 20,
        10, 20, 20, 20, 20, 20, 20, 10,
        -20, -20,  0,  0,  0,  0, -20, -20,
        -20, -30, -10,  0,  0, -10, -30, -20
    };
    const int blackKing_endGame_eval[64] = {
        50, 40, 30, 20, 20, 30, 40, 50,
        30, 20, 10, 0,  0, 10, 20, 30,
        30, 10, -20, -30, -30, -20, 10, 30,
        30, 10, -30, -40, -40, -30, 10, 30,
        30, 10, -30, -40, -40, -30, 10, 30,
        30, 10, -20, -30, -30, -20, 10, 30,
        30, 30, 0, 0,  0, 0, 30, 30,
        50, 30, 30, 30, 30, 30, 30, 50
    };
    
    // Functions
    void playerMove(int*, char*, int, int*, int*);
    int evaluate(int*);
    int isCheck(int*, int);
    void displayBoard_console();
    void displayBoard_terminal();
};

/*
 Function that move the pieces on the board
 Parameters:
    - 8x8 board
    - char *move = 6 element string containing
        - the move (4 char)
        - the code of the piece to promote in case of promotion (1 char) example: Queen = Q, Knight = N
          Use capital letters for the promotion
    - isWhiteMoving: 1 -> white is moving, 0 -> black is moving
    - 8x8 board for capture en-pasant
    - lenght 4 array containing the castling rights
*/
void Board::playerMove(int *board, char *move, int isWhiteMoving, int *enpasant, int *rights){
    // check the move if is correct
    int moveIsCorrect = 0;  // Starting with illegal
    
    // the move is in form y1r1y2r2
    // example the move 1.Nf3 is g1f3
    int f1 = (int)move[0] - 97;
    int r1 = (int)move[1] - 49;
    int f2 = (int)move[2] - 97;
    int r2 = (int)move[3] - 49;
    
    int start = r1*8 + f1;
    int land = r2*8 + f2;
    
    // TO FINISH AND TEST
    if(start >= 0 && start < 64 && land >= 0 && land < 64){
        if(isWhiteMoving == 1){
            // Remove all the right to capture a white pawn en-pasant
            for(int j = 0; j < 8; j++)
                enpasant[24 + j] = 0;
            
            if(board[start] > 0 && board[land] <= 0){
                switch (board[start]){
                    case 100: // Pawn
                        if(r1 == 1){ // Starting square
                            if(land - start == 16 && board[start + 8] == 0 && board[land] == 0){
                                moveIsCorrect = 1;
                                enpasant[land] = 1;
                            }
                            else if(land - start == 8 && board[land] == 0)
                                moveIsCorrect = 1;
                            else if((land - start == 7 || land - start == 9) && board[land] < 0)
                                moveIsCorrect = 1;
                        }
                        else if(r1 == 4){ // En-pasant capture
                            // Normal moves
                            if(land - start == 8 && board[land] == 0)
                                moveIsCorrect = 1;
                            else if((land - start == 7 || land - start == 9) && board[land] < 0)
                                moveIsCorrect = 1;
                            // En-pasant captures
                            else if(land - start == 9 && enpasant[start + 1] == 1){
                                moveIsCorrect = 1;
                                board[start + 1] = 0;
                            }
                            else if(land - start == 7 && enpasant[start - 1] == 1){
                                moveIsCorrect = 1;
                                board[start - 1] = 0;
                            }
                        }
                        else if(r1 == 6){ // Promotion
                            switch (move[4]) {
                                case 'N':
                                    board[start] = 310;
                                    break;
                                
                                case 'B':
                                    board[start] = 320;
                                    break;
                                    
                                case 'R':
                                    board[start] = 500;
                                    break;
                                    
                                case 'Q':
                                    board[start] = 900;
                                    break;
                                    
                                default:
                                    std::cout << "The move made is illegal!" << std::endl;
                                    exit(0);
                                    break;
                            }
                            
                            if(land - start == 8 && board[land] == 0){
                                moveIsCorrect = 1;
                            }
                            else if((land - start == 7 || land - start == 9) && board[land] < 0){
                                moveIsCorrect = 1;
                            }
                            
                        }
                        else{ // Every other rank
                            if(land - start == 8 && board[land] == 0)
                                moveIsCorrect = 1;
                            else if((land - start == 7 || land - start == 9) && board[land] < 0)
                                moveIsCorrect = 1;
                        }
                        break;
                    
                    case 310: // Knight
                        if(abs(r2 - r1) + abs(f2 - f1) == 3)
                            moveIsCorrect = 1;
                        break;
                    
                    case 320: // Bishop
                        if(abs(r2 - r1) == abs(f2 - f1)){
                            int kr = (r2 - r1 > 0) ? 1 : -1;
                            int kf = (f2 - f1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(r2 - r1); i++){
                                if(board[start + (i*kr*8) + (i*kf)] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        break;
                    
                    case 500: // Rook
                        // White lose the castling rights
                        if(start == 0) // queenside
                            rights[1] = 0;
                        else if(start == 7) //kingside
                            rights[0] = 0;
                        
                        if(r1 == r2){
                            int kf = (f2 - f1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(f2 - f1); i++){
                                if(board[start + i*kf] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        else if(f1 == f2){
                            int kr = (r2 - r1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(r2 - r1); i++){
                                if(board[start + i*kr*8] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        break;
                    
                    case 900: // Queen
                        // Move like a bishop
                        if(abs(r2 - r1) == abs(f2 - f1)){
                            int kr = (r2 - r1 > 0) ? 1 : -1;
                            int kf = (f2 - f1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(r2 - r1); i++){
                                if(board[start + (i*kr*8) + (i*kf)] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        // Or like a rook
                        else if(r1 == r2){
                            int kf = (f2 - f1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(f2 - f1); i++){
                                if(board[start + i*kf] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        else if(f1 == f2){
                            int kr = (r2 - r1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(r2 - r1); i++){
                                if(board[start + i*kr*8] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        break;
                        
                    case 1000000: // King
                        if(abs(r2 - r1) < 2 && abs(f2 - f1) < 2){
                            moveIsCorrect = 1;
                        }
                        else if(rights[0] == 1 && land == 6 && board[5] == 0 && board[6] == 0){
                            // Control checks in the way
                            if(this->isCheck(board, 1) == 0){
                                board[4] = 0;
                                board[5] = 1000000;
                                if(this->isCheck(board, 1) == 0){
                                    board[5] = 0;
                                    board[6] = 1000000;
                                    if(this->isCheck(board, 1) == 0){
                                        moveIsCorrect = 1;
                                        // Restore king's position
                                        board[4] = 1000000;
                                        board[6] = 0;
                                        // Move the rook
                                        board[7] = 0;
                                        board[5] = 500;
                                    }
                                }
                            }
                        }
                        else if(rights[1] == 1 && land == 2 && board[3] == 0 && board[2] == 0 && board[1] == 0){
                            // Control checks in the way
                            if(this->isCheck(board,1) == 0){
                                board[4] = 0;
                                board[3] = 1000000;
                                if(this->isCheck(board,1) == 0){
                                    board[3] = 0;
                                    board[2] = 1000000;
                                    if(this->isCheck(board,1) == 0){
                                        moveIsCorrect = 1;
                                        // Restore king's position
                                        board[4] = 1000000;
                                        board[2] = 0;
                                        // Move the rook
                                        board[0] = 0;
                                        board[3] = 500;
                                    }
                                }
                            }
                        }
                        // white lose all castling rights
                        rights[0] = rights[1] = 0;
                        
                        break;
                }
            }
        }
        else if(isWhiteMoving == 0){
            // Remove all the right to capture a black pawn en-pasant
            for(int j = 0; j < 8; j++)
                enpasant[32 + j] = 0;
            
            if(board[start] < 0 && board[land] >= 0){
                switch (board[start]){
                    case -100: // Pawn
                        if(r1 == 6){ // Starting square
                            if(start - land == 16 && board[start - 8] == 0 && board[land] == 0){
                                moveIsCorrect = 1;
                                enpasant[land] = 1;
                            }
                            else if(start - land == 8 && board[land] == 0)
                                moveIsCorrect = 1;
                            else if((start - land == 7 || start - land == 9) && board[land] > 0)
                                moveIsCorrect = 1;
                        }
                        else if(r1 == 3){ // En-pasant capture
                            // Normal moves
                            if(start - land == 8 && board[land] == 0)
                                moveIsCorrect = 1;
                            else if((start - land == 7 || start - land == 9) && board[land] > 0)
                                moveIsCorrect = 1;
                            // En-pasant captures
                            else if(start - land == 7 && enpasant[start + 1] == 1){
                                moveIsCorrect = 1;
                                board[start + 1] = 0;
                            }
                            else if(start - land == 9 && enpasant[start - 1] == 1){
                                moveIsCorrect = 1;
                                board[start - 1] = 0;
                            }
                        }
                        else if(r1 == 1){ // Promotion
                            switch (move[4]) {
                                case 'N':
                                    board[start] = -310;
                                    break;
                                    
                                case 'B':
                                    board[start] = -320;
                                    break;
                                    
                                case 'R':
                                    board[start] = -500;
                                    break;
                                    
                                case 'Q':
                                    board[start] = -900;
                                    break;
                                    
                                default:
                                    std::cout << "The move made is illegal!" << std::endl;
                                    exit(0);
                                    break;
                            }
                            
                            if(start - land == 8 && board[land] == 0){
                                moveIsCorrect = 1;
                            }
                            else if((start - land == 7 || start - land == 9) && board[land] > 0){
                                moveIsCorrect = 1;
                            }
                            
                        }
                        else{ // Every other rank
                            if(start - land == 8 && board[land] == 0)
                                moveIsCorrect = 1;
                            else if((start - land == 7 || start - land == 9) && board[land] > 0)
                                moveIsCorrect = 1;
                        }
                        break;
                        
                    case -310: // Knight
                        if(abs(r2 - r1) + abs(f2 - f1) == 3)
                            moveIsCorrect = 1;
                        break;
                        
                    case -320: // Bishop
                        if(abs(r2 - r1) == abs(f2 - f1)){
                            int kr = (r2 - r1 > 0) ? 1 : -1;
                            int kf = (f2 - f1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(r2 - r1); i++){
                                if(board[start + (i*kr*8) + (i*kf)] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        break;
                        
                    case -500: // Rook
                        // White lose the castling rights
                        if(start == 56) // queenside
                            rights[3] = 0;
                        else if(start == 63) //kingside
                            rights[2] = 0;
                        
                        if(r1 == r2){
                            int kf = (f2 - f1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(f2 - f1); i++){
                                if(board[start + i*kf] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        else if(f1 == f2){
                            int kr = (r2 - r1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(r2 - r1); i++){
                                if(board[start + i*kr*8] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        break;
                        
                    case -900: // Queen
                        // Move like a bishop
                        if(abs(r2 - r1) == abs(f2 - f1)){
                            int kr = (r2 - r1 > 0) ? 1 : -1;
                            int kf = (f2 - f1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(r2 - r1); i++){
                                if(board[start + (i*kr*8) + (i*kf)] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        // Or like a rook
                        else if(r1 == r2){
                            int kf = (f2 - f1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(f2 - f1); i++){
                                if(board[start + i*kf] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        else if(f1 == f2){
                            int kr = (r2 - r1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(r2 - r1); i++){
                                if(board[start + i*kr*8] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        break;
                        
                    case -1000000: // King
                        if(abs(r2 - r1) < 2 && abs(f2 - f1) < 2){
                            moveIsCorrect = 1;
                        }
                        else if(rights[2] == 1 && land == 62 && board[61] == 0 && board[62] == 0){
                            // Control checks in the way
                            if(this->isCheck(board, 0) == 0){
                                board[60] = 0;
                                board[61] = -1000000;
                                if(this->isCheck(board, 0) == 0){
                                    board[61] = 0;
                                    board[62] = -1000000;
                                    if(this->isCheck(board, 0) == 0){
                                        moveIsCorrect = 1;
                                        // Restore king's position
                                        board[60] = -1000000;
                                        board[62] = 0;
                                        // Move the rook
                                        board[63] = 0;
                                        board[61] = -500;
                                    }
                                }
                            }
                        }
                        else if(rights[3] == 1 && land == 58 && board[59] == 0 && board[58] == 0 && board[57] == 0){
                            // Control checks in the way
                            if(this->isCheck(board, 0) == 0){
                                board[60] = 0;
                                board[59] = -1000000;
                                if(this->isCheck(board, 0) == 0){
                                    board[59] = 0;
                                    board[58] = -1000000;
                                    if(this->isCheck(board, 0) == 0){
                                        moveIsCorrect = 1;
                                        // Restore king's position
                                        board[60] = -1000000;
                                        board[68] = 0;
                                        // Move the rook
                                        board[56] = 0;
                                        board[59] = -500;
                                    }
                                }
                            }
                        }
                        // black lose all castling rights
                        rights[2] = rights[3] = 0;
                        
                        break;
                }
            }
        }
    }
    else{
        std::cout << "The move made is illegal!" << std::endl;
        exit(0);
    }
    
    if(moveIsCorrect == 1){
        board[land] = board[start];
        board[start] = 0;
        
        if(this->isCheck(board, isWhiteMoving) == 1){
            std::cout << "The move made is illegal!" << std::endl;
            exit(0);
        }
    }
    else{
        std::cout << "The move made is illegal!" << std::endl;
        exit(0);
    }
}


// Parameter:
//      - an 8x8 board
int Board::evaluate(int *board){
    int evaluation = 0;
    
    int pieceValueCount = 0;    // to know when it go in the endgame
    int whiteKing_index = 0, blackKing_index = 0;
    
    for(int k = 0; k < 64; k++){
        // Add the value of the piece
        evaluation += board[k];
        
        // Add the module of all pieces to know when is the endgame
        pieceValueCount += abs(board[k]);
        
        // Decide which piece-square table use
        switch (board[k]) {
            case 0:
                break;
                
            case 100:
                evaluation += this->whitePawn_eval[k];
                break;
            
            case 310:
                evaluation += this->whiteKnight_eval[k];
                break;
                
            case 320:
                evaluation += this->whiteBishop_eval[k];
                break;
                
            case 500:
                evaluation += this->whiteRook_eval[k];
                break;
                
            case 900:
                evaluation += this->whiteQueen_eval[k];
                break;
                
            case 1000000:   // Save the coords for after
                whiteKing_index = k;
                break;
                
            case -100:
                evaluation += this->blackPawn_eval[k];
                break;
                
            case -310:
                evaluation += this->blackKnight_eval[k];
                break;
                
            case -320:
                evaluation += this->blackBishop_eval[k];
                break;
                
            case -500:
                evaluation += this->blackRook_eval[k];
                break;
                
            case -900:
                evaluation += this->blackQueen_eval[k];
                break;
                
            case -1000000:  // Save the coords for after
                blackKing_index = k;
                break;
        }
    }
    // If the sum of the module of all pieces is less than 2003600 we are in the endgame
    // 2003600 is exactly:
    // 1 King + 1 Queen + 1 Rook + 4 Pawn each
    if(pieceValueCount < 2003600){
        evaluation += this->whiteKing_endGame_eval[whiteKing_index];
        evaluation += this->blackKing_endGame_eval[blackKing_index];
    }
    else{
        evaluation += this->whiteKing_middleGame_eval[whiteKing_index];
        evaluation += this->blackKing_middleGame_eval[blackKing_index];
    }
    
    return evaluation;
}


// Control if there are checks on the board:
//  - isWhiteKing = 1 -> white king under check
//  - isWhiteKing = 0 -> black king under check
// Return value: 1 -> true, 0 -> false
int Board::isCheck(int *board, int isWhiteKing){
    if(isWhiteKing == 1){
        int index = 0;
        for(int k = 0; k < 64; k++){
            if(board[k] == 1000000){
                index = k;
                break;
            }
        }
        
        int f = index % 8;
        int r = std::floor(index / 8);
        
        // Check from knights
        if(r+2 >= 0 && r+2 < 8 && f+1 >= 0 && f+1 < 8 && board[index + 17] == -310)
            return 1;
        if(r+1 >= 0 && r+1 < 8 && f+2 >= 0 && f+2 < 8 && board[index + 10] == -310)
            return 1;
        if(r-1 >= 0 && r-1 < 8 && f+2 >= 0 && f+2 < 8 && board[index - 6] == -310)
            return 1;
        if(r-2 >= 0 && r-2 < 8 && f+1 >= 0 && f+1 < 8 && board[index - 15] == -310)
            return 1;
        if(r-2 >= 0 && r-2 < 8 && f-1 >= 0 && f-1 < 8 && board[index - 17] == -310)
            return 1;
        if(r-1 >= 0 && r-1 < 8 && f-2 >= 0 && f-2 < 8 && board[index - 10] == -310)
            return 1;
        if(r+1 >= 0 && r+1 < 8 && f-2 >= 0 && f-2 < 8 && board[index + 6] == -310)
            return 1;
        if(r+2 >= 0 && r+2 < 8 && f-1 >= 0 && f-1 < 8 && board[index + 15] == -310)
            return 1;
        
        // Check from bishops/queens
        for(int i = 1; r + i < 8 && f + i < 8; i++){
            if(i == 1){ // Check from pawns
                if(board[index + 9*i] == -100)
                    return 1;
            }
            if(board[index + 9*i] == -320 || board[index + 9*i] == -900)
                return 1;
            if(board[index + 9*i] != 0)
                break;
        }
        for(int i = 1; r - i >= 0 && f + i < 8; i++){
            if(board[index - 7*i] == -320 || board[index - 7*i] == -900)
                return 1;
            if(board[index - 7*i] != 0)
                break;
        }
        for(int i = 1; r - i >= 0 && f - i >= 0; i++){
            if(board[index - 9*i] == -320 || board[index - 9*i] == -900)
                return 1;
            if(board[index - 9*i] != 0)
                break;
        }
        for(int i = 1; r + i < 8 && f - i >= 0; i++){
            if(i == 1){ // Check from pawns
                if(board[index + 7*i] == -100)
                    return 1;
            }
            if(board[index + 7*i] == -320 || board[index + 7*i] == -900)
                return 1;
            if(board[index + 7*i] != 0)
                break;
        }
        
        // Check from rook/queens
        for(int i = 1; r + i < 8; i++){
            if(board[index + 8*i] == -500 || board[index + 8*i] == -900)
                return 1;
            if(board[index + 8*i] != 0)
                break;
        }
        for(int i = 1; f + i < 8; i++){
            if(board[index + i] == -500 || board[index + i] == -900)
                return 1;
            if(board[index + i] != 0)
                break;
        }
        for(int i = 1; r - i >= 0; i++){
            if(board[index - 8*i] == -500 || board[index - 8*i] == -900)
                return 1;
            if(board[index - 8*i] != 0)
                break;
        }
        for(int i = 1; f - i >= 0; i++){
            if(board[index - i] == -500 || board[index - i] == -900)
                return 1;
            if(board[index - i] != 0)
                break;
        }
    }
    else{
        int index = 0;
        for(int k = 63; k >= 0; k--){
            if(board[k] == -1000000){
                index = k;
                break;
            }
        }
        
        int f = index % 8;
        int r = std::floor(index / 8);
        
        // Check from knights
        if(r+2 >= 0 && r+2 < 8 && f+1 >= 0 && f+1 < 8 && board[index + 17] == 310)
            return 1;
        if(r+1 >= 0 && r+1 < 8 && f+2 >= 0 && f+2 < 8 && board[index + 10] == 310)
            return 1;
        if(r-1 >= 0 && r-1 < 8 && f+2 >= 0 && f+2 < 8 && board[index - 6] == 310)
            return 1;
        if(r-2 >= 0 && r-2 < 8 && f+1 >= 0 && f+1 < 8 && board[index - 15] == 310)
            return 1;
        if(r-2 >= 0 && r-2 < 8 && f-1 >= 0 && f-1 < 8 && board[index - 17] == 310)
            return 1;
        if(r-1 >= 0 && r-1 < 8 && f-2 >= 0 && f-2 < 8 && board[index - 10] == 310)
            return 1;
        if(r+1 >= 0 && r+1 < 8 && f-2 >= 0 && f-2 < 8 && board[index + 6] == 310)
            return 1;
        if(r+2 >= 0 && r+2 < 8 && f-1 >= 0 && f-1 < 8 && board[index + 15] == 310)
            return 1;
        
        // Check from bishops/queens
        for(int i = 1; r + i < 8 && f + i < 8; i++){
            if(board[index + 9*i] == 320 || board[index + 9*i] == 900)
                return 1;
            if(board[index + 9*i] != 0)
                break;
        }
        for(int i = 1; r - i >= 0 && f + i < 8; i++){
            if(i == 1){ // Check from pawns
                if(board[index - 7*i] == 100)
                    return 1;
            }
            if(board[index - 7*i] == 320 || board[index - 7*i] == 900)
                return 1;
            if(board[index - 7*i] != 0)
                break;
        }
        for(int i = 1; r - i >= 0 && f - i >= 0; i++){
            if(i == 1){ // Check from pawns
                if(board[index - 9*i] == 100)
                    return 1;
            }
            if(board[index - 9*i] == 320 || board[index - 9*i] == 900)
                return 1;
            if(board[index - 9*i] != 0)
                break;
        }
        for(int i = 1; r + i < 8 && f - i >= 0; i++){
            if(board[index + 7*i] == 320 || board[index + 7*i] == 900)
                return 1;
            if(board[index + 7*i] != 0)
                break;
        }
        
        // Check from rook/queens
        for(int i = 1; r + i < 8; i++){
            if(board[index + 8*i] == 500 || board[index + 8*i] == 900)
                return 1;
            if(board[index + 8*i] != 0)
                break;
        }
        for(int i = 1; f + i < 8; i++){
            if(board[index + i] == 500 || board[index + i] == 900)
                return 1;
            if(board[index + i] != 0)
                break;
        }
        for(int i = 1; r - i >= 0; i++){
            if(board[index - 8*i] == 500 || board[index - 8*i] == 900)
                return 1;
            if(board[index - 8*i] != 0)
                break;
        }
        for(int i = 1; f - i >= 0; i++){
            if(board[index - i] == 500 || board[index - i] == 900)
                return 1;
            if(board[index - i] != 0)
                break;
        }
    }
    
    // No checks
    return 0;
}

// Display the board without using colors
// Compatible with all OS
void Board::displayBoard_console(){
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            switch (this->board[i*8 + j]) {
                case 0:
                    std::cout << "00 ";
                    break;
                    
                case 100:
                    std::cout << "WP ";
                    break;
                    
                case 310:
                    std::cout << "WN ";
                    break;
                    
                case 320:
                    std::cout << "WB ";
                    break;
                    
                case 500:
                    std::cout << "WR ";
                    break;
                    
                case 900:
                    std::cout << "WQ ";
                    break;
                    
                case 1000000:
                    std::cout << "WK ";
                    break;
                    
                case -100:
                    std::cout << "BP ";
                    break;
                    
                case -310:
                    std::cout << "BN ";
                    break;
                    
                case -320:
                    std::cout << "BB ";
                    break;
                    
                case -500:
                    std::cout << "BR ";
                    break;
                    
                case -900:
                    std::cout << "BQ ";
                    break;
                    
                case -1000000:
                    std::cout << "BK ";
                    break;
                    
                default:
                    std::cout << "Detected an unknown piece on the board!"<< std::endl;
                    exit(0);
                    break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Define ANSI codes for Mac OS
#define WHITE_LIGHT  "\x1b[37;46m"
#define WHITE_DARK   "\x1b[37;42m"
#define BLACK_LIGHT  "\x1b[30;46m"
#define BLACK_DARK   "\x1b[30;42m"
#define NORMAL       "\x1b[0m"

// Display the board using ANSI codes
// Needs to be lanched from Mac OS terminal
// Better UI than console display
void Board::displayBoard_terminal(){
    std::cout << std::endl;
    for(int i = 7; i >= 0; i--){
        std::cout << i + 1 ;
        for(int j = 0; j < 8; j++){
            switch(this->board[i*8 + j]) {
                case 0:
                    if((i + j) % 2 == 0)
                        std::cout << WHITE_DARK "   " NORMAL;
                    else
                        std::cout << WHITE_LIGHT "   " NORMAL;
                    break;
                    
                case 100:
                    if((i + j) % 2 == 0)
                        std::cout << WHITE_DARK " P " NORMAL;
                    else
                        std::cout << WHITE_LIGHT " P " NORMAL;
                    break;
                    
                case 310:
                    if((i + j) % 2 == 0)
                        std::cout << WHITE_DARK " N " NORMAL;
                    else
                        std::cout << WHITE_LIGHT " N " NORMAL;
                    break;
                    
                case 320:
                    if((i + j) % 2 == 0)
                        std::cout << WHITE_DARK " B " NORMAL;
                    else
                        std::cout << WHITE_LIGHT " B " NORMAL;
                    break;
                    
                case 500:
                    if((i + j) % 2 == 0)
                        std::cout << WHITE_DARK " R " NORMAL;
                    else
                        std::cout << WHITE_LIGHT " R " NORMAL;
                    break;
                    
                case 900:
                    if((i + j) % 2 == 0)
                        std::cout << WHITE_DARK " Q " NORMAL;
                    else
                        std::cout << WHITE_LIGHT " Q " NORMAL;
                    break;
                    
                case 1000000:
                    if((i + j) % 2 == 0)
                        std::cout << WHITE_DARK " K " NORMAL;
                    else
                        std::cout << WHITE_LIGHT " K " NORMAL;
                    break;
                    
                case -100:
                    if((i + j) % 2 == 0)
                        std::cout << BLACK_DARK " P " NORMAL;
                    else
                        std::cout << BLACK_LIGHT " P " NORMAL;
                    break;
                    
                case -310:
                    if((i + j) % 2 == 0)
                        std::cout << BLACK_DARK " N " NORMAL;
                    else
                        std::cout << BLACK_LIGHT " N " NORMAL;
                    break;
                    
                case -320:
                    if((i + j) % 2 == 0)
                        std::cout << BLACK_DARK " B " NORMAL;
                    else
                        std::cout << BLACK_LIGHT " B " NORMAL;
                    break;
                    
                case -500:
                    if((i + j) % 2 == 0)
                        std::cout << BLACK_DARK " R " NORMAL;
                    else
                        std::cout << BLACK_LIGHT " R " NORMAL;
                    break;
                    
                case -900:
                    if((i + j) % 2 == 0)
                        std::cout << BLACK_DARK " Q " NORMAL;
                    else
                        std::cout << BLACK_LIGHT " Q " NORMAL;
                    break;
                    
                case -1000000:
                    if((i + j) % 2 == 0)
                        std::cout << BLACK_DARK " K " NORMAL;
                    else
                        std::cout << BLACK_LIGHT " K " NORMAL;
                    break;
                    
                default:
                    std::cout << "Detected an unknown piece on the board!"<< std::endl;
                    exit(0);
                    break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  a  b  c  d  e  f  g  h" << std::endl << std::endl;
}

#endif /* chess_h */
