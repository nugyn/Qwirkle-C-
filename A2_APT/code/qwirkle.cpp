#include "LinkedList.h"
#include "GameEngine.h"
#include "Player.h"
#include "Bag.h"
#include "IOCode.h"

#include <iostream>

#define EXIT_SUCCESS 0
#define NUMBER_OF_PLAYERS 2
#define MAX_LENGTH 26
#define MAX_WIDTH 26
#define HANDSIZE 6

void mainMenu();
void printMenu();
void menuSelect(char input);
void newGame();
void loadGame();
void showInfo();
void quit();

bool exitProgram = false;

int main(void)
{
    // LinkedList* list = new LinkedList();
    // delete list;

    std::cout << "Welcome to Qwirkle!" << std::endl
              << std::endl;
    while (!exitProgram)
    {
        mainMenu();
    }

    return EXIT_SUCCESS;
}

void mainMenu()
{

    printMenu();

    //use this bool to determine if the user has input a valid option
    bool validInput = false;
    char input = '0';
    //while the user hasnt input a valid option

    while (!validInput)
    {
        std::cout << "> ";
        std::cin >> input;
        if (input == '1' || input == '2' || input == '3' || input == '4')
        {
            validInput = true;
            std::cout << std::endl;
            menuSelect(input);
        }
        else
        {
            std::cout << "Invalid Input" << std::endl;
        }
    }
}

void printMenu()
{

    std::cout << "Menu\n";
    std::cout << "----\n";
    std::cout << "1. New Game\n";
    std::cout << "2. Load Game\n";
    std::cout << "3. Show student information\n";
    std::cout << "4. Quit\n";
}

void menuSelect(char input)
{
    if (input == '1')
    {
        newGame();
    }
    else if (input == '2')
    {
        loadGame();
    }
    else if (input == '3')
    {
        showInfo();
    }
    else
    {
        quit();
    }
}

void newGame()
{
    bool validName = false;
    std::string playerNames[NUMBER_OF_PLAYERS] = {"", ""};
    Player **players = new Player *[NUMBER_OF_PLAYERS];
    std::regex nameFormat("^[a-zA-Z]+");
    std::cout << "Starting A New Game\n\n";
    Bag *bagPtr = new Bag();
    bagPtr->fillBag();

    //Make the players and give them their hands
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        std::cout << "Enter a name for player " << i + 1 << "\n";
        while (!validName)
        {
            std::cout << ">";
            std::cin >> playerNames[i];
            if (std::regex_match(playerNames[i], nameFormat))
            {
                validName = true;
                LinkedList *hand = new LinkedList();
                //populate the hand with new tiles and delete the tiles in the bag
                for (int j = 0; j < HANDSIZE; j++)
                {
                    int shape = bagPtr->getTiles()->getTile(0)->getShape();
                    int colour = bagPtr->getTiles()->getTile(0)->getColour();
                    Tile *temp = new Tile(colour, shape);
                    bagPtr->getTiles()->deleteFront();
                    hand->insertFront(temp);
                }
                players[i] = new Player(playerNames[i], hand);
            }
            else
            {
                std::cout << "Only letters allowed \n";
            }
        }
        validName = false;
    }
    std::cout << "\n";
    std::cout << "Let's Play\n";
    TilePtr **board = new TilePtr *[MAX_LENGTH];
    for (int i = 0; i < MAX_LENGTH; ++i)
        board[i] = new TilePtr[MAX_WIDTH];
    TilePtr ***boardPtr = &board;
    //changes ALL values to nullptr
    for (int i = 0; i < MAX_WIDTH; i++)
    {
        for (int j = 0; j < MAX_LENGTH; j++)
        {
            board[i][j] = nullptr;
        }
    }
    //make the whole board nullptr
    GameEngine *gameEnginePtr = new GameEngine(players[0], players[1], boardPtr, bagPtr);
    gameEnginePtr->newGame();
    delete gameEnginePtr;
    //loop through to delete?
    delete[] board;
}

