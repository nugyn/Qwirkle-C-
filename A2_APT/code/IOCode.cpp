#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct SaveGame
{
    string playerName1;
    int playerScore1;
    string playerHand1;

    string playerName2;
    int playerScore2;
    string playerHand2;

    string board;
    string bag;
    string currentPlayer;
};

void writeFile(SaveGame s)
{

    ofstream outputFile;
    outputFile.open("savegame.txt");

    outputFile << s.playerName1 << endl;
    outputFile << s.playerScore1 << endl;
    outputFile << s.playerHand1 << endl;

    outputFile << s.playerName2 << endl;
    outputFile << s.playerScore2 << endl;
    outputFile << s.playerHand2 << endl;

    outputFile << s.board << endl;
    outputFile << s.bag << endl;
    outputFile << s.currentPlayer << endl;

    outputFile.close();
}

SaveGame readFile(string fileName)
{

    string line;
    ifstream inFile;
    inFile.open("savegame.txt");

    struct saveGame
    {
        string playerName1;
        int playerScore1;
        string playerHand1;

        string playerName2;
        int playerScore2;
        string playerHand2;

        string board;
        string bag;
        string currentPlayer;
    };

    saveGame sg;
    string value = "";
    string board = "";
    int playerPos = 1;
    int currentPlayer = 1;
    int boardPos = 6;
    int other = 0;
    for (std::string line; getline(inFile, line);)
    {
        if ((playerPos % 3) == 2)
        {
            string value = line;
            if(currentPlayer == 1){
            sg.playerName1 = value;
            ++playerPos;
            }
            else if(currentPlayer == 2){
                sg.playerName2 = value;
                ++playerPos;
            }
        }
        else if ((playerPos % 2) == 1)
        {
            if(currentPlayer == 1){
                int number;
                std::istringstream iss(line);
                iss >> number;
                if (!iss.good())
                {
                    sg.playerScore1 = number;
                    ++playerPos;
                }
            }
            else if(currentPlayer == 2){
                int number;
                std::istringstream iss(line);
                iss >> number;
                if (!iss.good())
                {
                    sg.playerScore1 = number;
                    ++playerPos;
                }
            }
        }
        else if ((playerPos % 3) == 0)
        {
            string value = line;

            if(currentPlayer == 1){
                sg.playerHand1 = value;
                playerPos = 0;
            }
            else if(currentPlayer == 2){
                sg.playerHand2 = value;
                playerPos = 0;
            }
            ++currentPlayer;
        }
       

        if (boardPos == 8)
         {
            board = line + "\n";
            --boardPos;
         }
        else if(boardPos == 7){
            board = line + "\n";
            --boardPos;
        }
        else if(boardPos == 6){
            board = line + "\n";
            --boardPos;
        }
        else if(boardPos == 5){
            board = line + "\n";
            --boardPos;
        }
        else if(boardPos == 4){
            board = line + "\n";
            --boardPos;
        }
        else if(boardPos == 3){
            board = line + "\n";
            --boardPos;
        }
        else if(boardPos == 2){
            board = line + "\n";
            --boardPos;
        }
        else if(boardPos == 1){
            board = line;
            boardPos == 0;
            ++other;
        }

        if(other == 1){
            sg.bag = line;
            ++other;
        }
        else if(other == 2){
            sg.currentPlayer = line;
        }
    }
}

int main()
{
    struct SaveGame saveGame;
    saveGame.playerName1 = "Duy";
    saveGame.playerScore1 = 0;
    saveGame.playerHand1 = "R1,R2,R3,R4,R5";

    saveGame.playerName2 = "Duy Linh";
    saveGame.playerScore2 = 0;
    saveGame.playerHand2 = "R1,R2,R3,R4,R5";

    saveGame.board = "0  1  2  3  4  5  6\n-------------------\nA|R1|R2|R3|R4|R5|R6\nB|B1|B2|B3|B4|B5|B6\nC|C1|C2|C3|C4|C5|C6\nD|D1|D2|D3|D4|D5|D6\nE|E1|E2|E3|E4|E5|E6";
    saveGame.bag = "A1,A2,A3,A4,A5,A6,A7";
    saveGame.currentPlayer = "Duy";

    writeFile(saveGame);
    return 0;
}