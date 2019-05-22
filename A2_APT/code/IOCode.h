#ifndef IOCODE_H
#define IOCODE_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
        std::string activePlayer;
    };

class IOCode
{
public:
    IOCode();
    ~IOCode();

    void writeFile(SaveGame *s, std::string * fileName);
    SaveGame *readFile(std::string fileName);


};

#endif //IOCODE_H
