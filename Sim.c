#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h> 
#include <time.h> 
/*
 * The status of a line.
 */
enum {
    NO = 0, /* No line */
    RED = 1,
    BLUE = 2
};

/*
 * The board records the colors of the lines.
 * board[0] = color of 12
 * board[1] = color of 13
 * ...
 * board[14] = color of 56
 */
typedef char board_t[15];
typedef char player_t; /* A player should be RED or BLUE. */

void initiate_board(board_t board){
    for (int i=0; i<=14; i++){
        board[i] = '.';
    }
}

void play_move(board_t board, int move, player_t player){
    board[move] =  player;
}

int is_valid_move(board_t board, int move){
    if ((move > 14) || (move < 0)){
        return 0;
    }
    if(board[move]=='.'){
        return 1;
    }
    return 0;
}

int has_lost(board_t board, player_t player) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            for (int k = 0; k < 4 - i - j; k++) {
                int a1 = (i * (11 - i) / 2) + j + 1;
                int a2 = a1 + k + 1;
                int a3 = 6 + k + (i + j) * (9 - i - j) / 2;
                a1 = a1 - 1;
                a2 = a2 - 1;
                a3 = a3 - 1;
                
                if (board[a1] == board[a2] && board[a2] == board[a3] && board[a3] == player) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int is_full(board_t board)
{
    for(int i=0; i<=14; i++){
        if (board[i] == '.'){
            return 0;
        }  
    }
    return 1;
}

typedef struct {
    int line; /* 0 for 12, 1 for 13, ..., 14 for 56. */
    int score; /* -1 for loss, 0 for draw, 1 for win. */
} move_score;

move_score best_move(board_t board, player_t player, int alpha, int beta, int depth, int max_min) {
    move_score best;
    best.score = (max_min == 1) ? -INT_MAX : INT_MAX;
    best.line = -1;

    if (has_lost(board, player)) {
        best.score = -1;
        return best;
    } 
    else if (has_lost(board, (player == 'R') ? 'B' : 'R')) {
        best.score = 1;
        return best;
    }


    if (max_min == 1) {
        for (int col = 14; col >= 0; col--) {
            if (is_valid_move(board, col)) {
                
                play_move(board, col, player);

                move_score eval = best_move(board, player, alpha, beta, depth + 1, 0);

                board[col] = '.';

                if (eval.score > best.score) {
                    best.score = eval.score;
                    best.line = col;
                }
                alpha = (alpha > best.score) ? alpha : best.score;
                if (alpha >= beta) {
                    break;
                }
            }
        }
    } else { // max_min = 0
        for (int col = 14; col >= 0; col--) {
            if (is_valid_move(board, col)) {
                play_move(board, col, (player == 'R') ? 'B' : 'R');

                move_score eval = best_move(board, player, alpha, beta, depth + 1, 1);

                board[col] = '.';

                if (eval.score < best.score) {
                    best.score = eval.score;
                    best.line = col;
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

void print_board(board_t board)
{
    for (int i = 0; i < 15; ++i) {
        printf("%c", board[i]);
        printf(" ");
    }
    printf("\n");
}

int generateRandoms(board_t board,int lower, int upper) 
{ 
    while(1){
    int num = (rand() % (upper - lower + 1)) + lower; 
    if(is_valid_move(board, num)){
        return num;
    }
    }
} 

int main()
{
    board_t board;
    initiate_board(board);
    printf("Initializing Board...\n");
    print_board(board); printf("\n");


    player_t user;
    printf("Red plays First\n");
    printf("Which Color do you choose? (R or B): ");
    scanf("%c", &user);
    if (user != 'R' && user != 'B')
    {   
        while(1){
            printf("Invalid choice. Please select 'R' or 'B' :");
            scanf(" %c", &user);
            if (user == 'R' || user == 'B'){
                break;
            }
        }

    }printf("\n");
    player_t computer = (user == 'R')?'B':'R';
    player_t current = 'R';

    while(1){
        if (current == user){
            int move;
            printf("Enter your move (1, 15): ");
            scanf("%d", &move);
            while(!is_valid_move(board, move - 1)){
                printf("Not a valid move.\nEnter move again: ");
                scanf("%d", &move);}
        play_move(board, move-1, current);
        }

        else{
            printf("Computer is thinking...\n");
            move_score computer_move = best_move(board, current, INT_MIN, INT_MAX, 0, 1);
            play_move(board, computer_move.line , current);
        }

        print_board(board);
        printf("\n");

        if(has_lost(board, current)){
            (current==user)?printf("OOPS! Computer Won\n"):printf("HURRAY! You Won\n");
            break;
        }

        current = (current == user)? computer: user;

    }
    return 0;
}
