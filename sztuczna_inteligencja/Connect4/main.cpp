#include <iostream>
#include <sstream>
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include "connect4.h"
#include <algorithm>
#include "utils.h"

Move pickRandomTopMove(std::vector<std::pair<Move, double>> moves) //input sorted
{
    double bestMove = moves.front().second;
    std::vector<std::pair<Move, double>> bestMoves;
    for(size_t i=0; i<moves.size(); i++)
    {
        auto move = moves[i];
        if(move.second>bestMove)
            bestMove = move.second;
    }
    std::wstringstream stream;
    stream<<"Computer moves: ";
    for(auto move:moves)
    {
        if(move.second>=bestMove*0.95f)
        {
            stream<<"!!("<<move.first.x<<","<<move.first.y<<") g:"<<move.second<<"!! ";
            bestMoves.push_back(move);
        }
        else
            stream<<"  ("<<move.first.x<<","<<move.first.y<<") g:"<<move.second<<"   ";
    }
    std::wcout<<stream.str()<<"\n";
    return bestMoves[rndInt(0, bestMoves.size())].first;
}

int main()
{
    //The source files have to be formated in UNIX style to print correctly
    setlocale(LC_ALL, "");
    _setmode(_fileno(stdout), _O_U16TEXT);

    Connect4 c4 = Connect4(5, 5);
    auto game = alpha_beta_searcher<Move, true>(3,true);

    bool playerTurn = true;
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
                c4.commitMove(move);
                playerTurn = false;
            }
        }
        else
        {
            std::wcout<<"-----COMPUTER-----\n";
            game.do_search(c4);
            auto moves = game.get_scores();
            c4.commitMove(pickRandomTopMove(moves));
            playerTurn = true;
        }
        std::wcout<<c4.to_string()<<"\n\n";
    }

    return 0;
}


