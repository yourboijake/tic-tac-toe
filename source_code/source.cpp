
//Jacob Dunning
//Tic Tac Toe CS2 Project
//Helpful source: https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-3-tic-tac-toe-ai-finding-optimal-move/

#include <iostream>
#include "Board.h"
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h> 
#include <Wincon.h>
#include <fstream>
using namespace std;

struct Move{
    int score;
    int index_best;
    Move(){
        score = 0;
        index_best = 0;
    }
};

int moveScore(Board b, int score_count, bool isAI, int depth){
    int score = b.evalPosition(b.getMinimaxTurn());
    //base cases: win, loss, cat game
    if(depth>10000)
        return 0;
    else if(score==1)
        return score;
    else if(score==-1)
        return score;
    else if(score==0)
        return score;
    //recursive cases: if isAI, make AI move, if !isAI, make human move
    else if(isAI){
        for(int i=0;i<9;i++){
            if(b.isLegal(i)){
                b.changeSqr(i+1,b.getMinimaxTurn());
                depth++;
                score_count += moveScore(b, score_count, !isAI, depth);
                b.changeSqr(i+1,i+'1');
                b.displayBoard();
            }
        }
        return score_count;
    }
    else{
        for(int i=0;i<9;i++){
            if(b.isLegal(i)){
                b.changeSqr(i+1,b.getNotMinimaxTurn());
                depth++;
                score_count += moveScore(b, score_count, !isAI, depth);
                b.changeSqr(i+1,i+'1');
                b.displayBoard();
            }
        }
        return score_count;
    }
}

Move findBestMove(Board b){
    Move m1;
    m1.score = -1000;
    for(int i=0;i<9;i++){
        if(b.isLegal(i)){
            b.changeSqr(i+1,b.getMinimaxTurn());
            int tempscore = moveScore(b, 0, false, 0);
            if(tempscore>m1.score){
                m1.score = tempscore;
                m1.index_best = i;
            }
            b.changeSqr(i+1,i+'1');
        }
    }
    return m1;
}

int main(){
    Board b, b2;
    char player;
    cout << "do you want to be X's or O's? Type 'X' or 'O':  ";
    cin >> player;
    
    if(player=='X') {
        b.setAI('O');
        b2.setAI('O');
    }
    else {
        b.setAI('X');
        b2.setAI('X');
    }

    /*b2.changeSqr(1,'X');
    b2.changeSqr(2,'X');
    b2.changeSqr(3,'O');
    b2.changeSqr(4,'O');
    b2.changeSqr(5,'O');
    b2.changeSqr(7,'X');
    b2.changeSqr(8,'X');*/
    b2.changeSqr(1,'X');
    b2.changeSqr(5,'O');
    b2.changeSqr(7,'X');
    b2.displayBoard();
    Move best = findBestMove(b2);
    cout << endl << "The best move in this position for O is " << best.index_best+1 << endl;

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
