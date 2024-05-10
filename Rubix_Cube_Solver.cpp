#include <iostream>
#include <array>
#include <queue>
#include <algorithm>
#include <deque>
#include <list>

using namespace std;

class Cube
{
public:
    std::array<int8_t, 24> state;
    std::string moveHistory = "";

    // Cube()
    // {
    //     setInputState(state);
    //     std::cout << state[12] << endl;
    // }

    Cube(const std::array<int8_t, 24> &inputState)
    {
        state = inputState;

    }

    Cube(const std::array<int8_t, 24> &inputState, std::string move)
    {
        state = inputState;
        moveHistory = move;
    }

    std::array<int8_t, 24> getState()
    {
        return state;
    }

    std::string getMove()
    {
        return moveHistory;
    }


    std::string printColor(int8_t color)
    {
        if(color == 1){
            return "\033[0;97m@\033[0m";
        } else if(color == 2){
            return "\033[0;34m@\033[0m";
        } else if(color == 3){
            return "\033[38;5;208m@\033[0m";
        } else if(color == 4){
            return "\033[0;31m@\033[0m";
        } else if(color == 5){
            return "\033[0;32m@\033[0m";
        } else if(color == 6){
            return "\033[0;93m@\033[0m";
        } else {
            return "Invalid Color";
        }
    }

    void printCube()
    {
        std::cout << "The state of the cube is as follows: " << endl;
        std::cout << "Front Face: " << endl;
        std::cout << printColor(state[3]) << " " << printColor(state[0]) << endl;
        std::cout << printColor(state[6]) << " " << printColor(state[9]) << endl;
        std::cout << endl;
        std::cout << "Right Face: " << endl;
        std::cout << printColor(state[2]) << " " << printColor(state[16]) << endl;
        std::cout << printColor(state[10]) << " " << printColor(state[14]) << endl;
        std::cout << endl;
        std::cout << "Left Face: " << endl;
        std::cout << printColor(state[20]) << " " << printColor(state[4]) << endl;
        std::cout << printColor(state[22]) << " " << printColor(state[8]) << endl;
        std::cout << endl;
        std::cout << "Up Face: " << endl;
        std::cout << printColor(state[19]) << " " << printColor(state[17]) << endl;
        std::cout << printColor(state[5]) << " " << printColor(state[1]) << endl;
        std::cout << endl;
        std::cout << "Down Face: " << endl;
        std::cout << printColor(state[7]) << " " << printColor(state[11]) << endl;
        std::cout << printColor(state[23]) << " " << printColor(state[13]) << endl;
        std::cout << endl;
        std::cout << "Back Face: " << endl;
        std::cout << printColor(state[15]) << " " << printColor(state[18]) << endl;
        std::cout << printColor(state[12]) << " " << printColor(state[21]) << endl;
        std::cout << endl;
    }

    bool isValid()
    {
        return true;
    }

    bool isSolved()
    {
        std::array<int8_t, 24> solvedState2 = {1, 3, 2, 1, 5, 3, 1, 4, 5, 1, 2, 4, 6, 4, 2, 6, 2, 3, 6, 3, 5, 6, 5, 4}; // Assuming you're holding the cube with the white face at front and the blue face at right, orange face at top. Means the unmoved cubelet has bld = yellow, ldb = green, dbl = red.

        for (int i = 0; i < 24; i++)
        {
            if (solvedState2[i] != state[i])
            {
                return false;
            }
        }
        return true;
    }

    Cube R()
    {
        std::array<int8_t, 24> newState;
        // 1st Cubelet
        newState[17] = state[0];
        newState[15] = state[1];
        newState[16] = state[2];
        // 4th Cubelet
        newState[1] = state[9];
        newState[2] = state[10];
        newState[0] = state[11];
        // 5th Cubelet
        newState[11] = state[12];
        newState[9] = state[13];
        newState[10] = state[14];
        // 6th Cubelet
        newState[13] = state[15];
        newState[14] = state[16];
        newState[12] = state[17];

        // Rest of the cubelets
        newState[3] = state[3];
        newState[4] = state[4];
        newState[5] = state[5];
        newState[6] = state[6];
        newState[7] = state[7];
        newState[8] = state[8];
        newState[18] = state[18];
        newState[19] = state[19];
        newState[20] = state[20];
        newState[21] = state[21];
        newState[22] = state[22];
        newState[23] = state[23];

        return Cube(newState, "R" + moveHistory);
    }

