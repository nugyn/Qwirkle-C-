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

    SaveGame sg;
    string value = "";
    string board = "";
    int playerPos = 1;
    int currentPlayer = 1;
    int boardPos = 9;
    int other = 0;
    bool boardFill = false;
    for (std::string line; getline(inFile, line);)
    {
        if ((playerPos % 3) == 1) //read first line
        {
            string value = line;
            if (currentPlayer == 1)
            {
                sg.playerName1 = value;
                ++playerPos;
            }
            else if (currentPlayer == 2)
            {
                sg.playerName2 = value;
                ++playerPos;
            }
        }
        else if ((playerPos % 3) == 2) //read second line
        {
            if (currentPlayer == 1)
            {
                int number;
                std::istringstream iss(line);
                iss >> number;
                if (!iss.good())
                {
                    sg.playerScore1 = number;
                    ++playerPos;
                }
            }
            else if (currentPlayer == 2)
            {
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
        else if ((playerPos % 3) == 0) //read third line
        {
            string value = line;

            if (currentPlayer == 1)
            {
                sg.playerHand1 = value;
                playerPos = 1;
                ++currentPlayer;
            }
            else if (currentPlayer == 2)
            {
                sg.playerHand2 = value;
                playerPos = 1;
                currentPlayer = 3;
                value = "It's done";
            }
        }
        //std::cout << value << "|" <<currentPlayer << std::endl;
        if (currentPlayer > 2 && boardFill == true)
        {
                
            if(boardPos == 9){
                --boardPos;
            }
            else if (boardPos == 8)
            {
                sg.board += line + "\n";


                --boardPos;
            }
            else if (boardPos == 7)
            {
                sg.board += line + "\n";


                --boardPos;
            }
            else if (boardPos == 6)
            {
                sg.board += line + "\n";
                --boardPos;
            }
            else if (boardPos == 5)
            {
                sg.board += line + "\n";
                --boardPos;
            }
            else if (boardPos == 4)
            {
                sg.board += line + "\n";
                --boardPos;
            }
            else if (boardPos == 3)
            {
                sg.board += line + "\n";
                --boardPos;
            }
            else if (boardPos == 2)
            {
                sg.board += line + "\n";
                --boardPos;
            }
            else if (boardPos == 1)
            {
                boardPos = -1;
                ++other;
            }

            if (boardPos == -1)
            {
                if (other == 1)
                {
                    sg.bag = line;
                    ++other;
                }
                else if (other == 2)
                {
                    sg.currentPlayer = line;
                    other = -1;
                }
            }
        }
        boardFill = true;
    }
    // std::cout << sg.playerName1 << std::endl;
    // std::cout << sg.playerScore1 << std::endl;
    // std::cout << sg.playerHand1 << std::endl;
    // std::cout << sg.playerName2 << std::endl;
    // std::cout << sg.playerScore2 << std::endl;
    // std::cout << sg.playerHand2 << std::endl;

    std::cout << sg.board << std::endl;

    std::cout << sg.bag << std::endl;

    std::cout << sg.currentPlayer<< std::endl;

    return sg;
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

    // writeFile(saveGame);
    SaveGame sg = readFile("savegame.txt");

    // std::cout << sg.playerName1 << std::endl;
    // std::cout << sg.playerScore1 << std::endl;
    // std::cout << sg.playerHand1 << std::endl;

    return 0;
}