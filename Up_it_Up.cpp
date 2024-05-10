#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Cube {
    int8_t state[8];
};

const int BoardSize = 3;

// Board is a 2D vector of cubes
typedef std::vector<std::vector<Cube>> Board;

struct BoardHistory
{
    Board board;
    std::string history;
};

bool isSolved(Board &board){
    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            if(board[i][j].state[0] != 0 && board[i][j].state[0] != 6 ) {
                return false;
            }
        }
    }

    return true;
}

void printBoard(const Board &board) {
    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            std::cout << board[i][j].state[0] << " ";
        }
        std::cout << std::endl;
    }
}

void down(Cube &cube, BoardHistory &boardHistory) {
    int x = cube.state[6];
    int y = cube.state[7];

    if (x == 0 || x == 1) {
        // Rotation Segment
        int a = cube.state[0];
        cube.state[0] = cube.state[3];
        cube.state[3] = cube.state[5];
        cube.state[5] = cube.state[1];
        cube.state[1] = a;

        // Swapping the Cubes
        std::swap(boardHistory.board[x + 1][y], boardHistory.board[x][y]);

        // Updating Cube Internal Coordinates
        boardHistory.board[x + 1][y].state[6] = x + 1;
        boardHistory.board[x][y].state[6] = x;
    }

    boardHistory.history = "D" + boardHistory.history;
}

void up(Cube &cube, BoardHistory &boardHistory) {
    int x = cube.state[6];
    int y = cube.state[7];

    if (x == 1 || x == 2) {
        // Rotation Segment
        int a = cube.state[0];
        cube.state[0] = cube.state[1];
        cube.state[1] = cube.state[5];
        cube.state[5] = cube.state[3];
        cube.state[3] = a;

        // Swapping the Cubes
        std::swap(boardHistory.board[x - 1][y], boardHistory.board[x][y]);

        // Updating Cube Internal Coordinates
        boardHistory.board[x - 1][y].state[6] = x - 1;
        boardHistory.board[x][y].state[6] = x;
    }
    
    boardHistory.history = "U" + boardHistory.history;
}

void left(Cube &cube, BoardHistory &boardHistory) {
    int x = cube.state[6];
    int y = cube.state[7];

    if (y == 1 || y == 2) {
        // Rotation Segment
        int a = cube.state[0];
        cube.state[0] = cube.state[4];
        cube.state[4] = cube.state[5];
        cube.state[5] = cube.state[2];
        cube.state[2] = a;

        // Swapping the Cubes
        std::swap(boardHistory.board[x][y - 1], boardHistory.board[x][y]);

        // Updating Cube Internal Coordinates
        boardHistory.board[x][y - 1].state[7] = y - 1;
        boardHistory.board[x][y].state[7] = y;
    }

    boardHistory.history = "L" + boardHistory.history;
}

void right(Cube &cube, BoardHistory &boardHistory) {
    int x = cube.state[6];
    int y = cube.state[7];

    if (y == 0 || y == 1) {
        // Rotation Segment
        int a = cube.state[0];
        cube.state[0] = cube.state[2];
        cube.state[2] = cube.state[5];
        cube.state[5] = cube.state[4];
        cube.state[4] = a;

        // Swapping the Cubes
        std::swap(boardHistory.board[x][y + 1], boardHistory.board[x][y]);

        // Updating Cube Internal Coordinates
        boardHistory.board[x][y + 1].state[7] = y + 1;
        boardHistory.board[x][y].state[7] = y;
    }

    boardHistory.history = "R" + boardHistory.history;
}

BoardHistory copyConstructor(BoardHistory boardHistory){
    Board newBoard(BoardSize, std::vector<Cube>(BoardSize));

    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            newBoard[i][j] = boardHistory.board[i][j];
        }
    }

    std::string newHistory = boardHistory.history;

    return {newBoard, newHistory};
}

// Function to get a list of possible moves for the current state
std::pair<std::vector<std::string>, std::pair<int, int>> getPossibleMoves(const Board &current_state) {
    std::vector<std::string> possible_moves;
    std::pair<int, int> gap_location;

    // Return a list of moves (e.g., "L", "R", "U", "D")
    if (current_state[0][0].state[0] == 0){
        possible_moves.push_back("L");
        possible_moves.push_back("U");
        gap_location = {0,0};
    }
    else if (current_state[0][1].state[0] == 0){
        possible_moves.push_back("L");
        possible_moves.push_back("U");
        possible_moves.push_back("R");
        gap_location = {0,1};
    }
    else if (current_state[0][2].state[0] == 0){
        possible_moves.push_back("U");
        possible_moves.push_back("R");
        gap_location = {0,2};
    }
    else if (current_state[1][0].state[0] == 0){
        possible_moves.push_back("L");
        possible_moves.push_back("U");
        possible_moves.push_back("D");
        gap_location = {1,0};
    }
    else if (current_state[1][1].state[0] == 0){
        possible_moves.push_back("L");
        possible_moves.push_back("U");
        possible_moves.push_back("D");
        possible_moves.push_back("R");
        gap_location = {1,1};
    }
    else if (current_state[1][2].state[0] == 0){
        possible_moves.push_back("R");
        possible_moves.push_back("U");
        possible_moves.push_back("D");
        gap_location = {1,2};
    }
    else if (current_state[2][0].state[0] == 0){
        possible_moves.push_back("L");
        possible_moves.push_back("D");
        gap_location = {2,0};
    }
    else if (current_state[2][1].state[0] == 0){
        possible_moves.push_back("L");
        possible_moves.push_back("R");
        possible_moves.push_back("D");
        gap_location = {2,1};
    }
    else if (current_state[2][2].state[0] == 0){
        possible_moves.push_back("R");
        possible_moves.push_back("D");
        gap_location = {2,2};
    }

    return {possible_moves, gap_location};
}

