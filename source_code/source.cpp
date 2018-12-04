
//Jacob Dunning
//Tic Tac Toe CS2 Project
//Helpful source: https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-3-tic-tac-toe-ai-finding-optimal-move/

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h> 
#include <Wincon.h>
using namespace std;

class Board{
private:
    char space[9];
    char turn;
    char minimaxturn;
public:
    Board(){
        turn = 'X';
        for(int i=0;i<9;i++){
            space[i] = '0'+i+1;
        }
    }
    void displayBoard(){
        cout << " " << space[0] << " | " << space[1] << " | " << space[2] << endl;
        cout << "------------" << endl;
        cout << " " << space[3] << " | " << space[4] << " | " << space[5] << endl;
        cout << "------------" << endl;
        cout << " " << space[6] << " | " << space[7] << " | " << space[8] << endl;
    }
    void changeSqr(int index, char move){
        space[index-1] = move;
    }
    bool spacesFilled(){
        bool filled = true;
        for(int i=0;i<9;i++){
            if(space[i]=='0'+i+1)
                filled = false;
        }
        return filled;
    }

    bool isLegal(int index){
        if(getSpace(index)==index+1)
            return false;
        else
            return true;
    }

    bool gameWon(){
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

//evaluates if a position is won or not, and returns the score of the position
    int evalPosition(char AIchar){
        if(gameWon()&&turn==AIchar)
            return 10;
        else if(gameWon()&&turn!=AIchar)
            return -10;
        else
            return 0;
    }
    char getWinner(){
        if(gameWon())
            return turn;
        else if(spacesFilled())
            return 'C';
    } 
    char getSpace(int index){return space[index];}
    char getTurn(){return turn;}
    void setAI(char c){minimaxturn = c;}
    char getMinimaxTurn(){return minimaxturn;}
    char getNotMinimaxTurn(){
        if(minimaxturn=='X')
            return 'Y';
        else
            return 'X';
    }
    void switchPlayer(){
        if(turn=='X')
            turn = 'Y';
        else
            turn = 'X';
    }
};

/*AI decision-making function. Reads the current board state, uses best possible moves for player and AI to return an int corresponding to the index of the
move int the space array that should be played*/
int minimax(Board b, int depth){
        int score = b.evalPosition(b.getTurn());
        if(score==10)
            return score;
        else if(score==-10)
            return score;
        else if(b.spacesFilled())
            return 0;
        else if(b.getTurn()==b.getMinimaxTurn()){
            int best = -1000;
            for(int i=0;i<9;i++){
                if(b.isLegal(i)){
                    b.changeSqr(i, b.getMinimaxTurn());
                    b.switchPlayer();
                    best = max(best, minimax(b, depth+1));
                }
            }
            return best;
        }
        else{
            int best = 1000;
            for(int i=0;i<9;i++){
                if(b.isLegal(i)){
                    b.changeSqr(i, b.getNotMinimaxTurn());
                    b.switchPlayer();
                    best = min(best, minimax(b, depth+1));
                }
            }
            return best;
        }
    }

int getBestMove(){
    
}

int main(){
    Board b;
    char player;
    cout << "do you want to be X's or O's? Type 'X' or 'O':  ";
    cin >> player;
    
    if(player=='X')
        b.setAI('O');
    else
        b.setAI('X');

    int move;
    bool legit_move=false;
    
    do{
        b.displayBoard();
        while(!legit_move){
                cout << endl << "Enter a move: ";
                cin >> move;
            if(b.getSpace(move)==move)
                cout << "space already taken. ";
            else
                legit_move=true;
        }
        b.changeSqr(move, b.getTurn());
        
        if(!b.gameWon()&&!b.spacesFilled())
            b.switchPlayer();
        
        legit_move=false;
        Sleep(100);
        system("cls");
    }while(!b.gameWon()&&!b.spacesFilled());
    
    b.displayBoard();
    cout << endl;

    if(b.getWinner()=='C')
        cout << "Cat game!";
    else
        cout << "The winner is " << b.getTurn() << endl;
    
    return 0;
}
