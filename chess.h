//
//  chess.h
//  PlutoCE
//
//  Created by Davide Fassio on 19/09/2019.
//  GNU GENERAL PUBLIC LICENSE v3.0
//

// Check operating system
// 0: not defined
// 1: Mac OS
// 2: Windows
// 3: Linux
#if defined(__APPLE__)
    #define OS 1
#elif defined(_WIN32)
    #define OS 2
#elif defined(__linux__)
    #define OS 3
#endif

#ifndef OS
    #define OS 0
#endif


#ifndef chess_h
#define chess_h

#include <iostream>
#include <cstdlib>


class Board{
public:
    // Functions
    void move(char*, int);
    void AImove(int);
    int isCheck(int*, int);
    void set_treeDepth(int);
    void set_board(int*);
    int* get_board();
    void print_bestMove(int);
    void displayBoard(int);
    
private:
    // Pieces values
    const int whitePawn = 100;
    const int whiteKnight = 310;
    const int whiteBishop = 320;
    const int whiteRook = 500;
    const int whiteQueen = 900;
    const int whiteKing = 1000000;
    
    const int blackPawn = -100;
    const int blackKnight = -310;
    const int blackBishop = -320;
    const int blackRook = -500;
    const int blackQueen = -900;
    const int blackKing = -1000000;
    
    // Pieces on the board
    int board[64] = {500, 310, 320, 900, 1000000, 320, 310, 500, 100, 100, 100, 100, 100, 100, 100, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -100, -100, -100, -100, -100, -100, -100, -100, -500, -310, -320, -900, -1000000, -320, -310, -500};
    
    int boardCopy[64];
    
    // Right to castel: 1 = castel is possible, 0 = castel is not possible
    // 0: white kingside, 1: white queenside, 2: black kingside, 3: black queenside
    int castling_rights[4] = {1, 1, 1, 1};
    
