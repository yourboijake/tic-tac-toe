//Jacob Dunning
//Tic Tac Toe CS2 Project

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

class Board{
private:
    char space[9];
    char turn;
public:
    Board(){
        turn = 'X';
        for(int i=0;i<9;i++){
            space[i] = '0'+i+1;
        }
    }
    void changeSqr(int index, char move){
        space[index-1] = move;
    }
    bool gameDone(){
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
    void displayBoard(){
        cout << " " << space[0] << " | " << space[1] << " | " << space[2] << endl;
        cout << "------------" << endl;
        cout << " " << space[3] << " | " << space[4] << " | " << space[5] << endl;
        cout << "------------" << endl;
        cout << " " << space[6] << " | " << space[7] << " | " << space[8] << endl;
    }
    
    char getSpace(int index){
        return space[index];
    }
    
    void AImove(){
        //figure out how to get the computer to make the best move
    }
};

void switchPlayer(char &x){
    if(x=='X')
        x = 'Y';
    else
        x = 'X';
}

int main(){
    Board b;
    char player;
    cout << "do you want to be X's or O's? Type X or O ";
    cin >> player;
    cout << endl;
    char currentplayer='X';
    int move;
    bool legit_move=false;
    
    do{
        b.displayBoard();
        while(legit_move!=true){
            //if(player==currentplayer){
                cout << endl << "Enter a move: ";
                cin >> move;
            //}
            if(b.getSpace(move)==move)
                cout << "space already taken. ";
            else
                legit_move=true;
        }
        b.changeSqr(move, currentplayer);
        switchPlayer(currentplayer);
        legit_move=false;
    }while(b.gameDone()==false);
}
