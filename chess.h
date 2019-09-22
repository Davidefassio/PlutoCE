//
//  chess.h
//  chessAI
//
//  Created by Davide Fassio on 19/09/2019.
//  Copyright © 2019 Davide Fassio. All rights reserved.
//

#ifndef chess_h
#define chess_h


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
    int board[8][8] = {
        {500, 310, 320, 900, 1000000, 320, 310, 500},
        {100, 100, 100, 100, 100, 100, 100, 100},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {-100, -100, -100, -100, -100, -100, -100, -100},
        {-500, -310, -320, -900, -1000000, -320, -310, -500}
    };
    
    // Right to castel: 1 = castel is possible, 0 = castel not possible
    // 0: white kingside
    // 1: white queenside
    // 2: black kingside
    // 3: black kingside
    int castling_rights[4] = {1, 1, 1, 1};
    
    // Capture en-pasant: 1 = can be captured en pasant, 0 = can't be captured en-pasant
    int captured_enpasant[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    // Piece-square table for better evaluation
    const int whitePawn_eval[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {5, 10, 10,-20,-20, 10, 10, 5},
        {5, -5,-10, 0, 0,-10, -5, 5},
        {0, 0, 0, 20, 20, 0, 0, 0},
        {5, 5, 10, 25, 25, 10, 5, 5},
        {10, 10, 20, 30, 30, 20, 10, 10},
        {50, 50, 50, 50, 50, 50, 50, 50},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };
    const int whiteKnight_eval[8][8] = {
        {-50, -40, -30, -30, -30, -30, -40, -50},
        {-40, -20, 0, 5, 5, 0, -20, -40},
        {-30, 5, 10, 15, 15, 10, 5, -30},
        {-30, 0, 15, 20, 20, 15, 0, -30},
        {-30, 5, 15, 20, 20, 15, 5, -30},
        {-30, 0, 10, 15, 15, 10, 0, -30},
        {-40, -20, 0, 0, 0, 0, -20, -40},
        {-50, -40, -30, -30, -30, -30, -40, -50}
    };
    const int whiteBishop_eval[8][8] = {
        {-20, -10, -10, -10, -10, -10, -10, -20},
        {-10, 5, 0, 0, 0, 0, 5, -10},
        {-10, 10, 10, 10, 10, 10, 10, -10},
        {-10, 0, 10, 10, 10, 10, 0, -10},
        {-10, 5, 5, 10, 10, 5, 5, -10},
        {-10, 0, 5, 10, 10, 5, 0, -10},
        {-10, 0, 0, 0, 0, 0, 0, -10},
        {-20, -10, -10, -10, -10, -10, -10, -20}
    };
    const int whiteRook_eval[8][8] = {
        {0, 0, 0, 5, 5, 0, 0, 0},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {5, 10, 10, 10, 10, 10, 10, 5},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    const int whiteQueen_eval[8][8] = {
        {-20, -10, -10, -5, -5, -10, -10, -20},
        {-10, 0, 5, 0,  0, 0, 0, -10},
        {-10, 5, 5, 5, 5, 5, 0, -10},
        {0, 0, 5, 5, 5, 5, 0, -5},
        {-5, 0, 5, 5, 5, 5, 0, -5},
        {-10, 0, 5, 5, 5, 5, 0, -10},
        {-10, 0, 0, 0, 0, 0, 0, -10},
        {-20, -10, -10, -5, -5, -10, -10, -20}
    };
    const int whiteKing_middleGame_eval[8][8] = {
        {20, 30, 10, 0, 0, 10, 30, 20},
        {20, 20, 0, 0, 0, 0, 20, 20},
        {-10, -20, -20, -20,-20, -20, -20, -10},
        {-20, -30, -30, -40,-40, -30, -30, -20},
        {-30, -40, -40, -50,-50, -40, -40, -30},
        {-30, -40, -40, -50,-50, -40, -40, -30},
        {-30, -40, -40, -50,-50, -40, -40, -30},
        {-30, -40, -40, -50,-50, -40, -40, -30}
    };
    const int whiteKing_endGame_eval[8][8] = {
        {-50, -30, -30, -30, -30, -30, -30, -50},
        {-30, -30, 0, 0, 0, 0, -30, -30},
        {-30, -10, 20, 30, 30, 20, -10, -30},
        {-30, -10, 30, 40, 40, 30, -10, -30},
        {-30, -10, 30, 40, 40, 30, -10, -30},
        {-30, -10, 20, 30, 30, 20, -10, -30},
        {-30, -20, -10, 0, 0, -10, -20, -30},
        {-50, -40, -30, -20, -20, -30, -40, -50}
    };
    
    const int blackPawn_eval[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {-50, -50, -50, -50, -50, -50, -50, -50},
        {-10, -10, -20, -30, -30, -20, -10, -10},
        {-5, -5, -10, -25, -25, -10, -5, -5},
        {0, 0, 0, -20, -20, 0, 0, 0},
        {-5, 5, 10, 0, 0, 10, 5, -5},
        {-5, -10, -10, 20, 20, -10, -10, -5},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    const int blackKnight_eval[8][8] = {
        {50, 40, 30, 30, 30, 30, 40, 50},
        {40, 20, 0, 0, 0, 0, 20, 40},
        {30, 0, -10, -15, -15, -10, 0, 30},
        {30, -5, -15, -20, -20, -15, -5, 30},
        {30, 0, -15, -20, -20, -15, 0, 30},
        {30, -5, -10, -15, -15, -10, -5, 30},
        {40, 20, 0, -5, -5, 0, 20, 40},
        {50, 40, 30, 30, 30, 30, 40, 50}
    };
    const int blackBishop_eval[8][8] = {
        {20, 10, 10, 10, 10, 10, 10, 20},
        {10, 0, 0, 0, 0, 0, 0, 10},
        {10, 0, -5, -10, -10, -5, 0, 10},
        {10, -5, -5, -10, -10, -5, -5, 10},
        {10, 0, -10, -10, -10, -10, 0, 10},
        {10, -10, -10, -10, -10, -10, -10, 10},
        {10, -5, 0, 0, 0, 0, -5, 10},
        {20, 10, 10, 10, 10, 10, 10, 20}
    };
    const int blackRook_eval[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {-5, -10, -10, -10, -10, -10, -10, -5},
        {5, 0, 0, 0, 0, 0, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 5},
        {5, 0, 0, 0, 0, 0, 0, 5},
        {0, 0, 0, -5, -5, 0, 0, 0}
    };
    const int blackQueen_eval[8][8] = {
        {20, 10, 10, 5, 5, 10, 10, 20},
        {10, 0, 0, 0, 0, 0, 0, 10},
        {10, 0, -5, -5, -5, -5, 0, 10},
        {5, 0, -5, -5, -5, -5, 0, 5},
        {0, 0, -5, -5, -5, -5, 0, 5},
        {10, -5, -5, -5, -5, -5, 0, 10},
        {10, 0, -5, 0, 0, 0, 0, 10},
        {20, 10, 10, 5, 5, 10, 10, 20}
    };
    const int blackKing_middleGame_eval[8][8] = {
        {30, 40, 40, 50, 50, 40, 40, 30},
        {30, 40, 40, 50, 50, 40, 40, 30},
        {30, 40, 40, 50, 50, 40, 40, 30},
        {30, 40, 40, 50, 50, 40, 40, 30},
        {20, 30, 30, 40, 40, 30, 30, 20},
        {10, 20, 20, 20, 20, 20, 20, 10},
        {-20, -20,  0,  0,  0,  0, -20, -20},
        {-20, -30, -10,  0,  0, -10, -30, -20}
    };
    const int blackKing_endGame_eval[8][8] = {
        {50, 40, 30, 20, 20, 30, 40, 50},
        {30, 20, 10, 0,  0, 10, 20, 30},
        {30, 10, -20, -30, -30, -20, 10, 30},
        {30, 10, -30, -40, -40, -30, 10, 30},
        {30, 10, -30, -40, -40, -30, 10, 30},
        {30, 10, -20, -30, -30, -20, 10, 30},
        {30, 30, 0, 0,  0, 0, 30, 30},
        {50, 30, 30, 30, 30, 30, 30, 50}
    };
    
    // Functions
    void move(int [8][8], char*, int, int, int[8][8], int [4]);
    int evaluate(int [8][8]);
    int isCheck(int [8][8], int);
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
    - isAIMoving:
        - 1 -> the AI is moving (so the move is correct)
        - 0 -> the player is moving (the move need to be checked)
    - isWhiteMoving: 1 -> white is moving, 0 -> black is moving
    - 8x8 board for capture en-pasant
    - lenght 4 array containing the castling rights
*/
void Board::move(int board[8][8], char *move, int isAIMoving, int isWhiteMoving, int enpasant[8][8], int rights[4]){
    if(isAIMoving == 1){
        // the move is correct
        // the move is in form r1y1r2y2
        // example the move 1.Nf3 is 6052
        int r1 = (int)move[0] - 48;
        int f1 = (int)move[1] - 48;
        int r2 = (int)move[2] - 48;
        int f2 = (int)move[3] - 48;
    
        board[r2][f2] = board[r1][f1];
        board[r1][f1] = 0;
    }
    else{
        // check the move if is correct
        int moveIsCorrect = 0;  // Starting with illegal
        
        // the move is in form y1r1y2r2
        // example the move 1.Nf3 is g1f3
        int f1 = (int)move[0] - 97;
        int r1 = (int)move[1] - 49;
        int f2 = (int)move[2] - 97;
        int r2 = (int)move[3] - 49;
        
        // TO FINISH AND TEST
        if(r1 >= 0 && r1 < 8 && f1 >= 0 && f1 < 8 && r2 >= 0 && r2 < 8 && f2 >= 0 && f2 < 8){
            if(isWhiteMoving == 1){
                // Remove all the right to capture a white pawn en-pasant
                for(int j = 0; j < 8; j++)
                    enpasant[3][j] = 0;
                
                if(board[r1][f1] > 0 && board[r2][f2] <= 0){
                    switch (board[r1][f1]){
                        case 100: // Pawn
                            if(r1 == 1){ // Starting square
                                if(r2 - r1 == 2 && f1 == f2 && board[r1+1][f1] == 0 && board[r2][f2] == 0){
                                    moveIsCorrect = 1;
                                    enpasant[r2][f2] = 1;
                                }
                                else if(r2 - r1 == 1 && f1 == f2 && board[r2][f2] == 0)
                                    moveIsCorrect = 1;
                                else if(r2 - r1 == 1 && abs(f1 - f2) == 1 && board[r2][f2] < 0)
                                    moveIsCorrect = 1;
                            }
                            else if(r1 == 4){ // En-pasant capture
                                // Normal moves
                                if(r2 - r1 == 1 && f1 == f2 && board[r2][f2] == 0)
                                    moveIsCorrect = 1;
                                else if(r2 - r1 == 1 && abs(f1 - f2) == 1 && board[r2][f2] < 0)
                                    moveIsCorrect = 1;
                                // En-pasant captures
                                else if(r2 - r1 == 1 && f2 - f1 == 1 && enpasant[r1][f1+1] == 1 && board[r2][f2] == 0){
                                    moveIsCorrect = 1;
                                    board[r1][f1+1] = 0;
                                }
                                else if(r2 - r1 == 1 && f1 - f2 == 1 && enpasant[r1][f1-1] == 1 && board[r2][f2] == 0){
                                    moveIsCorrect = 1;
                                    board[r1][f1-1] = 0;
                                }
                            }
                            else if(r1 == 6){ // Promotion
                                switch (move[4]) {
                                    case 'N':
                                        board[r1][f1] = 310;
                                        break;
                                    
                                    case 'B':
                                        board[r1][f1] = 320;
                                        break;
                                        
                                    case 'R':
                                        board[r1][f1] = 500;
                                        break;
                                        
                                    case 'Q':
                                        board[r1][f1] = 900;
                                        break;
                                        
                                    default:
                                        std::cout << "The move made is illegal!" << std::endl;
                                        exit(0);
                                        break;
                                }
                                
                                if(r2 - r1 == 1 && f1 == f2 && board[r2][f2] == 0){
                                    moveIsCorrect = 1;
                                }
                                else if(r2 - r1 == 1 && abs(f1 - f2) == 1 && board[r2][f2] < 0){
                                    moveIsCorrect = 1;
                                }
                                
                            }
                            else{ // Every other rank
                                if(r2 - r1 == 1 && f1 == f2 && board[r2][f2] == 0)
                                    moveIsCorrect = 1;
                                else if(r2 - r1 == 1 && abs(f1 - f2) == 1 && board[r2][f2] < 0)
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
                                    if(board[r1 + i*kr][f1 + i*kf] != 0)
                                        allEmpty = 0;
                                }
                                
                                if(allEmpty == 1)
                                    moveIsCorrect = 1;
                            }
                            break;
                        
                        case 500: // Rook
                            // White lose the castling rights
                            if(f1 == 0) // queenside
                                rights[1] = 0;
                            else if(f1 == 7) //kingside
                                rights[0] = 0;
                            
                            if(r1 == r2){
                                int kf = (f2 - f1 > 0) ? 1 : -1;
                                int allEmpty = 1;
                                
                                for(int i = 1; i < abs(f2 - f1); i++){
                                    if(board[r1][f1 + i*kf] != 0)
                                        allEmpty = 0;
                                }
                                
                                if(allEmpty == 1)
                                    moveIsCorrect = 1;
                            }
                            else if(f1 == f2){
                                int kr = (r2 - r1 > 0) ? 1 : -1;
                                int allEmpty = 1;
                                
                                for(int i = 1; i < abs(r2 - r1); i++){
                                    if(board[r1 + i*kr][f1] != 0)
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
                                    if(board[r1 + i*kr][f1 + i*kf] != 0)
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
                                    if(board[r1][f1 + i*kf] != 0)
                                        allEmpty = 0;
                                }
                                
                                if(allEmpty == 1)
                                    moveIsCorrect = 1;
                            }
                            else if(f1 == f2){
                                int kr = (r2 - r1 > 0) ? 1 : -1;
                                int allEmpty = 1;
                                
                                for(int i = 1; i < abs(r2 - r1); i++){
                                    if(board[r1 + i*kr][f1] != 0)
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
                            else if(r2 == 0 && f2 == 6 && rights[0] == 1 && board[0][5] == 0 && board[0][6] == 0){
                                // Control checks in the way
                                if(this->isCheck(board, 1) == 0){
                                    board[0][4] = 0;
                                    board[0][5] = 1000000;
                                    if(this->isCheck(board, 1) == 0){
                                        board[0][5] = 0;
                                        board[0][6] = 1000000;
                                        if(this->isCheck(board, 1) == 0){
                                            moveIsCorrect = 1;
                                            // Restore king's position
                                            board[0][4] = 1000000;
                                            board[0][6] = 0;
                                            // Move the rook
                                            board[0][7] = 0;
                                            board[0][5] = 500;
                                        }
                                    }
                                }
                            }
                            else if(r2 == 0 && f2 == 2 && rights[1] == 1 && board[0][3] == 0 && board[0][2] == 0 && board[0][1] == 0){
                                // Control checks in the way
                                if(this->isCheck(board,1) == 0){
                                    board[0][4] = 0;
                                    board[0][3] = 1000000;
                                    if(this->isCheck(board,1) == 0){
                                        board[0][3] = 0;
                                        board[0][2] = 1000000;
                                        if(this->isCheck(board,1) == 0){
                                            moveIsCorrect = 1;
                                            // Restore king's position
                                            board[0][4] = 1000000;
                                            board[0][2] = 0;
                                            // Move the rook
                                            board[0][0] = 0;
                                            board[0][3] = 500;
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
            else{
                // Remove all the right to capture a black pawn en-pasant
                for(int j = 0; j < 8; j++)
                    enpasant[3][j] = 0;
                
                if(board[r1][f1] < 0 && board[r2][f2] >= 0){
                    switch (board[r1][f1]){
                        case -100: // Pawn
                            if(r1 == 6){ // Starting square
                                if(r2 - r1 == -2 && f1 == f2 && board[r1-1][f1] == 0 && board[r2][f2] == 0){
                                    moveIsCorrect = 1;
                                    enpasant[r2][f2] = 1;
                                }
                                else if(r2 - r1 == -1 && f1 == f2 && board[r2][f2] == 0)
                                    moveIsCorrect = 1;
                                else if(r2 - r1 == -1 && abs(f1 - f2) == 1 && board[r2][f2] > 0)
                                    moveIsCorrect = 1;
                            }
                            else if(r1 == 3){ // En-pasant capture
                                // Normal moves
                                if(r2 - r1 == -1 && f1 == f2 && board[r2][f2] == 0)
                                    moveIsCorrect = 1;
                                else if(r2 - r1 == -1 && abs(f1 - f2) == 1 && board[r2][f2] > 0)
                                    moveIsCorrect = 1;
                                // En-pasant captures
                                else if(r2 - r1 == -1 && f2 - f1 == 1 && enpasant[r1][f1+1] == 1 && board[r2][f2] == 0){
                                    moveIsCorrect = 1;
                                    board[r1][f1+1] = 0;
                                }
                                else if(r2 - r1 == -1 && f1 - f2 == 1 && enpasant[r1][f1-1] == 1 && board[r2][f2] == 0){
                                    moveIsCorrect = 1;
                                    board[r1][f1-1] = 0;
                                }
                            }
                            else if(r1 == 1){ // Promotion
                                switch (move[4]) {
                                    case 'N':
                                        board[r1][f1] = -310;
                                        break;
                                        
                                    case 'B':
                                        board[r1][f1] = -320;
                                        break;
                                        
                                    case 'R':
                                        board[r1][f1] = -500;
                                        break;
                                        
                                    case 'Q':
                                        board[r1][f1] = -900;
                                        break;
                                        
                                    default:
                                        std::cout << "The move made is illegal!" << std::endl;
                                        exit(0);
                                        break;
                                }
                                
                                if(r2 - r1 == -1 && f1 == f2 && board[r2][f2] == 0){
                                    moveIsCorrect = 1;
                                }
                                else if(r2 - r1 == -1 && abs(f1 - f2) == 1 && board[r2][f2] > 0){
                                    moveIsCorrect = 1;
                                }
                                
                            }
                            else{ // Every other rank
                                if(r2 - r1 == -1 && f1 == f2 && board[r2][f2] == 0)
                                    moveIsCorrect = 1;
                                else if(r2 - r1 == -1 && abs(f1 - f2) == 1 && board[r2][f2] > 0)
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
                                    if(board[r1 + i*kr][f1 + i*kf] != 0)
                                        allEmpty = 0;
                                }
                                
                                if(allEmpty == 1)
                                    moveIsCorrect = 1;
                            }
                            break;
                            
                        case -500: // Rook
                            // White lose the castling rights
                            if(f1 == 0) // queenside
                                rights[3] = 0;
                            else if(f1 == 7) //kingside
                                rights[2] = 0;
                            
                            if(r1 == r2){
                                int kf = (f2 - f1 > 0) ? 1 : -1;
                                int allEmpty = 1;
                                
                                for(int i = 1; i < abs(f2 - f1); i++){
                                    if(board[r1][f1 + i*kf] != 0)
                                        allEmpty = 0;
                                }
                                
                                if(allEmpty == 1)
                                    moveIsCorrect = 1;
                            }
                            else if(f1 == f2){
                                int kr = (r2 - r1 > 0) ? 1 : -1;
                                int allEmpty = 1;
                                
                                for(int i = 1; i < abs(r2 - r1); i++){
                                    if(board[r1 + i*kr][f1] != 0)
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
                                    if(board[r1 + i*kr][f1 + i*kf] != 0)
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
                                    if(board[r1][f1 + i*kf] != 0)
                                        allEmpty = 0;
                                }
                                
                                if(allEmpty == 1)
                                    moveIsCorrect = 1;
                            }
                            else if(f1 == f2){
                                int kr = (r2 - r1 > 0) ? 1 : -1;
                                int allEmpty = 1;
                                
                                for(int i = 1; i < abs(r2 - r1); i++){
                                    if(board[r1 + i*kr][f1] != 0)
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
                            else if(r2 == 7 && f2 == 6 && rights[2] == 1 && board[7][5] == 0 && board[7][6] == 0){
                                // Control checks in the way
                                if(this->isCheck(board, 0) == 0){
                                    board[7][4] = 0;
                                    board[7][5] = -1000000;
                                    if(this->isCheck(board, 0) == 0){
                                        board[7][5] = 0;
                                        board[7][6] = -1000000;
                                        if(this->isCheck(board, 0) == 0){
                                            moveIsCorrect = 1;
                                            // Restore king's position
                                            board[7][4] = -1000000;
                                            board[7][6] = 0;
                                            // Move the rook
                                            board[7][7] = 0;
                                            board[7][5] = -500;
                                        }
                                    }
                                }
                            }
                            else if(r2 == 7 && f2 == 2 && rights[3] == 1 && board[7][3] == 0 && board[7][2] == 0 && board[7][1] == 0){
                                // Control checks in the way
                                if(this->isCheck(board, 0) == 0){
                                    board[7][4] = 0;
                                    board[7][3] = -1000000;
                                    if(this->isCheck(board, 0) == 0){
                                        board[7][3] = 0;
                                        board[7][2] = -1000000;
                                        if(this->isCheck(board, 0) == 0){
                                            moveIsCorrect = 1;
                                            // Restore king's position
                                            board[7][4] = -1000000;
                                            board[7][2] = 0;
                                            // Move the rook
                                            board[7][0] = 0;
                                            board[7][3] = -500;
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
            board[r2][f2] = board[r1][f1];
            board[r1][f1] = 0;
            
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
}


// Parameter:
//      - an 8x8 board
int Board::evaluate(int board[8][8]){
    int evaluation = 0;
    
    int pieceValueCount = 0;    // to know when it go in the endgame
    int whiteKing_row = 0, whiteKing_file = 0, blackKing_row = 0, blackKing_file = 0;
    
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            // Add the value of the piece
            evaluation += board[i][j];
            
            // Add the module of all pieces to know when is the endgame
            pieceValueCount += abs(board[i][j]);
            
            // Decide which piece-square table use
            switch (board[i][j]) {
                case 0:
                    break;
                    
                case 100:
                    evaluation += this->whitePawn_eval[i][j];
                    break;
                
                case 310:
                    evaluation += this->whiteKnight_eval[i][j];
                    break;
                    
                case 320:
                    evaluation += this->whiteBishop_eval[i][j];
                    break;
                    
                case 500:
                    evaluation += this->whiteRook_eval[i][j];
                    break;
                    
                case 900:
                    evaluation += this->whiteQueen_eval[i][j];
                    break;
                    
                case 1000000:   // Save the coords for after
                    whiteKing_row = i;
                    whiteKing_file = j;
                    break;
                    
                case -100:
                    evaluation += this->blackPawn_eval[i][j];
                    break;
                    
                case -310:
                    evaluation += this->blackKnight_eval[i][j];
                    break;
                    
                case -320:
                    evaluation += this->blackBishop_eval[i][j];
                    break;
                    
                case -500:
                    evaluation += this->blackRook_eval[i][j];
                    break;
                    
                case -900:
                    evaluation += this->blackQueen_eval[i][j];
                    break;
                    
                case -1000000:  // Save the coords for after
                    blackKing_row = i;
                    blackKing_file = j;
                    break;
            }
        }
    }
    
    // If the sum of the module of all pieces is less than 2003600 we are in the endgame
    // 2003600 is exactly:
    // 1 King + 1 Queen + 1 Rook + 4 Pawn each
    if(pieceValueCount < 2003600){
        evaluation += this->whiteKing_endGame_eval[whiteKing_row][whiteKing_file];
        evaluation += this->blackKing_endGame_eval[blackKing_row][blackKing_file];
    }
    else{
        evaluation += this->whiteKing_middleGame_eval[whiteKing_row][whiteKing_file];
        evaluation += this->blackKing_middleGame_eval[blackKing_row][blackKing_file];
    }
    
    return evaluation;
}


// Control if there are checks on the board:
//  - isWhiteKing = 1 -> white king under check
//  - isWhiteKing = 0 -> black king under check
// Return value: 1 -> true, 0 -> false
int Board::isCheck(int board[8][8], int isWhiteKing){
    if(isWhiteKing == 1){
        int r = 0, f = 0;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(board[i][j] == 1000000){
                    r = i;
                    f = j;
                    goto wkFound;
                }
            }
        }
        
        wkFound:
        // Check from knights
        if(r+2 >= 0 && r+2 < 0 && f+1 >= 0 && f+1 < 0 && board[r+2][f+1] == -310)
            return 1;
        if(r+1 >= 0 && r+1 < 0 && f+2 >= 0 && f+2 < 0 && board[r+2][f+1] == -310)
            return 1;
        if(r-1 >= 0 && r-1 < 0 && f+2 >= 0 && f+2 < 0 && board[r+2][f+1] == -310)
            return 1;
        if(r-2 >= 0 && r-2 < 0 && f+1 >= 0 && f+1 < 0 && board[r+2][f+1] == -310)
            return 1;
        if(r-2 >= 0 && r-2 < 0 && f-1 >= 0 && f-1 < 0 && board[r+2][f+1] == -310)
            return 1;
        if(r-1 >= 0 && r-1 < 0 && f-2 >= 0 && f-2 < 0 && board[r+2][f+1] == -310)
            return 1;
        if(r+1 >= 0 && r+1 < 0 && f-2 >= 0 && f-2 < 0 && board[r+2][f+1] == -310)
            return 1;
        if(r+2 >= 0 && r+2 < 0 && f-1 >= 0 && f-1 < 0 && board[r+2][f+1] == -310)
            return 1;
        
        // Check from bishops/queens
        for(int i = 1; r + i < 8 && f + i < 8; i++){
            if(i == 1){ // Check from pawns
                if(board[r+i][f+i] == -100)
                    return 1;
            }
            if(board[r+i][f+i] == -320 || board[r+i][f+i] == -900)
                return 1;
            if(board[r+i][f+i] != 0)
                break;
        }
        for(int i = 1; r - i >= 0 && f + i < 8; i++){
            if(board[r-i][f+i] == -320 || board[r-i][f+i] == -900)
                return 1;
            if(board[r-i][f+i] != 0)
                break;
        }
        for(int i = 1; r - i >= 0 && f - i >= 0; i++){
            if(board[r-i][f-i] == -320 || board[r-i][f-i] == -900)
                return 1;
            if(board[r-i][f-i] != 0)
                break;
        }
        for(int i = 1; r + i < 8 && f - i >= 0; i++){
            if(i == 1){ // Check from pawns
                if(board[r+i][f-i] == -100)
                    return 1;
            }
            if(board[r+i][f-i] == -320 || board[r+i][f-i] == -900)
                return 1;
            if(board[r+i][f-i] != 0)
                break;
        }
        
        // Check from rook/queens
        for(int i = 1; r + i < 8; i++){
            if(board[r+i][f] == -500 || board[r+i][f] == -900)
                return 1;
            if(board[r+i][f] != 0)
                break;
        }
        for(int i = 1; f + i < 8; i++){
            if(board[r][f+i] == -500 || board[r][f+i] == -900)
                return 1;
            if(board[r][f+i] != 0)
                break;
        }
        for(int i = 1; r - i >= 0; i++){
            if(board[r-i][f] == -500 || board[r-i][f] == -900)
                return 1;
            if(board[r-i][f] != 0)
                break;
        }
        for(int i = 1; f - i >= 0; i++){
            if(board[r][f-i] == -500 || board[r][f-i] == -900)
                return 1;
            if(board[r][f-i] != 0)
                break;
        }
    }
    else{
        int r = 0, f = 0;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(board[i][j] == -1000000){
                    r = i;
                    f = j;
                    goto bkFound;
                }
            }
        }
        
        bkFound:
        // Check from knights
        if(r+2 >= 0 && r+2 < 0 && f+1 >= 0 && f+1 < 0 && board[r+2][f+1] == 310)
            return 1;
        if(r+1 >= 0 && r+1 < 0 && f+2 >= 0 && f+2 < 0 && board[r+2][f+1] == 310)
            return 1;
        if(r-1 >= 0 && r-1 < 0 && f+2 >= 0 && f+2 < 0 && board[r+2][f+1] == 310)
            return 1;
        if(r-2 >= 0 && r-2 < 0 && f+1 >= 0 && f+1 < 0 && board[r+2][f+1] == 310)
            return 1;
        if(r-2 >= 0 && r-2 < 0 && f-1 >= 0 && f-1 < 0 && board[r+2][f+1] == 310)
            return 1;
        if(r-1 >= 0 && r-1 < 0 && f-2 >= 0 && f-2 < 0 && board[r+2][f+1] == 310)
            return 1;
        if(r+1 >= 0 && r+1 < 0 && f-2 >= 0 && f-2 < 0 && board[r+2][f+1] == 310)
            return 1;
        if(r+2 >= 0 && r+2 < 0 && f-1 >= 0 && f-1 < 0 && board[r+2][f+1] == 310)
            return 1;
        
        // Check from bishops/queens
        for(int i = 1; r + i < 8 && f + i < 8; i++){
            if(board[r+i][f+i] == 320 || board[r+i][f+i] == 900)
                return 1;
            if(board[r+i][f+i] != 0)
                break;
        }
        for(int i = 1; r - i >= 0 && f + i < 8; i++){
            if(i == 1){ // Check from pawns
                if(board[r+i][f+i] == 100)
                    return 1;
            }
            if(board[r-i][f+i] == 320 || board[r-i][f+i] == 900)
                return 1;
            if(board[r-i][f+i] != 0)
                break;
        }
        for(int i = 1; r - i >= 0 && f - i >= 0; i++){
            if(i == 1){ // Check from pawns
                if(board[r+i][f-i] == 100)
                    return 1;
            }
            if(board[r-i][f-i] == 320 || board[r-i][f-i] == 900)
                return 1;
            if(board[r-i][f-i] != 0)
                break;
        }
        for(int i = 1; r + i < 8 && f - i >= 0; i++){
            if(board[r+i][f-i] == 320 || board[r+i][f-i] == 900)
                return 1;
            if(board[r+i][f-i] != 0)
                break;
        }
        
        // Check from rook/queens
        for(int i = 1; r + i < 8; i++){
            if(board[r+i][f] == 500 || board[r+i][f] == 900)
                return 1;
            if(board[r+i][f] != 0)
                break;
        }
        for(int i = 1; f + i < 8; i++){
            if(board[r][f+i] == 500 || board[r][f+i] == 900)
                return 1;
            if(board[r][f+i] != 0)
                break;
        }
        for(int i = 1; r - i >= 0; i++){
            if(board[r-i][f] == 500 || board[r-i][f] == 900)
                return 1;
            if(board[r-i][f] != 0)
                break;
        }
        for(int i = 1; f - i >= 0; i++){
            if(board[r][f-i] == 500 || board[r][f-i] == 900)
                return 1;
            if(board[r][f-i] != 0)
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
            switch (this->board[i][j]) {
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
            switch(this->board[i][j]) {
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
