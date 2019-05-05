
#include "LinkedList.h"

#include <iostream>

#define EXIT_SUCCESS    0

void printMenu();

int main(void) {
  // LinkedList* list = new LinkedList();
  // delete list;

   std::cout << "Welcome to Qwirkle!" << std::endl << std::endl;
   printMenu();
   //use this bool to determine if the user has input a valid option
   bool validInput = false;
   char input = '0';
   //while the user hasnt input a valid option
   while(!validInput){
       std::cin >> input;
       if(input == '1' || input == '2' || input == '3' || input == '4'){
           validInput = true;
       }
   }

   return EXIT_SUCCESS;
}

void printMenu(){

    std::cout << "Menu" << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Show student information" << std::endl;
    std::cout << "4. Quit" << std::endl;

}


