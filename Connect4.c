#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h> 
#include <time.h> 

int TOTAL_ROW = 4;
int TOTAL_COL = 5;

/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
enum
{
    EMPTY = 0,
    RED,
    BLUE,
};

typedef char board_t[4][5];
typedef char player_t;

// Initiate board
void initiate_board(board_t board){
    for(int r=0 ; r<TOTAL_ROW; r++){
        for(int c=0; c<TOTAL_COL; c++){
            (board)[r][c]='.';
        }
    }
}

// Drops a piece of that player on the given location
void drop_piece(board_t board, int row, int col, player_t player){
    board[row][col]=player;
}

// Checks if that column is not already full
int is_valid_location(board_t board,int col){
   if(board[0][col]=='.'){
    return 1;
   }
   return 0;
}

// Checks the next empty row of that col
int next_open_row(board_t board, int col){
    for(int r=TOTAL_ROW-1; r>=0;r--){
        if(board[r][col]=='.'){
            return r;
        }
    }
    return -1;
}

// prints the board
void print_borad(board_t board){
    printf("\n"); 
    for(int r=0 ;r<TOTAL_ROW; r++){
        for(int c=0; c<TOTAL_COL;c++){
            printf("%c ", board[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

int is_draw(board_t board){
    for(int r=0; r<TOTAL_ROW; r++){
        for(int c=0; c<TOTAL_COL; c++){
            if (board[r][c] == '.'){return 0;}
        }
    }
    return 1;
}

// check if player has won
int has_won(board_t board, player_t player){
    // horizontal win
    for(int c=0; c<TOTAL_COL-3; c++){
        for(int r=0; r<TOTAL_ROW; r++){
            if(board[r][c]==player && board[r][c+1]==player && board[r][c+2]==player && board[r][c+3]==player){
                return 1;
            }
        }
    }

    // vertical win
    for (int r=0; r<TOTAL_ROW-3; r++){
        for (int c=0; c<TOTAL_COL; c++){
            if(board[r][c]==player && board[r+1][c]==player && board[r+2][c]==player && board[r+3][c]==player){
                return 1;
            }
        }
    }

    // Positively Sloped Diagonal Win
    for(int r=0; r<TOTAL_ROW-3; r++){
        for(int c=0; c<TOTAL_COL-3; c++){
            if(board[r][c]==player && board[r+1][c+1]==player && board[r+2][c+2]==player && board[r+3][c+3]==player){
                return 1;
            }
        }
    }

    // Negetively Sloped Diagonal Win
    for(int c=0; c<TOTAL_COL-3; c++){
        for(int r=3; r<TOTAL_ROW; r++){
            if(board[r][c]==player && board[r-1][c+1]==player && board[r-2][c+2]==player && board[r-3][c+3]==player){
                return 1;
            }
            
        } 
    }
    return 0;
}

int generateRandoms(board_t board,int lower, int upper) 
{ 
    while(1){
    int num = (rand() % (upper - lower + 1)) + lower; 
    if(is_valid_location(board, num)){
        return num;
    }
    }
} 


typedef struct{
    int col;
    int score;
} move_score;


move_score best_move(board_t board, player_t player, int alpha, int beta, int depth, int max_min) {
    move_score best;
    best.score = (max_min == 1) ? -INT_MAX : INT_MAX;
    best.col = -1;

    if (has_won(board, player)) {
        int score = 1 - depth;
        best.score = 1;
        return best;
    } else if (has_won(board, (player == 'R') ? 'B' : 'R')) {
        int score = -depth - 1;
        best.score = -1;
        return best;
    } else if (is_draw(board)) {
        int score = -depth;
        best.score = 0;
        return best;
    }

    if (max_min == 1) {
        for (int col = 0; col < TOTAL_COL; col++) {
            if (is_valid_location(board, col)) {
                int row = next_open_row(board, col);
                drop_piece(board, row, col, player);

                move_score eval = best_move(board, player, alpha, beta, depth + 1, 0);

                board[row][col] = '.';

                if (eval.score > best.score) {
                    best.score = eval.score;
                    best.col = col;
                }
                alpha = (alpha > best.score) ? alpha : best.score;
                if (alpha >= beta) {
                    break;
                }
            }
        }
    } else { // max_min = 0
        for (int col = 0; col < TOTAL_COL; col++) {
            if (is_valid_location(board, col)) {
                int row = next_open_row(board, col);
                drop_piece(board, row, col, (player == 'R') ? 'B' : 'R');

                move_score eval = best_move(board, player, alpha, beta, depth + 1, 1);

                board[row][col] = '.';

                if (eval.score < best.score) {
                    best.score = eval.score;
                    best.col = col;
                }
                beta = (beta < best.score) ? beta : best.score;
                if (alpha >= beta) {
                    break;
                }
            }
        }
    }
    return best;
}





int main(){
    board_t board;
    initiate_board(board);
    print_borad(board);

    // User Choice of Red of Blue
    player_t user_choice;
    printf("Do you want to start as Red (R) or Blue (B)? ");
    scanf(" %c", &user_choice);
    if (user_choice != 'R' && user_choice != 'B')
    {   
        while(1){
            printf("Invalid choice. Please select 'R' or 'B' :");
            scanf(" %c", &user_choice);
            if (user_choice == 'R' || user_choice == 'B'){
                break;
            }
        }

    }
    player_t computer_choise = (user_choice=='R')?'B':'R';
    player_t current_player = 'R';

    // Start Game
    int move;
    while(1){
        if(current_player==user_choice){
            printf("Choose your move (1-%d) :", TOTAL_COL);
            scanf("%d", &move);
            if (move > TOTAL_COL || move < 1 || (!is_valid_location(board, move-1))){   
                while(1){ 
                    printf("Invalid choice. Please select valid move: ");
                    scanf(" %d", &move);
                    if ((move >= 1) && (move <= TOTAL_COL) && (is_valid_location(board, move-1))){break;}
                }

            }

            int row = next_open_row(board, move-1);
            drop_piece(board, row, move-1, user_choice);

        }
        else{
            printf("\nComputer is thinking..\n");
            move_score best = best_move(board, computer_choise, INT_MIN, INT_MAX, 0, 1);
            int col = best.col;
            int row = next_open_row(board, col);
            drop_piece(board, row, col, computer_choise);
        }

        print_borad(board);

        if(has_won(board, current_player)){
            (current_player==user_choice)?printf("You Won\n"):printf("Computer Won\n");
            break;
        }

        if(is_draw(board)){
            printf("Game Draw\n");
            break;
        }

        current_player=(current_player=='R')?'B':'R';
    }
}