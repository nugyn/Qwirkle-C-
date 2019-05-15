#include <string>
#include <iostream>
#include "LinkedList.h"


using namespace std;

class Player{

public:

    Player(string name, string studentID, string email, LinkedList* hand);
    ~Player();

private:

    LinkedList *hand;
    string name;
    string studentID;
    string email;

};