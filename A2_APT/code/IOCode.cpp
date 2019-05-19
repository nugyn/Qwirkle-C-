
#include "IOCode.h"

void writeFile(SaveGame s)
{

    std::ofstream outputFile;
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

SaveGame readFile(std::string fileName)
{

    std::string line;
    std::ifstream inFile;
    inFile.open("savegame.txt");

    struct SaveGame
    {
        std::string playerName1;
        int playerScore1;
        std::string playerHand1;

        std::string playerName2;
        int playerScore2;
        std::string playerHand2;

        std::string board;
        std::string bag;
        std::string currentPlayer;
    };

    SaveGame sg;
    std::string value = "";
    std::string board = "";
    int playerPos = 1;
    int currentPlayer = 1;
    int boardPos = 9;
    int other = 0;
    bool boardFill = false;
    for (std::string line; getline(inFile, line);)
    {
        if ((playerPos % 3) == 1) //read first line
        {
            std::string value = line;
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
            std::string value = line;

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
        if (currentPlayer > 2 && boardFill == true) // allPlayers read, now read the board
        {

            if (boardPos == 9)
            {
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

    std::cout << sg.board << std::endl;

    std::cout << sg.bag << std::endl;

    std::cout << sg.currentPlayer << std::endl;

    return sg;
}