    Cube Rdash()
    {
        std::array<int8_t, 24> newState;

        // 1st Cubelet
        newState[11] = state[0];
        newState[9] = state[1];
        newState[10] = state[2];
        // 4th Cubelet
        newState[13] = state[9];
        newState[14] = state[10];
        newState[12] = state[11];
        // 5th Cubelet
        newState[17] = state[12];
        newState[16] = state[14];
        newState[15] = state[13];
        // 6th Cubelet
        newState[1] = state[15];
        newState[2] = state[16];
        newState[0] = state[17];

        // Rest of the cubelets
        newState[3] = state[3];
        newState[4] = state[4];
        newState[5] = state[5];
        newState[6] = state[6];
        newState[7] = state[7];
        newState[8] = state[8];
        newState[18] = state[18];
        newState[19] = state[19];
        newState[20] = state[20];
        newState[21] = state[21];
        newState[22] = state[22];
        newState[23] = state[23];

        return Cube(newState,  "Rdash" + moveHistory);
    }

    Cube R2()
    {
        std::array<int8_t, 24> newState;
        // 1st Cubelet
        newState[17] = state[0];
        newState[15] = state[1];
        newState[16] = state[2];
        // 4th Cubelet
        newState[1] = state[9];
        newState[2] = state[10];
        newState[0] = state[11];
        // 5th Cubelet
        newState[11] = state[12];
        newState[9] = state[13];
        newState[10] = state[14];
        // 6th Cubelet
        newState[13] = state[15];
        newState[14] = state[16];
        newState[12] = state[17];

        // Rest of the cubelets
        newState[3] = state[3];
        newState[4] = state[4];
        newState[5] = state[5];
        newState[6] = state[6];
        newState[7] = state[7];
        newState[8] = state[8];
        newState[18] = state[18];
        newState[19] = state[19];
        newState[20] = state[20];
        newState[21] = state[21];
        newState[22] = state[22];
        newState[23] = state[23];

        std::array<int8_t, 24> newState2;
        // 1st Cubelet
        newState2[17] = newState[0];
        newState2[15] = newState[1];
        newState2[16] = newState[2];
        // 4th Cubelet
        newState2[1] = newState[9];
        newState2[2] = newState[10];
        newState2[0] = newState[11];
        // 5th Cubelet
        newState2[11] = newState[12];
        newState2[9] = newState[13];
        newState2[10] = newState[14];
        // 6th Cubelet
        newState2[13] = newState[15];
        newState2[14] = newState[16];
        newState2[12] = newState[17];

        // Rest of the cubelets
        newState2[3] = newState[3];
        newState2[4] = newState[4];
        newState2[5] = newState[5];
        newState2[6] = newState[6];
        newState2[7] = newState[7];
        newState2[8] = newState[8];
        newState2[18] = newState[18];
        newState2[19] = newState[19];
        newState2[20] = newState[20];
        newState2[21] = newState[21];
        newState2[22] = newState[22];
        newState2[23] = newState[23];

        return Cube(newState2, "R2" + moveHistory);
    }

    Cube F()
    {
        std::array<int8_t, 24> newState;
        // 2nd Cubelet
        newState[0] = state[3];
        newState[1] = state[4];
        newState[2] = state[5];
        // 1st Cubelet
        newState[9] = state[0];
        newState[10] = state[1];
        newState[11] = state[2];
        // 4th Cubelet
        newState[6] = state[9];
        newState[7] = state[10];
        newState[8] = state[11];
        // 3th Cubelet
        newState[3] = state[6];
        newState[4] = state[7];
        newState[5] = state[8];

        // Rest of the cubelets
        newState[12] = state[12];
        newState[13] = state[13];
        newState[14] = state[14];
        newState[15] = state[15];
        newState[16] = state[16];
        newState[17] = state[17];
        newState[18] = state[18];
        newState[19] = state[19];
        newState[20] = state[20];
        newState[21] = state[21];
        newState[22] = state[22];
        newState[23] = state[23];

        return Cube(newState, "F" + moveHistory);
    }