void loadGame()
{
    //TO DO

    std::string fileName = "";
    std::cout << "Enter the filename you wish to load"
              << "\n"
              << ">";

    std::cin >> fileName;

    IOCode *fileLoader = new IOCode();
    //4 std::cout << fileName << std::endl;
    SaveGame *loadGame = fileLoader->readFile(fileName + ".txt");

    std::string name = loadGame->playerName1;
    std::cout << name << std::endl;
    //TODO Build the hands of players (LinkedList)
    LinkedList *hand1 = new LinkedList();
    LinkedList *hand2 = new LinkedList();

    //begin parsing Hand string
    std::string hand1String = loadGame->playerHand1;
    std::string hand2String = loadGame->playerHand2;
    std::cout << hand1String << std::endl;
    std::string delimiter = ", ";
    std::cout << "what the fuck" << std::endl;
    size_t pos = 0;
    std::string token;
    std::string colour;
    std::string shape;

    while ((pos = hand1String.find(delimiter)) != std::string::npos)
    {
        std::cout << "legoo" << std::endl;
        token = hand1String.substr(0, pos);
        std::cout << token << std::endl;
        colour = token[0];
        shape = token[1];
        int shapeInt = stoi(shape);
        const char *colourChar = colour.c_str();
        Tile *newTile = new Tile(*colourChar, shapeInt);
       
        hand1->insertFront(newTile);
        hand1String.erase(0, pos + delimiter.length());
        
    }
    std::cout << "what the fuck 2" << std::endl;

    while ((pos = hand2String.find(delimiter)) != std::string::npos)
    {
        std::cout << "Loooping" << std::endl;

        token = hand2String.substr(0, pos);
        colour = token[0];
        shape = token[1];
        int shapeInt = stoi(shape);
        const char *colourChar = colour.c_str();
        Tile *newTile = new Tile(*colourChar, shapeInt);
        std::cout << newTile->toString() << std::endl;
         

        hand2->insertFront(newTile);
        hand2String.erase(0, pos + delimiter.length());
        delete newTile;
    }

    

    std::cout << "what the fuck 3" << std::endl;

    //TODO Build the bag (LinkedList)
    LinkedList *bagLList = new LinkedList();
    //TODO Fill Board (2D Array)
    Player **players = new Player *[NUMBER_OF_PLAYERS];
    Player *player1 = new Player(loadGame->playerName1, hand1);
    Player *player2 = new Player(loadGame->playerName2, hand2);
    std::cout << "what the fuck 4" << std::endl;

    players[1] = player1;
    players[2] = player2;
    Bag *bagPtr = new Bag();

    bagPtr->bagLinkedList = *bagLList;
    std::cout << "what the fuck 5" << std::endl;

    TilePtr **board = new TilePtr *[MAX_LENGTH];
    for (int i = 0; i < MAX_LENGTH; ++i)
        board[i] = new TilePtr[MAX_WIDTH];
    TilePtr ***boardPtr = &board;
    //changes ALL values to nullptr
    for (int i = 0; i < MAX_WIDTH; i++)
    {
        for (int j = 0; j < MAX_LENGTH; j++)
        {
            board[i][j] = nullptr;
        }
    }

    GameEngine *gameEnginePtr = new GameEngine(player1, player2, boardPtr, bagPtr);
    std::cout << "what the fuck 6" << std::endl;

    gameEnginePtr->newGame();
    std::cout << "what the fuck 7" << std::endl;

    delete gameEnginePtr;
    delete[] board;
}

void showInfo()
{
    //TO DO
    std::cout << "--------------------------------\n";
    std::cout << "Name: Duy Nguyen\n";
    std::cout << "Student ID: s3429599\n";
    std::cout << "Email: s3429599@student.rmit.edu.au\n\n";
    std::cout << "Name: Justin Cooper\n";
    std::cout << "Student ID: s3720189\n";
    std::cout << "Email: s3720189@student.rmit.edu.au\n\n";
    std::cout << "Name: Koby Gean\n";
    std::cout << "Student ID: s3681583\n";
    std::cout << "Email: s3681583@student.rmit.edu.au\n\n";
    std::cout << "Name: Jack Kelly\n";
    std::cout << "Student ID: s3707748\n";
    std::cout << "Email: s3707748@student.rmit.edu.au\n\n";
    std::cout << "--------------------------------\n\n";
}

void quit()
{
    //TO DO
    std::cout << "smell ya later"
              << "\n";
    exitProgram = true;
}