    // Capture en-pasant: 1 = can be captured en pasant, 0 = can't be captured en-pasant
    int captured_enpasant[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    // Piece-square table for better evaluation
    const int whitePawn_eval[64] = {0, 0, 0, 0, 0, 0, 0, 0, 5, 10, 10,-20,-20, 10, 10, 5, 5, -5,-10, 0, 0,-10, -5, 5, 0, 0, 0, 20, 20, 0, 0, 0, 5, 5, 10, 25, 25, 10, 5, 5, 10, 10, 20, 30, 30, 20, 10, 10, 50, 50, 50, 50, 50, 50, 50, 50, 0, 0, 0, 0, 0, 0, 0, 0};
    const int whitePawn_passed[64] = {0, 0, 0, 0, 0, 0, 0, 0, 40, 30, 30, 40, 40, 30, 30, 40, 50, 40, 40, 50, 50, 40, 40, 50, 60, 50, 50, 60, 60, 50, 50, 60, 70, 60, 60, 70, 70, 60, 60, 70, 90, 90, 90, 90, 90, 90, 90, 90, 80, 70, 70, 80, 80, 70, 70, 80, 0, 0, 0, 0, 0, 0, 0, 0};
    const int whiteKnight_eval[64] = {-50, -40, -30, -30, -30, -30, -40, -50, -40, -20, 0, 5, 5, 0, -20, -40, -30, 5, 10, 15, 15, 10, 5, -30, -30, 0, 15, 20, 20, 15, 0, -30, -30, 5, 15, 20, 20, 15, 5, -30, -30, 0, 10, 15, 15, 10, 0, -30, -40, -20, 0, 0, 0, 0, -20, -40, -50, -40, -30, -30, -30, -30, -40, -50};
    const int whiteBishop_eval[64] = {-20, -10, -10, -10, -10, -10, -10, -20, -10, 5, 0, 0, 0, 0, 5, -10, -10, 10, 10, 10, 10, 10, 10, -10, -10, 0, 10, 10, 10, 10, 0, -10, -10, 5, 5, 10, 10, 5, 5, -10, -10, 0, 5, 10, 10, 5, 0, -10, -10, 0, 0, 0, 0, 0, 0, -10, -20, -10, -10, -10, -10, -10, -10, -20};
    const int whiteRook_eval[64] = {0, 0, 0, 5, 5, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, -5, -5, 0, 0, 0, 0, 0, 0, -5, -5, 0, 0, 0, 0, 0, 0, -5, -5, 0, 0, 0, 0, 0, 0, -5, -5, 0, 0, 0, 0, 0, 0, -5, 5, 10, 10, 10, 10, 10, 10, 5, 0, 0, 0, 0, 0, 0, 0, 0};
    const int whiteQueen_eval[64] = {-20, -10, -10, -5, -5, -10, -10, -20, -10, 0, 5, 0, 0, 0, 0, -10, -10, 5, 5, 5, 5, 5, 0, -10, 0, 0, 5, 5, 5, 5, 0, -5, -5, 0, 5, 5, 5, 5, 0, -5, -10, 0, 5, 5, 5, 5, 0, -10, -10, 0, 0, 0, 0, 0, 0, -10, -20, -10, -10, -5, -5, -10, -10, -20};
    const int whiteKing_middleGame_eval[64] = {20, 30, 10, 0, 0, 10, 30, 20, 20, 20, 0, 0, 0, 0, 20, 20, -10, -20, -20, -20,-20, -20, -20, -10, -20, -30, -30, -40,-40, -30, -30, -20, -30, -40, -40, -50,-50, -40, -40, -30, -30, -40, -40, -50,-50, -40, -40, -30, -30, -40, -40, -50,-50, -40, -40, -30, -30, -40, -40, -50,-50, -40, -40, -30};
    const int whiteKing_endGame_eval[64] = {-50, -30, -30, -30, -30, -30, -30, -50, -30, -30, 0, 0, 0, 0, -30, -30, -30, -10, 20, 30, 30, 20, -10, -30, -30, -10, 30, 40, 40, 30, -10, -30, -30, -10, 30, 40, 40, 30, -10, -30, -30, -10, 20, 30, 30, 20, -10, -30, -30, -20, -10, 0, 0, -10, -20, -30, -50, -40, -30, -20, -20, -30, -40, -50};
    
    const int blackPawn_eval[64] = {0, 0, 0, 0, 0, 0, 0, 0, -50, -50, -50, -50, -50, -50, -50, -50, -10, -10, -20, -30, -30, -20, -10, -10, -5, -5, -10, -25, -25, -10, -5, -5, 0, 0, 0, -20, -20, 0, 0, 0, -5, 5, 10, 0, 0, 10, 5, -5, -5, -10, -10, 20, 20, -10, -10, -5, 0, 0, 0, 0, 0, 0, 0, 0};
    const int blackPawn_passed[64] = {0, 0, 0, 0, 0, 0, 0, 0, -90, -90, -90, -90, -90, -90, -90, -90, -80, -70, -70, -80, -80, -70, -70, -80, -70, -60, -60, -70, -70, -60, -60, -70, -60, -50, -50, -60, -60, -50, -50, -60, -50, -40, -40, -50, -50, -40, -40, -50, -40, -30, -30, -40, -40, -30, -30, -40, 0, 0, 0, 0, 0, 0, 0, 0};
    const int blackKnight_eval[64] = {50, 40, 30, 30, 30, 30, 40, 50, 40, 20, 0, 0, 0, 0, 20, 40, 30, 0, -10, -15, -15, -10, 0, 30, 30, -5, -15, -20, -20, -15, -5, 30, 30, 0, -15, -20, -20, -15, 0, 30, 30, -5, -10, -15, -15, -10, -5, 30, 40, 20, 0, -5, -5, 0, 20, 40, 50, 40, 30, 30, 30, 30, 40, 50};
    const int blackBishop_eval[64] = {20, 10, 10, 10, 10, 10, 10, 20, 10, 0, 0, 0, 0, 0, 0, 10, 10, 0, -5, -10, -10, -5, 0, 10, 10, -5, -5, -10, -10, -5, -5, 10, 10, 0, -10, -10, -10, -10, 0, 10, 10, -10, -10, -10, -10, -10, -10, 10, 10, -5, 0, 0, 0, 0, -5, 10, 20, 10, 10, 10, 10, 10, 10, 20};
    const int blackRook_eval[64] = {0, 0, 0, 0, 0, 0, 0, 0, -5, -10, -10, -10, -10, -10, -10, -5, 5, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, -5, -5, 0, 0, 0};
    const int blackQueen_eval[64] = {20, 10, 10, 5, 5, 10, 10, 20, 10, 0, 0, 0, 0, 0, 0, 10, 10, 0, -5, -5, -5, -5, 0, 10, 5, 0, -5, -5, -5, -5, 0, 5, 0, 0, -5, -5, -5, -5, 0, 5, 10, -5, -5, -5, -5, -5, 0, 10, 10, 0, -5, 0, 0, 0, 0, 10, 20, 10, 10, 5, 5, 10, 10, 20};
    const int blackKing_middleGame_eval[64] = {30, 40, 40, 50, 50, 40, 40, 30, 30, 40, 40, 50, 50, 40, 40, 30, 30, 40, 40, 50, 50, 40, 40, 30, 30, 40, 40, 50, 50, 40, 40, 30, 20, 30, 30, 40, 40, 30, 30, 20, 10, 20, 20, 20, 20, 20, 20, 10, -20, -20, 0, 0, 0, 0, -20, -20, -20, -30, -10, 0, 0, -10, -30, -20};
    const int blackKing_endGame_eval[64] = {50, 40, 30, 20, 20, 30, 40, 50, 30, 20, 10, 0, 0, 10, 20, 30, 30, 10, -20, -30, -30, -20, 10, 30, 30, 10, -30, -40, -40, -30, 10, 30, 30, 10, -30, -40, -40, -30, 10, 30, 30, 10, -20, -30, -30, -20, 10, 30, 30, 30, 0, 0, 0, 0, 30, 30, 50, 30, 30, 30, 30, 30, 30, 50};
    
    int treeDepth = 5;  // Default value
    int bestMoveEvaluation[4]; // evaluation, start, land, promotion
    
    // Functions
    int evaluate(int*);
    int* treeRoot(int);
    int tree(int*, int, int*, int*, int, int, int);
    int* copyArr(int*, int);
};


/*
 Function that move the pieces on the board
 Parameters:
 - char *move = 6 element string containing
 - the move (4 char)
 - the code of the piece to promote in case of promotion (1 char) example: Queen = Q, Knight = N
 Use capital letters for the promotion
 - isWhiteMoving: 1 -> white is moving, 0 -> black is moving
 */
void Board::move(char *move, int isWhiteMoving){
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
    
    if(r1 >= 0 && r1 < 8 && f1 >= 0 && f1 < 8 && r2 >= 0 && r2 < 8 && f2 >= 0 && f2 < 8){
        if(isWhiteMoving == 1){
            // Remove all the right to capture a white pawn en-pasant
            for(int j = 0; j < 8; j++)
                this->captured_enpasant[24 + j] = 0;
            
            if(this->board[start] > 0 && this->board[land] <= 0){
                switch (this->board[start]){
                    case 100: // Pawn
                        if(r1 == 1){ // Starting square
                            if(land - start == 16 && this->board[start + 8] == 0 && this->board[land] == 0){
                                moveIsCorrect = 1;
                                this->captured_enpasant[land] = 1;
                            }
                            else if(land - start == 8 && this->board[land] == 0)
                                moveIsCorrect = 1;
                            else if((land - start == 7 || land - start == 9) && this->board[land] < 0)
                                moveIsCorrect = 1;
                        }
                        else if(r1 == 4){ // En-pasant capture
                            // Normal moves
                            if(land - start == 8 && this->board[land] == 0)
                                moveIsCorrect = 1;
                            else if((land - start == 7 || land - start == 9) && this->board[land] < 0)
                                moveIsCorrect = 1;
                            // En-pasant captures
                            else if(land - start == 9 && this->captured_enpasant[start + 1] == 1){
                                moveIsCorrect = 1;
                                this->board[start + 1] = 0;
                            }
                            else if(land - start == 7 && this->captured_enpasant[start - 1] == 1){
                                moveIsCorrect = 1;
                                this->board[start - 1] = 0;
                            }
                        }
                        else if(r1 == 6){ // Promotion
                            switch (move[4]) {
                                case 'N':
                                    this->board[start] = 310;
                                    break;
                                    
                                case 'B':
                                    this->board[start] = 320;
                                    break;
                                    
                                case 'R':
                                    this->board[start] = 500;
                                    break;
                                    
                                case 'Q':
                                    this->board[start] = 900;
                                    break;
                                    
                                default:
                                    std::cout << "The move made is illegal!" << std::endl;
                                    exit(0);
                                    break;
                            }
                            
                            if(land - start == 8 && this->board[land] == 0){
                                moveIsCorrect = 1;
                            }
                            else if((land - start == 7 || land - start == 9) && this->board[land] < 0){
                                moveIsCorrect = 1;
                            }
                            
                        }
                        else{ // Every other rank
                            if(land - start == 8 && this->board[land] == 0)
                                moveIsCorrect = 1;
                            else if((land - start == 7 || land - start == 9) && this->board[land] < 0)
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
                                if(this->board[start + (i*kr*8) + (i*kf)] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        break;
                        
                    case 500: // Rook
                        // White lose the castling rights
                        if(start == 0) // queenside
                            this->castling_rights[1] = 0;
                        else if(start == 7) //kingside
                            this->castling_rights[0] = 0;
                        
                        if(r1 == r2){
                            int kf = (f2 - f1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(f2 - f1); i++){
                                if(this->board[start + i*kf] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        else if(f1 == f2){
                            int kr = (r2 - r1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(r2 - r1); i++){
                                if(this->board[start + i*kr*8] != 0)
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
                                if(this->board[start + (i*kr*8) + (i*kf)] != 0)
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
                                if(this->board[start + i*kf] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        else if(f1 == f2){
                            int kr = (r2 - r1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(r2 - r1); i++){
                                if(this->board[start + i*kr*8] != 0)
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
                        else if(this->castling_rights[0] == 1 && land == 6 && this->board[5] == 0 && this->board[6] == 0){
                            // Control checks in the way
                            if(this->isCheck(this->board, 1) == 0){
                                this->board[4] = 0;
                                this->board[5] = 1000000;
                                if(this->isCheck(this->board, 1) == 0){
                                    this->board[5] = 0;
                                    this->board[6] = 1000000;
                                    if(this->isCheck(this->board, 1) == 0){
                                        moveIsCorrect = 1;
                                        // Restore king's position
                                        this->board[4] = 1000000;
                                        this->board[6] = 0;
                                        // Move the rook
                                        this->board[7] = 0;
                                        this->board[5] = 500;
                                    }
                                }
                            }
                        }
                        else if(this->castling_rights[1] == 1 && land == 2 && this->board[3] == 0 && this->board[2] == 0 && this->board[1] == 0){
                            // Control checks in the way
                            if(this->isCheck(this->board,1) == 0){
                                this->board[4] = 0;
                                this->board[3] = 1000000;
                                if(this->isCheck(this->board,1) == 0){
                                    this->board[3] = 0;
                                    this->board[2] = 1000000;
                                    if(this->isCheck(this->board,1) == 0){
                                        moveIsCorrect = 1;
                                        // Restore king's position
                                        this->board[4] = 1000000;
                                        this->board[2] = 0;
                                        // Move the rook
                                        this->board[0] = 0;
                                        this->board[3] = 500;
                                    }
                                }
                            }
                        }
                        // white lose all castling rights
                        this->castling_rights[0] = this->castling_rights[1] = 0;
                        
                        break;
                }
            }
        }
        else if(isWhiteMoving == 0){
            // Remove all the right to capture a black pawn en-pasant
            for(int j = 0; j < 8; j++)
                this->captured_enpasant[32 + j] = 0;
            
            if(this->board[start] < 0 && this->board[land] >= 0){
                switch (this->board[start]){
                    case -100: // Pawn
                        if(r1 == 6){ // Starting square
                            if(start - land == 16 && this->board[start - 8] == 0 && this->board[land] == 0){
                                moveIsCorrect = 1;
                                this->captured_enpasant[land] = 1;
                            }
                            else if(start - land == 8 && this->board[land] == 0)
                                moveIsCorrect = 1;
                            else if((start - land == 7 || start - land == 9) && this->board[land] > 0)
                                moveIsCorrect = 1;
                        }
                        else if(r1 == 3){ // En-pasant capture
                            // Normal moves
                            if(start - land == 8 && this->board[land] == 0)
                                moveIsCorrect = 1;
                            else if((start - land == 7 || start - land == 9) && this->board[land] > 0)
                                moveIsCorrect = 1;
                            // En-pasant captures
                            else if(start - land == 7 && this->captured_enpasant[start + 1] == 1){
                                moveIsCorrect = 1;
                                this->board[start + 1] = 0;
                            }
                            else if(start - land == 9 && this->captured_enpasant[start - 1] == 1){
                                moveIsCorrect = 1;
                                this->board[start - 1] = 0;
                            }
                        }
                        else if(r1 == 1){ // Promotion
                            switch (move[4]) {
                                case 'N':
                                    this->board[start] = -310;
                                    break;
                                    
                                case 'B':
                                    this->board[start] = -320;
                                    break;
                                    
                                case 'R':
                                    this->board[start] = -500;
                                    break;
                                    
                                case 'Q':
                                    this->board[start] = -900;
                                    break;
                                    
                                default:
                                    std::cout << "The move made is illegal!" << std::endl;
                                    exit(0);
                                    break;
                            }
                            
                            if(start - land == 8 && this->board[land] == 0){
                                moveIsCorrect = 1;
                            }
                            else if((start - land == 7 || start - land == 9) && this->board[land] > 0){
                                moveIsCorrect = 1;
                            }
                            
                        }
                        else{ // Every other rank
                            if(start - land == 8 && this->board[land] == 0)
                                moveIsCorrect = 1;
                            else if((start - land == 7 || start - land == 9) && this->board[land] > 0)
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
                                if(this->board[start + (i*kr*8) + (i*kf)] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        break;
                        
                    case -500: // Rook
                        // White lose the castling rights
                        if(start == 56) // queenside
                            this->castling_rights[3] = 0;
                        else if(start == 63) //kingside
                            this->castling_rights[2] = 0;
                        
                        if(r1 == r2){
                            int kf = (f2 - f1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(f2 - f1); i++){
                                if(this->board[start + i*kf] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        else if(f1 == f2){
                            int kr = (r2 - r1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(r2 - r1); i++){
                                if(this->board[start + i*kr*8] != 0)
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
                                if(this->board[start + (i*kr*8) + (i*kf)] != 0)
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
                                if(this->board[start + i*kf] != 0)
                                    allEmpty = 0;
                            }
                            
                            if(allEmpty == 1)
                                moveIsCorrect = 1;
                        }
                        else if(f1 == f2){
                            int kr = (r2 - r1 > 0) ? 1 : -1;
                            int allEmpty = 1;
                            
                            for(int i = 1; i < abs(r2 - r1); i++){
                                if(this->board[start + i*kr*8] != 0)
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
                        else if(this->castling_rights[2] == 1 && land == 62 && this->board[61] == 0 && this->board[62] == 0){
                            // Control checks in the way
                            if(this->isCheck(this->board, 0) == 0){
                                this->board[60] = 0;
                                this->board[61] = -1000000;
                                if(this->isCheck(this->board, 0) == 0){
                                    this->board[61] = 0;
                                    this->board[62] = -1000000;
                                    if(this->isCheck(this->board, 0) == 0){
                                        moveIsCorrect = 1;
                                        // Restore king's position
                                        this->board[60] = -1000000;
                                        this->board[62] = 0;
                                        // Move the rook
                                        this->board[63] = 0;
                                        this->board[61] = -500;
                                    }
                                }
                            }
                        }
                        else if(this->castling_rights[3] == 1 && land == 58 && this->board[59] == 0 && this->board[58] == 0 && this->board[57] == 0){
                            // Control checks in the way
                            if(this->isCheck(this->board, 0) == 0){
                                this->board[60] = 0;
                                this->board[59] = -1000000;
                                if(this->isCheck(this->board, 0) == 0){
                                    this->board[59] = 0;
                                    this->board[58] = -1000000;
                                    if(this->isCheck(this->board, 0) == 0){
                                        moveIsCorrect = 1;
                                        // Restore king's position
                                        this->board[60] = -1000000;
                                        this->board[58] = 0;
                                        // Move the rook
                                        this->board[56] = 0;
                                        this->board[59] = -500;
                                    }
                                }
                            }
                        }
                        // black lose all castling rights
                        this->castling_rights[2] = this->castling_rights[3] = 0;
                        
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
        this->board[land] = this->board[start];
        this->board[start] = 0;
        
        if(this->isCheck(this->board, isWhiteMoving) == 1){
            std::cout << "The move made is illegal!" << std::endl;
            exit(0);
        }
    }
    else{
        std::cout << "The move made is illegal!" << std::endl;
        exit(0);
    }
}

// The AI make a move and print out
void Board::AImove(int isWhiteMoving){
    int* temp;
    char move[6];
    
    temp = this->treeRoot(isWhiteMoving);
    
    int f1 = temp[1] % 8;
    int r1 = (temp[1] - f1) / 8;
    int f2 = temp[2] % 8;
    int r2 = (temp[2] - f2) / 8;
    
    // Add the promotions
    switch(std::abs(temp[3])){
        case 310:
            move[4] = 'N';
            break;
            
        case 320:
            move[4] = 'B';
            break;
            
        case 500:
            move[4] = 'R';
            break;
            
        case 900:
            move[4] = 'Q';
            break;
            
        default:
            move[4] = NULL;
            break;
    }
    
    move[0] = (char) (f1 + 97);
    move[1] = (char) (r1 + 49);
    move[2] = (char) (f2 + 97);
    move[3] = (char) (r2 + 49);
    
    std::cout << move << std::endl;
    
    this->move(move, isWhiteMoving);
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
        int r = (index - f) / 8;
        
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
        int r = (index - f) / 8;
        
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


// Set the tree's search depth
void Board::set_treeDepth(int depth){
    if(depth > 0)
        this->treeDepth = depth;
    else
        this->treeDepth = 5;
}


// Set the board position
// There must be 2 kings on the board
void Board::set_board(int* board){
    int whiteKingCount = 0;
    int blackKingCount = 0;
    
    for(int i = 0; i < 64; i++){
        this->board[i] = board[i];
        
        if(this->board[i] == 1000000)
            whiteKingCount++;
        if(this->board[i] == -1000000)
            blackKingCount++;
    }
    
    if(whiteKingCount != 1 || blackKingCount != 1){
        std::cout << "Error setting up the board!" << std::endl;
        exit(1);
    }
}


// Get a 64 int array containing the current board state
int* Board::get_board(){
    for(int i = 0; i < 64; i++)
        this->boardCopy[i] = this->board[i];
    
    return this->boardCopy;
}


void Board::print_bestMove(int isWhiteMoving){
    int* temp;
    char move[6];
    
    temp = this->treeRoot(isWhiteMoving);
    
    std::cout << "Board evaluation = " << temp[0] / 100.0 << std::endl;
    
    int f1 = temp[1] % 8;
    int r1 = (temp[1] - f1) / 8;
    int f2 = temp[2] % 8;
    int r2 = (temp[2] - f2) / 8;
    
    // Add the promotions
    switch(std::abs(temp[3])){
        case 310:
            move[4] = 'N';
            break;
            
        case 320:
            move[4] = 'B';
            break;
            
        case 500:
            move[4] = 'R';
            break;
            
        case 900:
            move[4] = 'Q';
            break;
            
        default:
            move[4] = NULL;
            break;
    }
    
    move[0] = (char) (f1 + 97);
    move[1] = (char) (r1 + 49);
    move[2] = (char) (f2 + 97);
    move[3] = (char) (r2 + 49);
    
    std::cout << move << std::endl;
}


// Define ANSI codes for Mac OS
#define WHITE_LIGHT  "\x1b[37;46m"
#define WHITE_DARK   "\x1b[37;42m"
#define BLACK_LIGHT  "\x1b[30;46m"
#define BLACK_DARK   "\x1b[30;42m"
#define NORMAL       "\x1b[0m"

/*  TODO
 CHANGE THE DISPLAY
 
 +---+---+---+---+---+---+---+---+
 | R | N | B | Q | K | B | N | R |
 +---+---+---+---+---+---+---+---+
 | P | P | P | P | P | P | P | P |
 +---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   |   |   |
 +---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   |   |   |
 +---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   |   |   |
 +---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   |   |   |
 +---+---+---+---+---+---+---+---+
 | P | P | P | P | P | P | P | P |
 +---+---+---+---+---+---+---+---+
 | R | N | B | Q | K | B | N | R |
 +---+---+---+---+---+---+---+---+
 
 Better vision also without colors.
 */

// Display the board
// Parameter: view mode 1 or 2
void Board::displayBoard(int view){
    std::cout << std::endl;
    switch (view) {
        case 1:
            // Display the board using only ASCII characters
            // Compatible with all OS
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
            break;
            
        case 2:
            // Display the board only in the Mac OS terminal
            // It uses ANSI codes for the colors
            // Better view than view=1
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
            break;
            
        default:
            std::cout << "Wrong view selection" << std::endl;
            exit(1);
            break;
    }
    std::cout << std::endl;
}


// Parameter:
//      - an 8x8 board -> array [64]
int Board::evaluate(int *board){
    int evaluation = 0;
    
    // Count the number of pawn per file and initialize to 0
    int pawnFile_white[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int pawnFile_black[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    
    int pieceValueCount = 0;    // To know when it go in the endgame
    int whiteKing_index = 0, blackKing_index = 0;   // Index of kings
    
    for(int k = 0; k < 64; k++){
        // Add the value of the piece
        evaluation += board[k];
        
        // Add the module of all pieces to know when is the endgame
        pieceValueCount += abs(board[k]);
        
        // Decide which piece-square table use
        switch (board[k]) {
            case 0: {
                break;
            }
                
            case 100: {
                evaluation += (this->whitePawn_eval[k] + this->whitePawn_passed[k]);
                
                int f = k % 8;
                int r = (k - f) / 8;
                
                pawnFile_white[f]++;
                
                if(f == 0){
                    for(int i = r + 1; i < 6; i++){
                        if(board[i*8 + f] == -100 || board[i*8 + f + 1] == -100){
                            // Remove the given points
                            evaluation -= this->whitePawn_passed[k];
                            break;
                        }
                    }
                }
                else if(f == 7){
                    for(int i = r + 1; i < 6; i++){
                        if(board[i*8 + f - 1] == -100 || board[i*8 + f] == -100){
                            // Remove the given points
                            evaluation -= this->whitePawn_passed[k];
                            break;
                        }
                    }
                }
                else{
                    for(int i = r + 1; i < 6; i++){
                        if(board[i*8 + f - 1] == -100 || board[i*8 + f] == -100 || board[i*8 + f + 1] == -100){
                            // Remove the given points
                            evaluation -= this->whitePawn_passed[k];
                            break;
                        }
                    }
                }
                
                break;
            }
                
            case 310: {
                evaluation += this->whiteKnight_eval[k];
                break;
            }
                
            case 320: {
                evaluation += this->whiteBishop_eval[k];
                break;
            }
                
            case 500: {
                // Add 10cp more assiuming is on an opne file
                evaluation += (this->whiteRook_eval[k] + 10);
                
                // Rook on an open file
                int f = k % 8;
                
                for(int i = 0; i < 8; i++){
                    if(abs(board[i*8 + f]) == 100){
                        // Subtract 10cp if is not on an open file
                        evaluation -= 10;
                        break;
                    }
                }
                break;
            }
                
            case 900: {
                evaluation += this->whiteQueen_eval[k];
                break;
            }
                
            case 1000000: {   // Save the coords for after
                whiteKing_index = k;
                break;
            }
                
            case -100: {
                evaluation += (this->blackPawn_eval[k] + this->blackPawn_passed[k]);
                
                int f = k % 8;
                int r = (k - f) / 8;
                
                pawnFile_black[f]++;
                
                if(f == 0){
                    for(int i = r - 1; i > 1; i--){
                        if(board[i*8 + f] == 100 || board[i*8 + f + 1] == 100){
                            // Remove the given points
                            evaluation -= this->blackPawn_passed[k];
                            break;
                        }
                    }
                }
                else if(f == 7){
                    for(int i = r - 1; i > 1; i--){
                        if(board[i*8 + f - 1] == 100 || board[i*8 + f] == 100){
                            // Remove the given points
                            evaluation -= this->blackPawn_passed[k];
                            break;
                        }
                    }
                }
                else{
                    for(int i = r - 1; i > 1; i--){
                        if(board[i*8 + f - 1] == 100 || board[i*8 + f] == 100 || board[i*8 + f + 1] == 100){
                            // Remove the given points
                            evaluation -= this->blackPawn_passed[k];
                            break;
                        }
                    }
                }
                
                break;
            }
                
            case -310: {
                evaluation += this->blackKnight_eval[k];
                break;
            }
                
            case -320: {
                evaluation += this->blackBishop_eval[k];
                break;
            }
                
            case -500: {
                // Subtract 10cp more assiuming is on an opne file
                evaluation += (this->blackRook_eval[k] - 10);
                
                // Rook on an open file
                int f = k % 8;
                
                for(int i = 0; i < 8; i++){
                    if(abs(board[i*8 + f]) == 100){
                        // Add 10cp if is not on an open file
                        evaluation += 10;
                        break;
                    }
                }
                break;
            }
                
            case -900: {
                evaluation += this->blackQueen_eval[k];
                break;
            }
                
            case -1000000: {  // Save the coords for after
                blackKing_index = k;
                break;
            }
                
            default: {
                std::cout << "Error in evaluating the position!" << std::endl;
                exit(1);
                break;
            }
        }
    }
    
    // Evaluate the pawns islands
    int islandCount_white = 0;
    int islandCount_black = 0;
    
    if(pawnFile_white[0] > 0)
        islandCount_white++;
    
    for(int i = 1; i < 8; i++){
        if(pawnFile_white[i-1] == 0 && pawnFile_white[i] > 0){
            islandCount_white++;
        }
        if(pawnFile_white[i] > 1){
            // Double or triple pawn (30cp malus)
            evaluation -= 30;
        }
    }
    
    if(pawnFile_black[0] > 0)
        islandCount_black++;
    
    for(int i = 1; i < 8; i++){
        if(pawnFile_black[i-1] == 0 && pawnFile_black[i] > 0){
            islandCount_black++;
        }
        if(pawnFile_black[i] > 1){
            // Double or triple pawn (30cp malus)
            evaluation += 30;
        }
    }
    
    // Calculate the difference of pawn island and add a malus of 15 cp per each island
    evaluation += (islandCount_black - islandCount_white)*15;
    
    // If the sum of the module of all pieces is less than 2003600 we are in the endgame
    // 2003600 is exactly:
    // 1 King + 1 Queen + 1 Rook + 4 Pawn each or equivalent
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


// Root of the tree
int* Board::treeRoot(int isWhiteMoving){
    // Initialize alpha beta
    int alpha = -1000000000;
    int beta = 1000000000;
    
    // Store here all possible arrays
    int *temp_board;
    int *temp_enpasant;
    int *temp_rights;
    
    int maxDepth = this->treeDepth - 1; // Reduce by 1 the depth
    
    int possible_moves = 0;     // Number of possible moves
    
    if(isWhiteMoving == 1){ // Maximising player
        this->bestMoveEvaluation[0] = -1000000000; // Evaluation of the best move
        isWhiteMoving = 0;
        
        for(int j = 0; j < 8; j++)
            this->captured_enpasant[24 + j] = 0;
        
        for(int index = 0; index < 64; index++){
            if(this->board[index] > 0){
                int f = index % 8;
                int r = (index - f) / 8;
                
                switch(this->board[index]){
                    case 100:
                        if(r == 1){
                            if(this->board[index + 8] == 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 8] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 8;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + 8] == 0 && this->board[index + 16] == 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 16] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    temp_enpasant[index + 16] = 1;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 16;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f - 1 >= 0 && this->board[index + 7] < 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 7] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 7;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f + 1 < 8 && this->board[index + 9] < 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 9] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 9;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                        }
                        else if(r == 4){
                            if(this->board[index + 8] == 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 8] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 8;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f - 1 >= 0 && this->board[index + 7] < 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 7] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 7;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f + 1 < 8 && this->board[index + 9] < 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 9] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 9;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f - 1 >= 0 && this->captured_enpasant[index - 1] == 1){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 7] = temp_board[index];
                                temp_board[index] = 0;
                                temp_board[index - 1] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 7;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f + 1 < 8 && this->captured_enpasant[index + 1] == 1){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 9] = temp_board[index];
                                temp_board[index] = 0;
                                temp_board[index + 1] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 9;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                        }
                        else if(r == 6){
                            if(this->board[index + 8] == 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 8] = 900;
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 8;
                                        this->bestMoveEvaluation[3] = 900;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index + 8] = 500;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 8;
                                        this->bestMoveEvaluation[3] = 500;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index + 8] = 320;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 8;
                                        this->bestMoveEvaluation[3] = 320;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index + 8] = 310;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 8;
                                        this->bestMoveEvaluation[3] = 310;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f - 1 >= 0 && this->board[index + 7] < 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 7] = 900;
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 7;
                                        this->bestMoveEvaluation[3] = 900;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index + 7] = 500;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 7;
                                        this->bestMoveEvaluation[3] = 500;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index + 7] = 320;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 7;
                                        this->bestMoveEvaluation[3] = 320;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index + 7] = 310;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 7;
                                        this->bestMoveEvaluation[3] = 310;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f + 1 < 8 && this->board[index + 9] < 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 9] = 900;
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 9;
                                        this->bestMoveEvaluation[3] = 900;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index + 9] = 500;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 9;
                                        this->bestMoveEvaluation[3] = 500;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index + 9] = 320;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 9;
                                        this->bestMoveEvaluation[3] = 320;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index + 9] = 310;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 9;
                                        this->bestMoveEvaluation[3] = 310;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                        }
                        else{
                            if(this->board[index + 8] == 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 8] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 8;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f - 1 >= 0 && this->board[index + 7] < 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 7] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 7;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f + 1 < 8 && this->board[index + 9] < 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 9] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 9;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                        }
                        break;
                        
                    case 310:
                        if(r+2 >= 0 && r+2 < 8 && f+1 >= 0 && f+1 < 8 && this->board[index + 17] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 17] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 17;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r+1 >= 0 && r+1 < 8 && f+2 >= 0 && f+2 < 8 && this->board[index + 10] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 10] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 10;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r-1 >= 0 && r-1 < 8 && f+2 >= 0 && f+2 < 8 && this->board[index - 6] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index -6] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 6;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r-2 >= 0 && r-2 < 8 && f+1 >= 0 && f+1 < 8 && this->board[index - 15] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 15] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 15;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r-2 >= 0 && r-2 < 8 && f-1 >= 0 && f-1 < 8 && this->board[index - 17] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 17] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 17;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r-1 >= 0 && r-1 < 8 && f-2 >= 0 && f-2 < 8 && this->board[index - 10] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 10] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 10;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r+1 >= 0 && r+1 < 8 && f-2 >= 0 && f-2 < 8 && this->board[index + 6] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 6] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 6;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r+2 >= 0 && r+2 < 8 && f-1 >= 0 && f-1 < 8 && this->board[index + 15] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 15] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 15;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        break;
                        
                    case 320:
                        for(int i = 1; r + i < 8 && f + i < 8; i++){
                            if(this->board[index + 9*i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 9*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 9*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + 9*i] != 0)
                                break;
                        }
                        for(int i = 1; r - i >= 0 && f + i < 8; i++){
                            if(this->board[index - 7*i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 7*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 7*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - 7*i] != 0)
                                break;
                        }
                        for(int i = 1; r - i >= 0 && f - i >= 0; i++){
                            if(this->board[index - 9*i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 9*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 9*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - 9*i] != 0)
                                break;
                        }
                        for(int i = 1; r + i < 8 && f - i >= 0; i++){
                            if(this->board[index + 7*i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 7*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 7*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + 7*i] != 0)
                                break;
                        }
                        break;
                        
                    case 500:
                        for(int i = 1; r + i < 8; i++){
                            if(this->board[index + 8*i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 8*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    if(index == 0) // queenside
                                        temp_rights[1] = 0;
                                    else if(index == 7) //kingside
                                        temp_rights[0] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 8*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + 8*i] != 0)
                                break;
                        }
                        for(int i = 1; f + i < 8; i++){
                            if(this->board[index + i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    if(index == 0) // queenside
                                        temp_rights[1] = 0;
                                    else if(index == 7) //kingside
                                        temp_rights[0] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + i] != 0)
                                break;
                        }
                        for(int i = 1; r - i >= 0; i++){
                            if(this->board[index - 8*i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 8*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    if(index == 0) // queenside
                                        temp_rights[1] = 0;
                                    else if(index == 7) //kingside
                                        temp_rights[0] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 8*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - 8*i] != 0)
                                break;
                        }
                        for(int i = 1; f - i >= 0; i++){
                            if(this->board[index - i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    if(index == 0) // queenside
                                        temp_rights[1] = 0;
                                    else if(index == 7) //kingside
                                        temp_rights[0] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - i] != 0)
                                break;
                        }
                        break;
                        
                    case 900:
                        for(int i = 1; r + i < 8 && f + i < 8; i++){
                            if(this->board[index + 9*i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 9*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 9*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + 9*i] != 0)
                                break;
                        }
                        for(int i = 1; r - i >= 0 && f + i < 8; i++){
                            if(this->board[index - 7*i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 7*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 7*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - 7*i] != 0)
                                break;
                        }
                        for(int i = 1; r - i >= 0 && f - i >= 0; i++){
                            if(this->board[index - 9*i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 9*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 9*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - 9*i] != 0)
                                break;
                        }
                        for(int i = 1; r + i < 8 && f - i >= 0; i++){
                            if(this->board[index + 7*i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 7*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 7*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + 7*i] != 0)
                                break;
                        }
                        for(int i = 1; r + i < 8; i++){
                            if(this->board[index + 8*i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 8*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 8*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + 8*i] != 0)
                                break;
                        }
                        for(int i = 1; f + i < 8; i++){
                            if(this->board[index + i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + i] != 0)
                                break;
                        }
                        for(int i = 1; r - i >= 0; i++){
                            if(this->board[index - 8*i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 8*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 8*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - 8*i] != 0)
                                break;
                        }
                        for(int i = 1; f - i >= 0; i++){
                            if(this->board[index - i] <= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - i] != 0)
                                break;
                        }
                        break;
                        
