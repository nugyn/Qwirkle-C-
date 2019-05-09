
#include "LinkedList.h"

#include <iostream>

#define EXIT_SUCCESS    0


void mainMenu();
void printMenu();
void menuSelect(char input);
void newGame();
void loadGame();
void showInfo();
void quit();

bool exitProgram = false;

int main(void) {
  // LinkedList* list = new LinkedList();
  // delete list;
   
   std::cout << "Welcome to Qwirkle!" << std::endl << std::endl;
   while(!exitProgram){
       mainMenu();
   }

   return EXIT_SUCCESS;
}

void mainMenu(){

   printMenu();

   //use this bool to determine if the user has input a valid option
   bool validInput = false;
   char input = '0';
   //while the user hasnt input a valid option

   while(!validInput){
       std::cout << "> ";
       std::cin >> input;
       if(input == '1' || input == '2' || input == '3' || input == '4'){
           validInput = true;
           std::cout << std::endl;
           menuSelect(input);
       }
       else{
           std::cout << "Invalid Input" << std::endl;
       }
   }
}

void printMenu(){

    std::cout << "Menu\n";
    std::cout << "----\n";
    std::cout << "1. New Game\n";
    std::cout << "2. Load Game\n";
    std::cout << "3. Show student information\n";
    std::cout << "4. Quit\n";

}

void menuSelect(char input){
    if(input == '1'){
        newGame();
    }
    else if (input == '2'){
        loadGame();
    }
    else if (input == '3'){
        showInfo();
    }
    else{
        quit();
    }
}

void newGame(){
    //TO DO
    bool validName = false;
    std::string playerOne = "";
    std::string playerTwo = "";
    std::cout << "Starting A New Game\n\n";
    // PLAYER ONE NAME
    std::cout << "Enter a name for player 1: \n";
    while(!validName){
        std::cout << ">";
        std::cin >> playerOne;
        //DO CHECKS HERE IN AN IF STATEMENT
        validName = true;
    }
    validName = false;
    std::cout << "\n";
    // PLAYER TWO NAME
    std::cout << "Enter a name for player 2: \n";
    while(!validName){
        std::cout << ">";
        std::cin >> playerTwo;
        //DO CHECKS HERE IN AN IF STATEMENT
        validName = true;
    }
    std::cout << std::endl;
    std::cout << "Let's Play\n";
}

void loadGame(){
    //TO DO
    std::string fileName = "";
    std::cout << "Enter the filename you wish to load" << std::endl << ">";
    std::cin >> fileName;
}

void showInfo(){
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

void quit(){
    //TO DO
    std::cout << "smell ya later" << std::endl;
    exitProgram = true;
}
