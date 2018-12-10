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
#include <fstream>
using namespace std;

class Board{
private:
    char space[9]; //board values
    char turn; //identifies whose turn it is
    char minimaxturn; //AI's turn
    char depth; //number of moves made in the game
public:
    Board(){
        turn = 'X';
        depth = 0;
        for(int i=0;i<9;i++){
            space[i] = '1'+i;
        }
    }

//outputs the board
    void displayBoard(){
        cout << " " << space[0] << " | " << space[1] << " | " << space[2] << endl;
        cout << "------------" << endl;
        cout << " " << space[3] << " | " << space[4] << " | " << space[5] << endl;
        cout << "------------" << endl;
        cout << " " << space[6] << " | " << space[7] << " | " << space[8] << endl;
    }

//changes the square at index to char move
    void changeSqr(int index, char move){
        space[index-1] = move;
    }

//returns true if all the spaces are filled
    bool spacesFilled(){
        bool filled = true;
        for(int i=0;i<9;i++){
            if(space[i]=='1'+i)
                filled = false;
        }
        return filled;
    }

//tests if making a move at the index input would be legal or not
    bool isLegal(int index){
        if(getSpace(index)==index+'1')
            return true;
        else
            return false;
    }

//return true if someone has won the game
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
//returns a char for who won the game, returns C if its a cat game
    char getWinner(){
        if(gameWon())
            return turn;
        else if(spacesFilled())
            return 'C';
    } 
    void incrementDepth(){depth++;}
    int getDepth(){return depth;}
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

int minimax(Board b, bool isAI, int depth){
    int score = b.evalPosition(b.getMinimaxTurn());
    if(depth > 1000){
        return 0;
        depth = 0;
    }
    else if(score==10)
        return score;
    else if(score==-10)
        return score;
    else if(b.spacesFilled())
        return 0;
    else if(isAI){
        int best = -1000;
        for(int i=0;i<9;i++){
            if(b.isLegal(i)){
                b.changeSqr(i+1, b.getMinimaxTurn());
                depth++;
                best = max(best, minimax(b, !isAI, depth));
                b.changeSqr(i+1,i+'1');
            }
        }
        return best;
    }
    else{
        int best = 1000;
        for(int i=0;i<9;i++){
            if(b.isLegal(i)){
                b.changeSqr(i+1, b.getNotMinimaxTurn());
                depth++;
                best = min(best, minimax(b, !isAI, depth));
                b.changeSqr(i+1,i+'1');
            }
        }
        return best;
    }
}

int findBestMove(Board b){
    int bestVal = -1000;
    int index_best;
    int depth = 0;
    for(int i=0;i<9;i++){
        if(b.isLegal(i)){
            b.changeSqr(i+1,b.getMinimaxTurn());
            int moveVal = minimax(b, false, depth);
            b.changeSqr(i+1,i+'1');
            if(moveVal>bestVal){
                bestVal = moveVal;
                index_best = i;
            }
        }
    }
    return index_best;
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
    int AImove;

    Board b2;
    b2.changeSqr(1,'X');
    b.switchPlayer();
    b2.changeSqr(4,'O');
    b.switchPlayer();
    b2.changeSqr(7,'X');
    b.switchPlayer();
    b2.displayBoard();
    int best_move = findBestMove(b2)+1;
    cout << endl << "The best move in this position is " << best_move;
    /*do{
        b.displayBoard();
        if(b.getTurn()==player){
            while(!legit_move){
                    cout << endl << "Enter a move: ";
                    cin >> move;
                if(b.getSpace(move)==move)
                    cout << "space already taken. ";
                else
                    legit_move=true;
            }
            b.changeSqr(move, b.getTurn());
        }
        legit_move=false;
        Sleep(100);
        system("cls");
        b.displayBoard();

        if(b.getTurn()!=player){
            if(b.getDepth()>1){
                AImove = findBestMove(b)+1;
                b.changeSqr(AImove, b.getMinimaxTurn());
            }
            else if(b.getDepth()==0||b.getSpace(4)!='5'){ //if first move or if opponent plays in the center, play corner
                b.changeSqr(1,b.getMinimaxTurn());
            }
            else if(b.getSpace(0)!='0'||b.getSpace(2)!='2'||b.getSpace(6)!='6'||b.getSpace(8)!='8'){ //if corner, play center
                b.changeSqr(5, b.getMinimaxTurn());
            }
            else{
                b.changeSqr(5, b.getMinimaxTurn()); //else play center
            }
        }
        b.incrementDepth();
        b.switchPlayer();
        Sleep(100);
        system("cls");
    }while(!b.gameWon()&&!b.spacesFilled());
    
    b.displayBoard();
    cout << endl;

    if(b.getWinner()=='C')
        cout << "Cat game!";
    else
        cout << "The winner is " << b.getTurn() << endl;*/
    
    ofstream fout;
    fout.open("final_result.txt");
    fout << " " << b.getSpace(0) << " | " << b.getSpace(1) << " | " << b.getSpace(2) << endl;
    fout << "------------" << endl;
    fout << " " << b.getSpace(3) << " | " << b.getSpace(4) << " | " << b.getSpace(5) << endl;
    fout << "------------" << endl;
    fout << " " << b.getSpace(6) << " | " << b.getSpace(7) << " | " << b.getSpace(8) << endl;
    if(b.getWinner()=='C')
        fout << "Cat game!";
    else
        fout << "The winner is " << b.getTurn() << endl;

    return 0;
}
