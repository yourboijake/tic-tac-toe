
#include "Board.h"

Board::Board(){
        turn = 'X';
        depth = 0;
        for(int i=0;i<9;i++){
            space[i] = '1'+i;
        }
    }
void Board::displayBoard(){
        cout << " " << space[0] << " | " << space[1] << " | " << space[2] << endl;
        cout << "------------" << endl;
        cout << " " << space[3] << " | " << space[4] << " | " << space[5] << endl;
        cout << "------------" << endl;
        cout << " " << space[6] << " | " << space[7] << " | " << space[8] << endl;
    }
void Board::changeSqr(int index, char move){
        space[index-1] = move;
    }

bool Board::spacesFilled(){
        bool filled = true;
        for(int i=0;i<9;i++){
            if(space[i]=='1'+i)
                filled = false;
        }
        return filled;
    }
bool Board::isLegal(int index){
        if(getSpace(index)==index+'1')
            return true;
        else
            return false;
    }
bool Board::gameWon(){
        if(space[0]==space[1]&&space[2]==space[1])
            return true;
        else if(space[3]==space[4]&&space[5]==space[4])
            return true;
        else if(space[6]==space[7]&&space[7]==space[8])
            return true;
        else if(space[0]==space[3]&&space[6]==space[3])
            return true;
        else if(space[1]==space[2]&&space[7]==space[4])
            return true;
        else if(space[2]==space[5]&&space[8]==space[5])
            return true;
        else if(space[0]==space[4]&&space[4]==space[8])
            return true;
        else if(space[2]==space[4]&&space[4]==space[6])
            return true;
        else
            return false;
    }
int Board::evalPosition(char AIchar){
        if(gameWon()&&turn==AIchar)
            return 10;
        else if(gameWon()&&turn!=AIchar)
            return -10;
        else
            return 0;
    }
char Board::getWinner(){
        if(gameWon())
            return turn;
        else if(spacesFilled())
            return 'C';
    } 
void Board::incrementDepth(){depth++;}
int Board::getDepth(){return depth;}
char Board::getSpace(int index){return space[index];}
char Board::getTurn(){return turn;}
void Board::setAI(char c){minimaxturn = c;}
char Board::getMinimaxTurn(){return minimaxturn;}
char Board::getNotMinimaxTurn(){
        if(minimaxturn=='X')
            return 'Y';
        else
            return 'X';
    }
void Board::switchPlayer(){
        if(turn=='X')
            turn = 'Y';
        else
            turn = 'X';
    }
