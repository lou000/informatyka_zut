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

    Connect4 game = Connect4(5, 5, 1);
    auto mv = game.createMove(1);
    game.addUserMove(mv);
    mv = game.createMove(1);
    game.addUserMove(mv);
    mv = game.createMove(2);
    game.addUserMove(mv);
    mv = game.createMove(3);
    game.addUserMove(mv);

    std::wcout<<game.to_string();

    return 0;
}


