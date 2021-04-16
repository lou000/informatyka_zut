#include <iostream>
#include <sstream>
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include "connect4.h"
int main()
{
    //The source files have to be formated in UNIX style to print correctly
    setlocale(LC_ALL, "");
    _setmode(_fileno(stdout), _O_U16TEXT);

    Connect4 c4 = Connect4(5, 5, 1);
    auto game = alpha_beta_searcher<Move, true>(1,true);

    game.do_search(c4);
    auto moves = game.get_scores();
    c4.commitMove(moves.front().first, false);

//    auto userMove = c4.createMove(1);
//    c4.commitMove(userMove, true);

//    game.do_search(c4);
//    moves = game.get_scores();
//    c4.commitMove(moves.front().first, false);

//    userMove = c4.createMove(0);
//    c4.commitMove(userMove, true);

//    game.do_search(c4);
//    moves = game.get_scores();
//    c4.commitMove(moves.front().first, false);

    std::wcout<<c4.to_string();

    return 0;
}