// Function to apply a move to the current state and generate a new state
void applyMove(BoardHistory &currentBoardHistory, const std::string &move) {
    
    // find gap location 
    std::pair<int, int> gapLocation;
    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            if(currentBoardHistory.board[i][j].state[0] == 0){
                gapLocation = {i,j};
            }
        }
    }

    if (move == "U") {
        up(currentBoardHistory.board[gapLocation.first + 1][gapLocation.second], currentBoardHistory);
    } else if (move == "D") {
        down(currentBoardHistory.board[gapLocation.first - 1][gapLocation.second], currentBoardHistory);
    } else if (move == "L") {
        left(currentBoardHistory.board[gapLocation.first][gapLocation.second + 1], currentBoardHistory);
    } else if (move == "R") {
        right(currentBoardHistory.board[gapLocation.first][gapLocation.second - 1], currentBoardHistory);
    } else {
    std::cout << "Invalid move! Please try again." << std::endl;
    }

}

// Function to generate next updated board states based on the current state and a move
std::vector<BoardHistory> generateNextStates(BoardHistory currentBoardHistory) {
    std::vector<BoardHistory> nextBoardHistories;

    std::vector<std::string> moveList;
    std::pair<int, int> gapLocation;
    std::pair<std::vector<std::string>, std::pair<int, int>> temp = getPossibleMoves(currentBoardHistory.board);
    moveList = temp.first;
    gapLocation = temp.second;
    std::string latestMove = currentBoardHistory.history.substr(0,1);
    // Remove the complementary move from the list of possible moves
    if (latestMove == "U") {
        moveList.erase(std::remove(moveList.begin(), moveList.end(), "D"), moveList.end());
    } else if (latestMove == "D") {
        moveList.erase(std::remove(moveList.begin(), moveList.end(), "U"), moveList.end());
    } else if (latestMove == "L") {
        moveList.erase(std::remove(moveList.begin(), moveList.end(), "R"), moveList.end());
    } else if (latestMove == "R") {
        moveList.erase(std::remove(moveList.begin(), moveList.end(), "L"), moveList.end());
    }

    // Loop over all possible moves
    for (const std::string move : moveList) {
        BoardHistory temp = copyConstructor(currentBoardHistory);
        // Apply the move to the current state to generate a new state
        applyMove(temp, move);
        nextBoardHistories.push_back(temp);
    }

    return nextBoardHistories;
}

void BFSSolve(BoardHistory &boardHistory) {
    std::queue<BoardHistory> q;
    q.push(boardHistory);
    printBoard(boardHistory.board);

    while (!q.empty()) {
        BoardHistory currentBoardHistory = q.front();
        q.pop();
        printBoard(currentBoardHistory.board);
        std::cout << currentBoardHistory.history << std::endl;

        if (isSolved(currentBoardHistory.board)) {
            std::cout << "Solved!" << std::endl;
            printBoard(currentBoardHistory.board);
            std::cout << currentBoardHistory.history << std::endl;
            return;
        }

        std::vector<BoardHistory> nextBoardHistories = generateNextStates(currentBoardHistory);
        for (BoardHistory &nextState : nextBoardHistories) {
            q.push(nextState);
        }
    }

    std::cout << "No solution found!" << std::endl;
}


int main() {
    

    // Initializing the basic components of the board
    // Cube cube2 = {2,6,3,1,5,4,0,1};
    Cube cube1 = {6,4,3,2,5,1,0,0};
    Cube cube2 = {6,4,3,2,5,1,0,1};
    Cube cube3 = {6,4,3,2,5,1,0,2};
    Cube cube4 = {6,4,3,2,5,1,1,0};
    Cube cube5 = {6,4,3,2,5,1,1,2};
    Cube cube6 = {6,4,3,2,5,1,2,0};
    Cube cube7 = {4,1,3,6,5,2,1,1};
    Cube cube8 = {6,4,3,2,5,1,2,2};
    Cube empty = {0,0,0,0,0,0,2,1};

    Board board={{cube1, cube2, cube3}, {cube4, cube7, cube5}, {cube6, empty, cube8}};

    // Initializing new board history
    BoardHistory boardHistory;
    boardHistory.board = board;
    boardHistory.history = "";


    // std::cout<< isSolved(boardHistory.board) << std::endl;
    // std::vector<BoardHistory> possibleStates = generateNextStates(boardHistory);
    // for (int i = 0; i < possibleStates.size(); i++) {
    //     printBoard(possibleStates[i].board);
    //     std::cout << std::endl;
    // }

    BFSSolve(boardHistory);

    return 0;
}
