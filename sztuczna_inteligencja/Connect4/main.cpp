#include <iostream>
#include <sstream>
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include "connect4.h"
#include <algorithm>
int main()
{
    //The source files have to be formated in UNIX style to print correctly
    setlocale(LC_ALL, "");
    _setmode(_fileno(stdout), _O_U16TEXT);

    Connect4 c4 = Connect4(5, 5, 1);
    auto game = alpha_beta_searcher<Move, true>(3,true);

//    char test[25] =
//    {
//        ' ', ' ', ' ', ' ', ' ',
//        'X', ' ', ' ', ' ', ' ',
//        'O', ' ', ' ', ' ', ' ',
//        'X', 'X', 'X', ' ', ' ',
//        'X', 'O', 'O', 'O', ' '
//    };
//    memcpy(c4.grid, test, 25*sizeof (char));

    bool playerTurn = false;
    while(c4.is_terminal() == std::nullopt)
    {
        if(playerTurn)
        {
            std::wcout<<"-----PLAYER-----\n";
            int playerChoice = -1;
            std::cin>>playerChoice;
            auto move = c4.createMove(playerChoice-1);
            if(move.h_grade >= 0)
            {
                c4.commitMove(move, true);
                playerTurn = false;
            }
        }
        else
        {
            std::wcout<<"-----COMPUTER-----\n";
            game.do_search(c4);
            auto moves = game.get_scores();
            std::sort(moves.begin(), moves.end(),[](std::pair<Move, double> a, std::pair<Move, double> b){
               return a.first.h_grade>b.first.h_grade;
            });
            for(auto move:moves)
            {
                //pick random move if the grade is similar
                move.first.print();
            }
            std::wcout<<"\n";
            c4.commitMove(moves.front().first, false);
            playerTurn = true;
        }
        std::wcout<<c4.to_string()<<"\n\n";
    }

    return 0;
}