    Cube Fdash()
    {
        std::array<int8_t, 24> newState;
        // 2nd Cubelet
        newState[6] = state[3];
        newState[7] = state[4];
        newState[8] = state[5];
        // 1st Cubelet
        newState[3] = state[0];
        newState[4] = state[1];
        newState[5] = state[2];
        // 4th Cubelet
        newState[0] = state[9];
        newState[1] = state[10];
        newState[2] = state[11];
        // 3th Cubelet
        newState[9] = state[6];
        newState[10] = state[7];
        newState[11] = state[8];

        // Rest of the cubelets
        newState[12] = state[12];
        newState[13] = state[13];
        newState[14] = state[14];
        newState[15] = state[15];
        newState[16] = state[16];
        newState[17] = state[17];
        newState[18] = state[18];
        newState[19] = state[19];
        newState[20] = state[20];
        newState[21] = state[21];
        newState[22] = state[22];
        newState[23] = state[23];

        return Cube(newState, "Fdash" + moveHistory);
    }

    Cube F2()
    {
        std::array<int8_t, 24> newState;
        // 2nd Cubelet
        newState[6] = state[3];
        newState[7] = state[4];
        newState[8] = state[5];
        // 1st Cubelet
        newState[3] = state[0];
        newState[4] = state[1];
        newState[5] = state[2];
        // 4th Cubelet
        newState[0] = state[9];
        newState[1] = state[10];
        newState[2] = state[11];
        // 3th Cubelet
        newState[9] = state[6];
        newState[10] = state[7];
        newState[11] = state[8];

        // Rest of the cubelets
        newState[12] = state[12];
        newState[13] = state[13];
        newState[14] = state[14];
        newState[15] = state[15];
        newState[16] = state[16];
        newState[17] = state[17];
        newState[18] = state[18];
        newState[19] = state[19];
        newState[20] = state[20];
        newState[21] = state[21];
        newState[22] = state[22];
        newState[23] = state[23];

        std::array<int8_t, 24> newState2;
        // 2nd Cubelet
        newState2[6] = newState[3];
        newState2[7] = newState[4];
        newState2[8] = newState[5];
        // 1st Cubelet
        newState2[3] = newState[0];
        newState2[4] = newState[1];
        newState2[5] = newState[2];
        // 4th Cubelet
        newState2[0] = newState[9];
        newState2[1] = newState[10];
        newState2[2] = newState[11];
        // 3th Cubelet
        newState2[9] = newState[6];
        newState2[10] = newState[7];
        newState2[11] = newState[8];

        // Rest of the cubelets
        newState2[12] = newState[12];
        newState2[13] = newState[13];
        newState2[14] = newState[14];
        newState2[15] = newState[15];
        newState2[16] = newState[16];
        newState2[17] = newState[17];
        newState2[18] = newState[18];
        newState2[19] = newState[19];
        newState2[20] = newState[20];
        newState2[21] = newState[21];
        newState2[22] = newState[22];
        newState2[23] = newState[23];

        return Cube(newState2, "F2" + moveHistory);
    }

    Cube U()
    {
        std::array<int8_t, 24> newState;
        // 7th Cubelet
        newState[16] = state[18];
        newState[17] = state[19];
        newState[15] = state[20];
        // 6th Cubelet
        newState[2] = state[15];
        newState[0] = state[16];
        newState[1] = state[17];
        // 1st Cubelet
        newState[4] = state[0];
        newState[5] = state[1];
        newState[3] = state[2];
        // 2nd Cubelet
        newState[20] = state[3];
        newState[18] = state[4];
        newState[19] = state[5];

        // Rest of the cubelets
        newState[6] = state[6];
        newState[7] = state[7];
        newState[8] = state[8];
        newState[9] = state[9];
        newState[10] = state[10];
        newState[11] = state[11];
        newState[12] = state[12];
        newState[13] = state[13];
        newState[14] = state[14];
        newState[21] = state[21];
        newState[22] = state[22];
        newState[23] = state[23];

        return Cube(newState, "U" + moveHistory);
    }

