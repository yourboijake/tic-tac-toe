
#ifndef _BOARD_H_
#define _BOARD_H_


#include <iostream>
using namespace std;

class Board{
private:
    char space[9]; //board values
    char turn; //identifies whose turn it is
    char minimaxturn; //AI's turn
    char depth; //number of moves made in the game
public:
    Board();

//outputs the board
    void displayBoard();

//changes the square at index to char move
    void changeSqr(int index, char move);

//returns true if all the spaces are filled
    bool spacesFilled();

//tests if making a move at the index input would be legal or not
    bool isLegal(int index);

//return true if someone has won the game
    bool gameWon();

//evaluates if a position is won or not, and returns the score of the position
    int evalPosition(char AIchar);

//returns a char for who won the game, returns C if its a cat game
    char getWinner();

    void incrementDepth();
    int getDepth();
    char getSpace(int index);
    char getTurn();
    void setAI(char c);
    char getMinimaxTurn();
    char getNotMinimaxTurn();
    void switchPlayer();
};

#endif
