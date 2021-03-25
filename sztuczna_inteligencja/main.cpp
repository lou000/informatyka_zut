#include <iostream>
#include <sstream>
#include<locale.h>
#include <io.h>
#include <fcntl.h>
#include "sudoku.h"

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    const char* board = "010020300004005060070000008006900070000100002030048000500006040000800106008000000";

    Sudoku* sud = new Sudoku(3, board);
    std::wcout<<sud->to_string();

    delete sud;

    return 0;
}