                    case 1000000:
                        if(r + 1 < 8 && this->board[index + 8] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 8] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[0] = temp_rights[1] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 8;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r + 1 < 8 && f + 1 < 8 && this->board[index + 9] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 9] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[0] = temp_rights[1] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 9;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(f + 1 < 8 && this->board[index + 1] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 1] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[0] = temp_rights[1] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 1;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r - 1 >= 0 && f + 1 < 8 && this->board[index - 7] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 7] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[0] = temp_rights[1] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 7;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r - 1 >= 0 && this->board[index - 8] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 8] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[0] = temp_rights[1] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 8;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r - 1 >= 0 && f - 1 <= 0 && this->board[index - 9] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 9] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[0] = temp_rights[1] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 9;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(f - 1 >= 0 && this->board[index - 1] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 1] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[0] = temp_rights[1] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 1;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r + 1 < 8 && f - 1 >= 0 && this->board[index + 7] <= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 7] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 1) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[0] = temp_rights[1] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score > this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 7;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(alpha < score)
                                    alpha = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(index == 4){
                            if(this->castling_rights[0] == 1 && this->board[5] == 0 && this->board[6] == 0){
                                if(this->isCheck(this->board, 1) == 0){
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[4] = 0;
                                    temp_board[5] = 1000000;
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_board[5] = 500;
                                        temp_board[6] = 1000000;
                                        temp_board[7] = 0;
                                        if(this->isCheck(temp_board, 1) == 0){
                                            temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                            temp_rights = this->copyArr(this->castling_rights, 4);
                                            
                                            temp_rights[0] = temp_rights[1] = 0;
                                            
                                            int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                            possible_moves++;
                                            
                                            if(score > this->bestMoveEvaluation[0]){
                                                this->bestMoveEvaluation[0] = score;
                                                this->bestMoveEvaluation[1] = index;
                                                this->bestMoveEvaluation[2] = index + 2;
                                            }
                                            
                                            delete temp_enpasant;
                                            delete temp_rights;
                                            
                                            if(alpha < score)
                                                alpha = score;
                                            
                                            if(beta <= alpha){
                                                delete temp_board;
                                                return this->bestMoveEvaluation;
                                            }
                                        }
                                    }
                                    delete temp_board;
                                }
                            }
                            else if(this->castling_rights[1] == 1 && this->board[3] == 0 && this->board[2] == 0 && this->board[1] == 0){
                                if(this->isCheck(this->board, 1) == 0){
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[4] = 0;
                                    temp_board[3] = 1000000;
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_board[3] = 500;
                                        temp_board[2] = 1000000;
                                        temp_board[0] = 0;
                                        if(this->isCheck(temp_board, 1) == 0){
                                            temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                            temp_rights = this->copyArr(this->castling_rights, 4);
                                            
                                            temp_rights[0] = temp_rights[1] = 0;
                                            
                                            int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                            possible_moves++;
                                            
                                            if(score > this->bestMoveEvaluation[0]){
                                                this->bestMoveEvaluation[0] = score;
                                                this->bestMoveEvaluation[1] = index;
                                                this->bestMoveEvaluation[2] = index - 2;
                                            }
                                            
                                            delete temp_enpasant;
                                            delete temp_rights;
                                            
                                            if(alpha < score)
                                                alpha = score;
                                            
                                            if(beta <= alpha){
                                                delete temp_board;
                                                return this->bestMoveEvaluation;
                                            }
                                        }
                                    }
                                    delete temp_board;
                                }
                            }
                        }
                        break;
                }
            }
        }
        
        // Check is stalemate
        if(possible_moves == 0 && this->isCheck(this->board, 1) == 0)
            return 0;
        
        return this->bestMoveEvaluation;
    }
    else if(isWhiteMoving == 0){ // Minimising player
        this->bestMoveEvaluation[0] = 1000000000; // Evaluation of the best move
        isWhiteMoving = 1;
        
        for(int j = 0; j < 8; j++)
            this->captured_enpasant[32 + j] = 0;
        
        for(int index = 63; index >= 0; index--){
            if(this->board[index] < 0){
                int f = index % 8;
                int r = (index - f) / 8;
                
                switch(this->board[index]){
                    case -100:
                        if(r == 6){
                            if(this->board[index - 8] == 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 8] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 8;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - 8] == 0 && this->board[index - 16] == 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 16] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    temp_enpasant[index - 16] = 1;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 16;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f - 1 >= 0 && this->board[index - 9] > 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 9] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 9;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f + 1 < 8 && this->board[index - 7] > 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 7] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 7;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                        }
                        else if(r == 3){
                            if(this->board[index - 8] == 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 8] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 8;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f - 1 >= 0 && this->board[index - 9] > 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 9] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 9;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f + 1 < 8 && this->board[index - 7] > 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 7] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 7;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f - 1 >= 0 && this->captured_enpasant[index - 1] == 1){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 9] = temp_board[index];
                                temp_board[index] = 0;
                                temp_board[index - 1] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 9;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f + 1 < 8 && this->captured_enpasant[index + 1] == 1){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 7] = temp_board[index];
                                temp_board[index] = 0;
                                temp_board[index + 1] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 7;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                        }
                        else if(r == 1){
                            if(this->board[index - 8] == 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 8] = -900;
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 8;
                                        this->bestMoveEvaluation[3] = -900;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index - 8] = -500;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 8;
                                        this->bestMoveEvaluation[3] = -500;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index - 8] = -320;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 8;
                                        this->bestMoveEvaluation[3] = -320;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index - 8] = -310;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 8;
                                        this->bestMoveEvaluation[3] = -310;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f - 1 >= 0 && this->board[index - 9] > 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 9] = -900;
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 9;
                                        this->bestMoveEvaluation[3] = -900;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index - 9] = -500;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 9;
                                        this->bestMoveEvaluation[3] = -500;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index - 9] = -320;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 9;
                                        this->bestMoveEvaluation[3] = -320;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index - 9] = -310;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 9;
                                        this->bestMoveEvaluation[3] = -310;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f + 1 < 8 && this->board[index - 7] > 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 7] = -900;
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 7;
                                        this->bestMoveEvaluation[3] = -900;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index - 7] = -500;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 7;
                                        this->bestMoveEvaluation[3] = -500;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index - 7] = -320;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 7;
                                        this->bestMoveEvaluation[3] = -320;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                    
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[index - 7] = -310;
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 7;
                                        this->bestMoveEvaluation[3] = -310;
                                    }
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                        }
                        else{
                            if(this->board[index - 8] == 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 8] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 8;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f - 1 >= 0 && this->board[index - 9] > 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 9] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 9;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f + 1 < 8 && this->board[index - 7] > 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 7] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 7;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                        }
                        break;
                        
                    case -310:
                        if(r+2 >= 0 && r+2 < 8 && f+1 >= 0 && f+1 < 8 && this->board[index + 17] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 17] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 17;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r+1 >= 0 && r+1 < 8 && f+2 >= 0 && f+2 < 8 && this->board[index + 10] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 10] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 10;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r-1 >= 0 && r-1 < 8 && f+2 >= 0 && f+2 < 8 && this->board[index - 6] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 6] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 6;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r-2 >= 0 && r-2 < 8 && f+1 >= 0 && f+1 < 8 && this->board[index - 15] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 15] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 15;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r-2 >= 0 && r-2 < 8 && f-1 >= 0 && f-1 < 8 && this->board[index - 17] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 17] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 17;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r-1 >= 0 && r-1 < 8 && f-2 >= 0 && f-2 < 8 && this->board[index - 10] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 10] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 10;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r+1 >= 0 && r+1 < 8 && f-2 >= 0 && f-2 < 8 && this->board[index + 6] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 6] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 6;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r+2 >= 0 && r+2 < 8 && f-1 >= 0 && f-1 < 8 && this->board[index + 15] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 15] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 15;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        break;
                        
                    case -320:
                        for(int i = 1; r + i < 8 && f + i < 8; i++){
                            if(this->board[index + 9*i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 9*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 9*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + 9*i] != 0)
                                break;
                        }
                        for(int i = 1; r - i >= 0 && f + i < 8; i++){
                            if(this->board[index - 7*i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 7*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 7*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - 7*i] != 0)
                                break;
                        }
                        for(int i = 1; r - i >= 0 && f - i >= 0; i++){
                            if(this->board[index - 9*i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 9*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 9*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - 9*i] != 0)
                                break;
                        }
                        for(int i = 1; r + i < 8 && f - i >= 0; i++){
                            if(this->board[index + 7*i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 7*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 7*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + 7*i] != 0)
                                break;
                        }
                        break;
                        
                    case -500:
                        for(int i = 1; r + i < 8; i++){
                            if(this->board[index + 8*i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 8*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    if(index == 56) // queenside
                                        temp_rights[3] = 0;
                                    else if(index == 63) //kingside
                                        temp_rights[2] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 8*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + 8*i] != 0)
                                break;
                        }
                        for(int i = 1; f + i < 8; i++){
                            if(this->board[index + i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    if(index == 56) // queenside
                                        temp_rights[3] = 0;
                                    else if(index == 63) //kingside
                                        temp_rights[2] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + i] != 0)
                                break;
                        }
                        for(int i = 1; r - i >= 0; i++){
                            if(this->board[index - 8*i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 8*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    if(index == 56) // queenside
                                        temp_rights[3] = 0;
                                    else if(index == 63) //kingside
                                        temp_rights[2] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 8*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - 8*i] != 0)
                                break;
                        }
                        for(int i = 1; f - i >= 0; i++){
                            if(this->board[index - i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    if(index == 56) // queenside
                                        temp_rights[3] = 0;
                                    else if(index == 63) //kingside
                                        temp_rights[2] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - i] != 0)
                                break;
                        }
                        break;
                        
                    case -900:
                        for(int i = 1; r + i < 8 && f + i < 8; i++){
                            if(this->board[index + 9*i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 9*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 9*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + 9*i] != 0)
                                break;
                        }
                        for(int i = 1; r - i >= 0 && f + i < 8; i++){
                            if(this->board[index - 7*i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 7*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 7*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - 7*i] != 0)
                                break;
                        }
                        for(int i = 1; r - i >= 0 && f - i >= 0; i++){
                            if(this->board[index - 9*i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 9*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 9*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - 9*i] != 0)
                                break;
                        }
                        for(int i = 1; r + i < 8 && f - i >= 0; i++){
                            if(this->board[index + 7*i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 7*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 7*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + 7*i] != 0)
                                break;
                        }
                        for(int i = 1; r + i < 8; i++){
                            if(this->board[index + 8*i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + 8*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + 8*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + 8*i] != 0)
                                break;
                        }
                        for(int i = 1; f + i < 8; i++){
                            if(this->board[index + i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index + i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index + i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index + i] != 0)
                                break;
                        }
                        for(int i = 1; r - i >= 0; i++){
                            if(this->board[index - 8*i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - 8*i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - 8*i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - 8*i] != 0)
                                break;
                        }
                        for(int i = 1; f - i >= 0; i++){
                            if(this->board[index - i] >= 0){
                                temp_board = this->copyArr(this->board, 64);
                                temp_board[index - i] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                    temp_rights = this->copyArr(this->castling_rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < this->bestMoveEvaluation[0]){
                                        this->bestMoveEvaluation[0] = score;
                                        this->bestMoveEvaluation[1] = index;
                                        this->bestMoveEvaluation[2] = index - i;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return this->bestMoveEvaluation;
                                    }
                                }
                                delete temp_board;
                            }
                            if(this->board[index - i] != 0)
                                break;
                        }
                        break;
                        
                    case -1000000:
                        if(r + 1 < 8 && this->board[index + 8] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 8] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[2] = temp_rights[3] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 8;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r + 1 < 8 && f + 1 < 8 && this->board[index + 9] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 9] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[2] = temp_rights[3] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 9;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(f + 1 < 8 && this->board[index + 1] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 1] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[2] = temp_rights[3] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 1;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r - 1 >= 0 && f + 1 < 8 && this->board[index - 7] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 7] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[2] = temp_rights[3] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 7;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r - 1 >= 0 && this->board[index - 8] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 8] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[2] = temp_rights[3] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 8;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r - 1 >= 0 && f - 1 <= 0 && this->board[index - 9] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 9] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[2] = temp_rights[3] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 9;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(f - 1 >= 0 && this->board[index - 1] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index - 1] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[2] = temp_rights[3] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index - 1;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(r + 1 < 8 && f - 1 >= 0 && this->board[index + 7] >= 0){
                            temp_board = this->copyArr(this->board, 64);
                            temp_board[index + 7] = temp_board[index];
                            temp_board[index] = 0;
                            
                            if(this->isCheck(temp_board, 0) == 0){
                                temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                temp_rights = this->copyArr(this->castling_rights, 4);
                                
                                temp_rights[2] = temp_rights[3] = 0;
                                
                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                possible_moves++;
                                
                                if(score < this->bestMoveEvaluation[0]){
                                    this->bestMoveEvaluation[0] = score;
                                    this->bestMoveEvaluation[1] = index;
                                    this->bestMoveEvaluation[2] = index + 7;
                                }
                                
                                delete temp_enpasant;
                                delete temp_rights;
                                
                                if(beta > score)
                                    beta = score;
                                
                                if(beta <= alpha){
                                    delete temp_board;
                                    return this->bestMoveEvaluation;
                                }
                            }
                            delete temp_board;
                        }
                        if(index == 60){
                            if(this->castling_rights[2] == 1 && this->board[61] == 0 && this->board[62] == 0){
                                if(this->isCheck(this->board, 0) == 0){
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[60] = 0;
                                    temp_board[61] = -1000000;
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_board[61] = -500;
                                        temp_board[62] = -1000000;
                                        temp_board[63] = 0;
                                        if(this->isCheck(temp_board, 0) == 0){
                                            temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                            temp_rights = this->copyArr(this->castling_rights, 4);
                                            
                                            temp_rights[2] = temp_rights[3] = 0;
                                            
                                            int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                            possible_moves++;
                                            
                                            if(score < this->bestMoveEvaluation[0]){
                                                this->bestMoveEvaluation[0] = score;
                                                this->bestMoveEvaluation[1] = index;
                                                this->bestMoveEvaluation[2] = index + 2;
                                            }
                                            
                                            delete temp_enpasant;
                                            delete temp_rights;
                                            
                                            if(beta > score)
                                                beta = score;
                                            
                                            if(beta <= alpha){
                                                delete temp_board;
                                                return this->bestMoveEvaluation;
                                            }
                                        }
                                    }
                                    delete temp_board;
                                }
                            }
                            else if(this->castling_rights[3] == 1 && this->board[59] == 0 && this->board[58] == 0 && this->board[57] == 0){
                                if(this->isCheck(this->board, 0) == 0){
                                    temp_board = this->copyArr(this->board, 64);
                                    temp_board[60] = 0;
                                    temp_board[59] = -1000000;
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_board[59] = -500;
                                        temp_board[58] = -1000000;
                                        temp_board[56] = 0;
                                        if(this->isCheck(temp_board, 1) == 0){
                                            temp_enpasant = this->copyArr(this->captured_enpasant, 64);
                                            temp_rights = this->copyArr(this->castling_rights, 4);
                                            
                                            temp_rights[2] = temp_rights[3] = 0;
                                            
                                            int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                            possible_moves++;
                                            
                                            if(score < this->bestMoveEvaluation[0]){
                                                this->bestMoveEvaluation[0] = score;
                                                this->bestMoveEvaluation[1] = index;
                                                this->bestMoveEvaluation[2] = index - 2;
                                            }
                                            
                                            delete temp_enpasant;
                                            delete temp_rights;
                                            
                                            if(beta > score)
                                                beta = score;
                                            
                                            if(beta <= alpha){
                                                delete temp_board;
                                                return this->bestMoveEvaluation;
                                            }
                                        }
                                    }
                                    delete temp_board;
                                }
                            }
                        }
                        break;
                }
            }
        }
        
        // Check is stalemate
        if(possible_moves == 0 && this->isCheck(this->board, 0) == 0)
            return 0;
        
        return this->bestMoveEvaluation;
    }
    else{
        std::cout << "Error generating the tree" << std::endl;
        exit(1);
    }
}


