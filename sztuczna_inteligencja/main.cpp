#define SUDOKU_DEBUG
#include <iostream>
#include <sstream>
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include "sudoku.h"
#include "SIplusplus/graph_search.hpp"

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    const char* board = "010020300004005060070000008006900070000100002030048000500006040000800106008000000";

    Sudoku sud = Sudoku(3, board);
    std::wcout<<"Board string: "<<board<<"\n";
    std::wcout<<"Board hash  : "<<sud.hash_code()<<"\n\n";
    std::wcout<<sud.to_string();

    std::wcout<<"\n\n";


    auto searcher = informative_searcher(sud, &Sudoku::compare, 10);
    std::wcout<<searcher.get_stats();

    for(size_t i = 0; i<searcher.get_number_of_solutions(); i++)
    {
        const Sudoku* solution = dynamic_cast<const Sudoku*>(searcher.get_solution(0));
        std::wcout<<solution->to_string();
    }

    return 0;
}


