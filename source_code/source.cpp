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
        return 0-(depth/2);
    else if(score==1)
        return score-(depth/2);
    else if(score==-1)
        return score;
    else if(b.spacesFilled())
        return score-(depth/2);
    //recursive cases: if isAI, make AI move, if !isAI, make human move
    else if(isAI){
        for(int i=0;i<9;i++){
            if(b.isLegal(i)){
                b.changeSqr(i+1,b.getMinimaxTurn());
                depth++;
                score_count += moveScore(b, score_count, !isAI, depth);
                b.changeSqr(i+1,i+'1');
                depth--;
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
                depth--;
            }
        }
        return score_count;
    }
}

Move findBestMove(Board b){
    Move m1;
    m1.score = -1000;
    //searches through all possible moves, returning moveScore for each, then choosing the largest
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
    bool humans_turn;
    Board b, b2;
    char player;
    cout << "do you want to be X's or O's? Type 'X' or 'O':  ";
    cin >> player;
    
    if(player=='X') {
        b.setAI('O');
        humans_turn = true;
    }
    else{
        b.setAI('X');
        humans_turn = false;
    }
    bool legit_move = false;
    int move;
    Move AImove;


    do{
        b.displayBoard();
        if(humans_turn){
            while(!legit_move){
                    cout << endl << "Enter a move: ";
                    cin >> move;
                if(!b.isLegal(move-1))
                    cout << "space already taken. ";
                else
                    legit_move=true;
            }
            b.changeSqr(move, b.getNotMinimaxTurn());
            legit_move=false;
        }
        
        if(!humans_turn){
            AImove = findBestMove(b);
            b.changeSqr(AImove.index_best, b.getMinimaxTurn());
        }
        Sleep(500);
        system("cls");
        if(humans_turn)
            humans_turn=false;
        else
            humans_turn=true;
    }while(!b.gameWon()&&!b.spacesFilled());
    
    b.displayBoard();
    cout << endl;
    int score = b.evalPosition(player);

    if(score == 0)
        cout << "Cat game!";
    else if(score == -1)
        cout << "The winner is me!" << endl;
    else
        cout << "Congratulations, you beat me :(" << endl;
    
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