    Cube Udash()
    {
        std::array<int8_t, 24> newState;
        // 7th Cubelet
        newState[4] = state[18];
        newState[5] = state[19];
        newState[3] = state[20];
        // 6th Cubelet
        newState[20] = state[15];
        newState[18] = state[16];
        newState[19] = state[17];
        // 1st Cubelet
        newState[16] = state[0];
        newState[17] = state[1];
        newState[15] = state[2];
        // 2nd Cubelet
        newState[2] = state[3];
        newState[0] = state[4];
        newState[1] = state[5];

        // Rest of the cubelets
        newState[6] = state[6];
        newState[7] = state[7];
        newState[8] = state[8];
        newState[9] = state[9];
        newState[10] = state[10];
        newState[11] = state[11];
        newState[12] = state[12];
        newState[13] = state[13];
        newState[14] = state[14];
        newState[21] = state[21];
        newState[22] = state[22];
        newState[23] = state[23];

        return Cube(newState, "Udash" + moveHistory);
    }

    Cube U2()
    {
        std::array<int8_t, 24> newState;
        // 7th Cubelet
        newState[16] = state[18];
        newState[17] = state[19];
        newState[15] = state[20];
        // 6th Cubelet
        newState[2] = state[15];
        newState[0] = state[16];
        newState[1] = state[17];
        // 1st Cubelet
        newState[4] = state[0];
        newState[5] = state[1];
        newState[3] = state[2];
        // 2nd Cubelet
        newState[20] = state[3];
        newState[18] = state[4];
        newState[19] = state[5];

        // Rest of the cubelets
        newState[6] = state[6];
        newState[7] = state[7];
        newState[8] = state[8];
        newState[9] = state[9];
        newState[10] = state[10];
        newState[11] = state[11];
        newState[12] = state[12];
        newState[13] = state[13];
        newState[14] = state[14];
        newState[21] = state[21];
        newState[22] = state[22];
        newState[23] = state[23];

        std::array<int8_t, 24> newState2;
        // 7th Cubelet
        newState2[16] = newState[18];
        newState2[17] = newState[19];
        newState2[15] = newState[20];
        // 6th Cubelet
        newState2[2] = newState[15];
        newState2[0] = newState[16];
        newState2[1] = newState[17];
        // 1st Cubelet
        newState2[4] = newState[0];
        newState2[5] = newState[1];
        newState2[3] = newState[2];
        // 2nd Cubelet
        newState2[20] = newState[3];
        newState2[18] = newState[4];
        newState2[19] = newState[5];

        // Rest of the cubelets
        newState2[6] = newState[6];
        newState2[7] = newState[7];
        newState2[8] = newState[8];
        newState2[9] = newState[9];
        newState2[10] = newState[10];
        newState2[11] = newState[11];
        newState2[12] = newState[12];
        newState2[13] = newState[13];
        newState2[14] = newState[14];
        newState2[21] = newState[21];
        newState2[22] = newState[22];
        newState2[23] = newState[23];

        return Cube(newState2, "U2" + moveHistory);
    }


};