// Generate the tree containing all the possible moves and
// evaluate the position using minimax
int Board::tree(int *board, int isWhiteMoving, int *enpasant, int *rights, int maxDepth, int alpha, int beta){
    if(maxDepth > 0){
        // Store here all possible arrays
        int *temp_board;
        int *temp_enpasant;
        int *temp_rights;
        
        maxDepth--;     // Reduce by 1 the depth
        int possible_moves = 0;     // Number of possible moves
        
        if(isWhiteMoving == 1){ // Maximising player
            int bestMove = -1000000000; // Evaluation of the best move
            isWhiteMoving = 0;
            
            for(int j = 0; j < 8; j++)
                enpasant[24 + j] = 0;
            
            for(int index = 0; index < 64; index++){
                if(board[index] > 0){
                    int f = index % 8;
                    int r = (index - f) / 8;
                    
                    switch(board[index]){
                        case 100:
                            if(r == 1){
                                if(board[index + 8] == 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 8] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + 8] == 0 && board[index + 16] == 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 16] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        temp_enpasant[index + 16] = 1;
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f - 1 >= 0 && board[index + 7] < 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 7] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f + 1 < 8 && board[index + 9] < 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 9] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                            }
                            else if(r == 4){
                                if(board[index + 8] == 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 8] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f - 1 >= 0 && board[index + 7] < 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 7] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f + 1 < 8 && board[index + 9] < 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 9] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f - 1 >= 0 && enpasant[index - 1] == 1){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 7] = temp_board[index];
                                    temp_board[index] = 0;
                                    temp_board[index - 1] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f + 1 < 8 && enpasant[index + 1] == 1){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 9] = temp_board[index];
                                    temp_board[index] = 0;
                                    temp_board[index + 1] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                            }
                            else if(r == 6){
                                if(board[index + 8] == 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 8] = 900;
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index + 8] = 500;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index + 8] = 320;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index + 8] = 310;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f - 1 >= 0 && board[index + 7] < 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 7] = 900;
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index + 7] = 500;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index + 7] = 320;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index + 7] = 310;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f + 1 < 8 && board[index + 9] < 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 9] = 900;
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index + 9] = 500;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index + 9] = 320;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index + 9] = 310;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                            }
                            else{
                                if(board[index + 8] == 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 8] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f - 1 >= 0 && board[index + 7] < 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 7] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f + 1 < 8 && board[index + 9] < 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 9] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                            }
                            break;
                            
                        case 310:
                            if(r+2 >= 0 && r+2 < 8 && f+1 >= 0 && f+1 < 8 && board[index + 17] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 17] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r+1 >= 0 && r+1 < 8 && f+2 >= 0 && f+2 < 8 && board[index + 10] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 10] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r-1 >= 0 && r-1 < 8 && f+2 >= 0 && f+2 < 8 && board[index - 6] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index -6] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r-2 >= 0 && r-2 < 8 && f+1 >= 0 && f+1 < 8 && board[index - 15] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index - 15] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r-2 >= 0 && r-2 < 8 && f-1 >= 0 && f-1 < 8 && board[index - 17] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index - 17] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r-1 >= 0 && r-1 < 8 && f-2 >= 0 && f-2 < 8 && board[index - 10] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index - 10] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r+1 >= 0 && r+1 < 8 && f-2 >= 0 && f-2 < 8 && board[index + 6] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 6] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r+2 >= 0 && r+2 < 8 && f-1 >= 0 && f-1 < 8 && board[index + 15] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 15] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            break;
                            
                        case 320:
                            for(int i = 1; r + i < 8 && f + i < 8; i++){
                                if(board[index + 9*i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 9*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + 9*i] != 0)
                                    break;
                            }
                            for(int i = 1; r - i >= 0 && f + i < 8; i++){
                                if(board[index - 7*i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 7*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - 7*i] != 0)
                                    break;
                            }
                            for(int i = 1; r - i >= 0 && f - i >= 0; i++){
                                if(board[index - 9*i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 9*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - 9*i] != 0)
                                    break;
                            }
                            for(int i = 1; r + i < 8 && f - i >= 0; i++){
                                if(board[index + 7*i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 7*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + 7*i] != 0)
                                    break;
                            }
                            break;
                            
                        case 500:
                            for(int i = 1; r + i < 8; i++){
                                if(board[index + 8*i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 8*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        if(index == 0) // queenside
                                            temp_rights[1] = 0;
                                        else if(index == 7) //kingside
                                            temp_rights[0] = 0;
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + 8*i] != 0)
                                    break;
                            }
                            for(int i = 1; f + i < 8; i++){
                                if(board[index + i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        if(index == 0) // queenside
                                            temp_rights[1] = 0;
                                        else if(index == 7) //kingside
                                            temp_rights[0] = 0;
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + i] != 0)
                                    break;
                            }
                            for(int i = 1; r - i >= 0; i++){
                                if(board[index - 8*i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 8*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        if(index == 0) // queenside
                                            temp_rights[1] = 0;
                                        else if(index == 7) //kingside
                                            temp_rights[0] = 0;
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - 8*i] != 0)
                                    break;
                            }
                            for(int i = 1; f - i >= 0; i++){
                                if(board[index - i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        if(index == 0) // queenside
                                            temp_rights[1] = 0;
                                        else if(index == 7) //kingside
                                            temp_rights[0] = 0;
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - i] != 0)
                                    break;
                            }
                            break;
                            
                        case 900:
                            for(int i = 1; r + i < 8 && f + i < 8; i++){
                                if(board[index + 9*i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 9*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + 9*i] != 0)
                                    break;
                            }
                            for(int i = 1; r - i >= 0 && f + i < 8; i++){
                                if(board[index - 7*i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 7*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - 7*i] != 0)
                                    break;
                            }
                            for(int i = 1; r - i >= 0 && f - i >= 0; i++){
                                if(board[index - 9*i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 9*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - 9*i] != 0)
                                    break;
                            }
                            for(int i = 1; r + i < 8 && f - i >= 0; i++){
                                if(board[index + 7*i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 7*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + 7*i] != 0)
                                    break;
                            }
                            for(int i = 1; r + i < 8; i++){
                                if(board[index + 8*i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 8*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + 8*i] != 0)
                                    break;
                            }
                            for(int i = 1; f + i < 8; i++){
                                if(board[index + i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + i] != 0)
                                    break;
                            }
                            for(int i = 1; r - i >= 0; i++){
                                if(board[index - 8*i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 8*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - 8*i] != 0)
                                    break;
                            }
                            for(int i = 1; f - i >= 0; i++){
                                if(board[index - i] <= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 1) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score > bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(alpha < score)
                                            alpha = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - i] != 0)
                                    break;
                            }
                            break;
                            
                        case 1000000:
                            if(r + 1 < 8 && board[index + 8] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 8] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[0] = temp_rights[1] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r + 1 < 8 && f + 1 < 8 && board[index + 9] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 9] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[0] = temp_rights[1] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f + 1 < 8 && board[index + 1] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 1] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[0] = temp_rights[1] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r - 1 >= 0 && f + 1 < 8 && board[index - 7] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index - 7] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[0] = temp_rights[1] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r - 1 >= 0 && board[index - 8] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index - 8] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[0] = temp_rights[1] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r - 1 >= 0 && f - 1 <= 0 && board[index - 9] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index - 9] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[0] = temp_rights[1] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f - 1 >= 0 && board[index - 1] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index - 1] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[0] = temp_rights[1] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r + 1 < 8 && f - 1 >= 0 && board[index + 7] <= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 7] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 1) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[0] = temp_rights[1] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score > bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(alpha < score)
                                        alpha = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(index == 4){
                                if(rights[0] == 1 && board[5] == 0 && board[6] == 0){
                                    if(this->isCheck(board, 1) == 0){
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[4] = 0;
                                        temp_board[5] = 1000000;
                                        if(this->isCheck(temp_board, 1) == 0){
                                            temp_board[5] = 500;
                                            temp_board[6] = 1000000;
                                            temp_board[7] = 0;
                                            if(this->isCheck(temp_board, 1) == 0){
                                                temp_enpasant = this->copyArr(enpasant, 64);
                                                temp_rights = this->copyArr(rights, 4);
                                                
                                                temp_rights[0] = temp_rights[1] = 0;
                                                
                                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                                possible_moves++;
                                                
                                                if(score > bestMove){
                                                    bestMove = score;
                                                }
                                                
                                                delete temp_enpasant;
                                                delete temp_rights;
                                                
                                                if(alpha < score)
                                                    alpha = score;
                                                
                                                if(beta <= alpha){
                                                    delete temp_board;
                                                    return bestMove;
                                                }
                                            }
                                        }
                                        delete temp_board;
                                    }
                                }
                                else if(rights[1] == 1 && board[3] == 0 && board[2] == 0 && board[1] == 0){
                                    if(this->isCheck(board, 1) == 0){
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[4] = 0;
                                        temp_board[3] = 1000000;
                                        if(this->isCheck(temp_board, 1) == 0){
                                            temp_board[3] = 500;
                                            temp_board[2] = 1000000;
                                            temp_board[0] = 0;
                                            if(this->isCheck(temp_board, 1) == 0){
                                                temp_enpasant = this->copyArr(enpasant, 64);
                                                temp_rights = this->copyArr(rights, 4);
                                                
                                                temp_rights[0] = temp_rights[1] = 0;
                                                
                                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                                possible_moves++;
                                                
                                                if(score > bestMove){
                                                    bestMove = score;
                                                }
                                                
                                                delete temp_enpasant;
                                                delete temp_rights;
                                                
                                                if(alpha < score)
                                                    alpha = score;
                                                
                                                if(beta <= alpha){
                                                    delete temp_board;
                                                    return bestMove;
                                                }
                                            }
                                        }
                                        delete temp_board;
                                    }
                                }
                            }
                            break;
                    }
                }
            }
            
            // Check is stalemate
            if(possible_moves == 0 && this->isCheck(board, 1) == 0)
                return 0;
            
            return bestMove;
        }
        else if(isWhiteMoving == 0){ // Minimising player
            int bestMove = 1000000000; // Evaluation of the best move
            isWhiteMoving = 1;
            
            for(int j = 0; j < 8; j++)
                enpasant[32 + j] = 0;
            
            for(int index = 63; index >= 0; index--){
                if(board[index] < 0){
                    int f = index % 8;
                    int r = (index - f) / 8;
                    
                    switch(board[index]){
                        case -100:
                            if(r == 6){
                                if(board[index - 8] == 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 8] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - 8] == 0 && board[index - 16] == 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 16] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        temp_enpasant[index - 16] = 1;
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f - 1 >= 0 && board[index - 9] > 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 9] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f + 1 < 8 && board[index - 7] > 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 7] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                            }
                            else if(r == 3){
                                if(board[index - 8] == 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 8] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f - 1 >= 0 && board[index - 9] > 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 9] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f + 1 < 8 && board[index - 7] > 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 7] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f - 1 >= 0 && enpasant[index - 1] == 1){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 9] = temp_board[index];
                                    temp_board[index] = 0;
                                    temp_board[index - 1] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f + 1 < 8 && enpasant[index + 1] == 1){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 7] = temp_board[index];
                                    temp_board[index] = 0;
                                    temp_board[index + 1] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                            }
                            else if(r == 1){
                                if(board[index - 8] == 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 8] = -900;
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index - 8] = -500;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index - 8] = -320;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index - 8] = -310;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f - 1 >= 0 && board[index - 9] > 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 9] = -900;
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index - 9] = -500;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index - 9] = -320;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index - 9] = -310;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f + 1 < 8 && board[index - 7] > 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 7] = -900;
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index - 7] = -500;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index - 7] = -320;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                        
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[index - 7] = -310;
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                            }
                            else{
                                if(board[index - 8] == 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 8] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f - 1 >= 0 && board[index - 9] > 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 9] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(f + 1 < 8 && board[index - 7] > 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 7] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                            }
                            break;
                            
                        case -310:
                            if(r+2 >= 0 && r+2 < 8 && f+1 >= 0 && f+1 < 8 && board[index + 17] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 17] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r+1 >= 0 && r+1 < 8 && f+2 >= 0 && f+2 < 8 && board[index + 10] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 10] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r-1 >= 0 && r-1 < 8 && f+2 >= 0 && f+2 < 8 && board[index - 6] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index -6] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r-2 >= 0 && r-2 < 8 && f+1 >= 0 && f+1 < 8 && board[index - 15] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index - 15] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r-2 >= 0 && r-2 < 8 && f-1 >= 0 && f-1 < 8 && board[index - 17] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index - 17] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r-1 >= 0 && r-1 < 8 && f-2 >= 0 && f-2 < 8 && board[index - 10] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index - 10] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r+1 >= 0 && r+1 < 8 && f-2 >= 0 && f-2 < 8 && board[index + 6] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 6] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r+2 >= 0 && r+2 < 8 && f-1 >= 0 && f-1 < 8 && board[index + 15] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 15] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            break;
                            
                        case -320:
                            for(int i = 1; r + i < 8 && f + i < 8; i++){
                                if(board[index + 9*i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 9*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + 9*i] != 0)
                                    break;
                            }
                            for(int i = 1; r - i >= 0 && f + i < 8; i++){
                                if(board[index - 7*i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 7*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - 7*i] != 0)
                                    break;
                            }
                            for(int i = 1; r - i >= 0 && f - i >= 0; i++){
                                if(board[index - 9*i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 9*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - 9*i] != 0)
                                    break;
                            }
                            for(int i = 1; r + i < 8 && f - i >= 0; i++){
                                if(board[index + 7*i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 7*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + 7*i] != 0)
                                    break;
                            }
                            break;
                            
                        case -500:
                            for(int i = 1; r + i < 8; i++){
                                if(board[index + 8*i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 8*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        if(index == 56) // queenside
                                            temp_rights[3] = 0;
                                        else if(index == 63) //kingside
                                            temp_rights[2] = 0;
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + 8*i] != 0)
                                    break;
                            }
                            for(int i = 1; f + i < 8; i++){
                                if(board[index + i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        if(index == 56) // queenside
                                            temp_rights[3] = 0;
                                        else if(index == 63) //kingside
                                            temp_rights[2] = 0;
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + i] != 0)
                                    break;
                            }
                            for(int i = 1; r - i >= 0; i++){
                                if(board[index - 8*i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 8*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        if(index == 56) // queenside
                                            temp_rights[3] = 0;
                                        else if(index == 63) //kingside
                                            temp_rights[2] = 0;
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - 8*i] != 0)
                                    break;
                            }
                            for(int i = 1; f - i >= 0; i++){
                                if(board[index - i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        if(index == 56) // queenside
                                            temp_rights[3] = 0;
                                        else if(index == 63) //kingside
                                            temp_rights[2] = 0;
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - i] != 0)
                                    break;
                            }
                            break;
                            
                        case -900:
                            for(int i = 1; r + i < 8 && f + i < 8; i++){
                                if(board[index + 9*i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 9*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + 9*i] != 0)
                                    break;
                            }
                            for(int i = 1; r - i >= 0 && f + i < 8; i++){
                                if(board[index - 7*i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 7*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - 7*i] != 0)
                                    break;
                            }
                            for(int i = 1; r - i >= 0 && f - i >= 0; i++){
                                if(board[index - 9*i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 9*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - 9*i] != 0)
                                    break;
                            }
                            for(int i = 1; r + i < 8 && f - i >= 0; i++){
                                if(board[index + 7*i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 7*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + 7*i] != 0)
                                    break;
                            }
                            for(int i = 1; r + i < 8; i++){
                                if(board[index + 8*i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + 8*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + 8*i] != 0)
                                    break;
                            }
                            for(int i = 1; f + i < 8; i++){
                                if(board[index + i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index + i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index + i] != 0)
                                    break;
                            }
                            for(int i = 1; r - i >= 0; i++){
                                if(board[index - 8*i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - 8*i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - 8*i] != 0)
                                    break;
                            }
                            for(int i = 1; f - i >= 0; i++){
                                if(board[index - i] >= 0){
                                    temp_board = this->copyArr(board, 64);
                                    temp_board[index - i] = temp_board[index];
                                    temp_board[index] = 0;
                                    
                                    if(this->isCheck(temp_board, 0) == 0){
                                        temp_enpasant = this->copyArr(enpasant, 64);
                                        temp_rights = this->copyArr(rights, 4);
                                        
                                        int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                        possible_moves++;
                                        
                                        if(score < bestMove){
                                            bestMove = score;
                                        }
                                        
                                        delete temp_enpasant;
                                        delete temp_rights;
                                        
                                        if(beta > score)
                                            beta = score;
                                        
                                        if(beta <= alpha){
                                            delete temp_board;
                                            return bestMove;
                                        }
                                    }
                                    delete temp_board;
                                }
                                if(board[index - i] != 0)
                                    break;
                            }
                            break;
                            
                        case -1000000:
                            if(r + 1 < 8 && board[index + 8] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 8] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[2] = temp_rights[3] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r + 1 < 8 && f + 1 < 8 && board[index + 9] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 9] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[2] = temp_rights[3] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f + 1 < 8 && board[index + 1] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 1] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[2] = temp_rights[3] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r - 1 >= 0 && f + 1 < 8 && board[index - 7] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index - 7] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[2] = temp_rights[3] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r - 1 >= 0 && board[index - 8] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index - 8] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[2] = temp_rights[3] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r - 1 >= 0 && f - 1 <= 0 && board[index - 9] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index - 9] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[2] = temp_rights[3] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(f - 1 >= 0 && board[index - 1] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index - 1] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[2] = temp_rights[3] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(r + 1 < 8 && f - 1 >= 0 && board[index + 7] >= 0){
                                temp_board = this->copyArr(board, 64);
                                temp_board[index + 7] = temp_board[index];
                                temp_board[index] = 0;
                                
                                if(this->isCheck(temp_board, 0) == 0){
                                    temp_enpasant = this->copyArr(enpasant, 64);
                                    temp_rights = this->copyArr(rights, 4);
                                    
                                    temp_rights[2] = temp_rights[3] = 0;
                                    
                                    int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                    possible_moves++;
                                    
                                    if(score < bestMove){
                                        bestMove = score;
                                    }
                                    
                                    delete temp_enpasant;
                                    delete temp_rights;
                                    
                                    if(beta > score)
                                        beta = score;
                                    
                                    if(beta <= alpha){
                                        delete temp_board;
                                        return bestMove;
                                    }
                                }
                                delete temp_board;
                            }
                            if(index == 60){
                                if(rights[2] == 1 && board[61] == 0 && board[62] == 0){
                                    if(this->isCheck(board, 0) == 0){
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[60] = 0;
                                        temp_board[61] = -1000000;
                                        if(this->isCheck(temp_board, 0) == 0){
                                            temp_board[61] = -500;
                                            temp_board[62] = -1000000;
                                            temp_board[63] = 0;
                                            if(this->isCheck(temp_board, 0) == 0){
                                                temp_enpasant = this->copyArr(enpasant, 64);
                                                temp_rights = this->copyArr(rights, 4);
                                                
                                                temp_rights[2] = temp_rights[3] = 0;
                                                
                                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                                possible_moves++;
                                                
                                                if(score < bestMove){
                                                    bestMove = score;
                                                }
                                                
                                                delete temp_enpasant;
                                                delete temp_rights;
                                                
                                                if(beta > score)
                                                    beta = score;
                                                
                                                if(beta <= alpha){
                                                    delete temp_board;
                                                    return bestMove;
                                                }
                                            }
                                        }
                                        delete temp_board;
                                    }
                                }
                                else if(rights[3] == 1 && board[59] == 0 && board[58] == 0 && board[57] == 0){
                                    if(this->isCheck(board, 0) == 0){
                                        temp_board = this->copyArr(board, 64);
                                        temp_board[60] = 0;
                                        temp_board[59] = -1000000;
                                        if(this->isCheck(temp_board, 0) == 0){
                                            temp_board[59] = -500;
                                            temp_board[58] = -1000000;
                                            temp_board[56] = 0;
                                            if(this->isCheck(temp_board, 1) == 0){
                                                temp_enpasant = this->copyArr(enpasant, 64);
                                                temp_rights = this->copyArr(rights, 4);
                                                
                                                temp_rights[2] = temp_rights[3] = 0;
                                                
                                                int score = this->tree(temp_board, isWhiteMoving, temp_enpasant, temp_rights, maxDepth, alpha, beta);
                                                possible_moves++;
                                                
                                                if(score < bestMove){
                                                    bestMove = score;
                                                }
                                                
                                                delete temp_enpasant;
                                                delete temp_rights;
                                                
                                                if(beta > score)
                                                    beta = score;
                                                
                                                if(beta <= alpha){
                                                    delete temp_board;
                                                    return bestMove;
                                                }
                                            }
                                        }
                                        delete temp_board;
                                    }
                                }
                            }
                            break;
                    }
                }
            }
            
            // Check is stalemate
            if(possible_moves == 0 && this->isCheck(board, 0) == 0)
                return 0;
            
            return bestMove;
        }
        else{
            std::cout << "Error generating the tree" << std::endl;
            exit(1);
        }
    }
    else{
        // This is the base of the tree: return the value of the evaluation
        return this->evaluate(board);
    }
}


// Copy the board to a new array
int* Board::copyArr(int *arr, int lenght){
    // Using dynamic allocation so it won't destruct with the return
    int* temp = new int[lenght];
    
    for(int i = 0; i < lenght; i++)
        temp[i] = arr[i];
    
    return temp;
}

#endif /* chess_h */
