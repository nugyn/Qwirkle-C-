#include <iostream>
#include <fstream>


using namespace std;

struct SaveGame{
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

void writeFile(SaveGame s){

    ofstream outputFile;
    outputFile.open("savegame.txt");

    outputFile << s.playerName1 << endl;
    outputFile << s.playerScore1 << endl;
    outputFile << s.playerHand1  << endl;

    outputFile << s.playerName2 << endl;
    outputFile << s.playerScore2 << endl;
    outputFile << s.playerHand2 << endl;

    outputFile << s.board  << endl;
    outputFile << s.bag  << endl;
    outputFile << s.currentPlayer << endl;

    outputFile.close();
}

// SaveGame readFile(string fileName, SaveGame saveFile){

//     // string line;
//     // ifstream inFile;
//     // inFile.open("savegame.txt");
    
// }


int main(){
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