void BFSSolve(Cube cube)
{
    // BFS to solve the cube

    std::cout << "Hold the cube such that the unmoved cubelet has back left down = yellow, left down back = green, down back left = red." << std::endl;

    std::queue<Cube> q;
    q.push(cube);
    // cube.printCube();
    while(!q.empty())
    {
        Cube currentCube = q.front();
        // currentCube.printCube();
        std::cout << currentCube.getMove() << " ";
        q.pop();
        if (currentCube.isSolved())
        {

            std::cout << std::endl << std::endl << "The cube has been solved!";
            std::cout << std::endl;
            currentCube.printCube();
            std::cout << "The moves to solve the cube are (Go from back to start): " << currentCube.getMove() << std::endl;
            return;
        }
        else
        {
            // Add all the children of the current cube to the queue
            if (currentCube.getMove().substr(0, 5) == "Rdash")
            {
                q.push(currentCube.F());
                q.push(currentCube.U());
                q.push(currentCube.U2());
                q.push(currentCube.Fdash());
                q.push(currentCube.F2());
                q.push(currentCube.Udash());
            }
            else if (currentCube.getMove().substr(0,2) == "R2")
            {
                q.push(currentCube.Udash());
                q.push(currentCube.F2());
                q.push(currentCube.Fdash());
                q.push(currentCube.U());
                q.push(currentCube.U2());
                q.push(currentCube.F());
            }
            else if (currentCube.getMove().substr(0, 1) == "R")
            {
                q.push(currentCube.Fdash());
                q.push(currentCube.Udash());
                q.push(currentCube.U());
                q.push(currentCube.F2());
                q.push(currentCube.F());
                q.push(currentCube.U2());
            }
            else if (currentCube.getMove().substr(0,5) == "Fdash")
            {
                q.push(currentCube.U2());
                q.push(currentCube.R());
                q.push(currentCube.Rdash());
                q.push(currentCube.U());
                q.push(currentCube.Udash());
                q.push(currentCube.R2());
            }
            else if (currentCube.getMove().substr(0,2) == "F2")
            {
                q.push(currentCube.R2());
                q.push(currentCube.Udash());
                q.push(currentCube.Rdash());
                q.push(currentCube.U());
                q.push(currentCube.R());
                q.push(currentCube.U2());
            }
            else if (currentCube.getMove().substr(0,1) == "F")
            {
                q.push(currentCube.Rdash());
                q.push(currentCube.U());
                q.push(currentCube.Udash());
                q.push(currentCube.R2());
                q.push(currentCube.U2());
                q.push(currentCube.R());
            }
            else if (currentCube.getMove().substr(0,5) == "Udash")
            {
                q.push(currentCube.F2());
                q.push(currentCube.Rdash());
                q.push(currentCube.F());
                q.push(currentCube.R2());
                q.push(currentCube.R());
                q.push(currentCube.Fdash());
            }
            else if (currentCube.getMove().substr(0,2) == "U2")
            {
                q.push(currentCube.R());
                q.push(currentCube.Rdash());
                q.push(currentCube.R2());
                q.push(currentCube.F());
                q.push(currentCube.Fdash());
                q.push(currentCube.F2());
            }
            else if (currentCube.getMove().substr(0,1) == "U")
            {
                q.push(currentCube.R());
                q.push(currentCube.Rdash());
                q.push(currentCube.R2());
                q.push(currentCube.F());
                q.push(currentCube.Fdash());
                q.push(currentCube.F2());
            }
            else if(currentCube.getMove() == "")
            {
                q.push(currentCube.R());
                q.push(currentCube.Rdash());
                q.push(currentCube.R2());
                q.push(currentCube.F());
                q.push(currentCube.Fdash());
                q.push(currentCube.F2());
                q.push(currentCube.U());
                q.push(currentCube.Udash());
                q.push(currentCube.U2());
            }
        }
    }

    std::cout << "The queue got empty!" << std::endl;
}

static void printColorCode()
{
    std::cout << "Color Codes are as follows:" << std::endl;
    std::cout << "1: White" << std::endl;
    std::cout << "2: Blue" << std::endl;
    std::cout << "3: Orange" << std::endl;
    std::cout << "4: Red" << std::endl;
    std::cout << "5: Green" << std::endl;
    std::cout << "6: Yellow" << std::endl;
}

