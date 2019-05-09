
#include "LinkedList.h"

#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {
   LinkedList* list = new LinkedList();
   
   int number = 1;
   char character = 'r';
   Tile* newTile = new Tile(character, number);


      list -> insertTile(newTile);


   // list -> insertTile(newTile1)
   // list -> insertTile(newTile2)
   // list -> insertTile(newTile3)
   // list -> insertTile(newTile4)
   // list -> insertTile(newTile5)





   std::cout << "TODO: Implement Qwirkle!" << std::endl;

   return EXIT_SUCCESS;
}