static void takeInputState(std::array<int8_t, 24> &inputState)
{
    std::cout<< "Hold the cube such that the unmoved cubelet has back face left down  = yellow, left face down back = green, down face back left = red." << std::endl;
    // Front Face
    std::cout << "Enter the colors of the front face in a clockwise manner starting from the top left corner:" << std::endl;
    printColorCode();
    std::cin >> inputState[3];
    std::cin >> inputState[0];
    std::cin >> inputState[9];
    std::cin >> inputState[6];

    // Right Face
    std::cout << "Turn the cube to the right face and enter the colors of the right face in a clockwise manner starting from the top left corner:" << std::endl;
    printColorCode();
    std::cin >> inputState[2];
    std::cin >> inputState[16];
    std::cin >> inputState[14];
    std::cin >> inputState[10];
    std::cout << "Turn the cube back to the front face" << std::endl;

    // Left Face
    std::cout << "Turn the cube to the left face and enter the colors of the left face in a clockwise manner starting from the top left corner:" << std::endl;
    printColorCode();
    std::cin >> inputState[20];
    std::cin >> inputState[4];
    std::cin >> inputState[8];
    std::cin >> inputState[22];
    std::cout << "Turn the cube back to the front face" << std::endl;

    // Up Face
    std::cout << "Turn the cube to the up face and enter the colors of the up face in a clockwise manner starting from the top left corner:" << std::endl;
    printColorCode();
    std::cin >> inputState[19];
    std::cin >> inputState[17];
    std::cin >> inputState[1];
    std::cin >> inputState[5];
    std::cout << "Turn the cube back to the front face" << std::endl;

    // Down Face
    std::cout << "Turn the cube to the down face and enter the colors of the down face in a clockwise manner starting from the top left corner:" << std::endl;
    printColorCode();
    std::cin >> inputState[7];
    std::cin >> inputState[11];
    std::cin >> inputState[13];
    std::cin >> inputState[23];
    std::cout << "Turn the cube back to the front face" << std::endl;

    // Back Face
    std::cout << "Turn the cube to the back face by making two right turns and enter the colors of the back face in a clockwise manner starting from the top left corner:" << std::endl;
    printColorCode();
    std::cin >> inputState[15];
    std::cin >> inputState[18];
    std::cin >> inputState[21];
    std::cin >> inputState[12];
    std::cout << "Turn the cube back to the front face by making two left turns" << std::endl;

    return;
}

int main()
{

    std::array<int8_t, 24> solvedState = {1, 3, 2, 1, 5, 3, 1, 4, 5, 1, 2, 4, 6, 4, 2, 6, 2, 3, 6, 3, 5, 6, 5, 4};
    // Assuming you're holding the cube with the white face at front and the blue face at right, orange face at top. Means the unmoved cubelet has bld = yellow, ldb = green, dbl = red.

    // Cube cube(solvedState);
    // cube.printCube();
    // BFSSolve(cube);

    // Testing for each of the moves
    // Cube cubeR = cube.R();
    // cubeR.printCube();

    // Cube cubeRdash = cube.Rdash();
    // cubeRdash.printCube();

    // Cube cubeR2 = cube.R2();
    // cubeR2.printCube();

    // Cube cubeF = cube.F();
    // cubeF.printCube();

    // Cube cubeFdash = cube.Fdash();
    // cubeFdash.printCube();

    // Cube cubeF2 = cube.F2();
    // cubeF2.printCube();

    // Cube cubeU = cube.U();
    // cubeU.printCube();

    // Cube cubeUdash = cube.Udash();
    // cubeUdash.printCube();

    // Cube cubeU2 = cube.U2();
    // cubeU2.printCube();
    
    // std::array<int8_t, 24> inp = {1, 3, 2, 5, 1, 4, 3, 6, 2, 5, 6, 3, 1, 5, 3, 4, 1, 2, 4, 2, 6, 6, 5, 4};
    // Cube cubeTest = Cube(inp);
    // BFSSolve(cubeTest);
        // std::cout << "Color Codes are as follows:" << std::endl;
        // std::cout << "1: White" << std::endl;
        // std::cout << "2: Blue" << std::endl;
        // std::cout << "3: Orange" << std::endl;
        // std::cout << "4: Red" << std::endl;
        // std::cout << "5: Green" << std::endl;
        // std::cout << "6: Yellow" << std::endl;

    // std::array<int8_t, 24> inp2 = {2, 1, 3, 2, 4, 1, 1, 4, 5, 4, 2, 6, 3, 6, 2, 5, 6, 3, 5, 3, 1, 6, 5, 4};
    // Cube cubeTest2 = Cube(inp2);
    // BFSSolve(cubeTest2);

    // std::array<int8_t, 24> inp3 = {3, 6, 2, 3, 5, 6, 2, 6, 4, 1, 4, 5, 3, 1, 5, 4, 1, 2, 1, 3, 2, 6, 5, 4};
    // Cube cubeTest3 = Cube(inp3);
    // BFSSolve(cubeTest3);
    std::array<int8_t, 24> inputState;
    takeInputState(inputState);
    for (int i = 0; i < 24; i++)
    {
        std::cout << inputState[i] << " ";
    }
    Cube cubeTest4 = Cube(inputState);
    cubeTest4.printCube();
    return 0;
}
