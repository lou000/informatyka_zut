#include <iostream>
#include <sstream>
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include "SIplusplus_wchar/graph_search.hpp"
#include "sudoku.h"
#include "puzzles.h"

void testPuzzles(uint8 count, uint8 solutions, uint8 size, const char** array)
{
    for(int i=0; i<count; i++)
    {
        std::wcout<<"\n\n"<<"BOARD 9x9:\n";
        Sudoku sud = Sudoku(size, array[i]);
        std::wcout<<"String: "<<array[i]<<"\n";
        std::wcout<<"Hash  : "<<sud.hash_code()<<"\n\n";
        std::wcout<<sud.to_string();

        std::wcout<<"\n\n"<<"SOLUTION:\n";


        auto searcher = informative_searcher(sud, &Sudoku::compare, solutions);
        for(size_t i = 0; i<searcher.get_number_of_solutions(); i++)
        {
            const Sudoku* solution = dynamic_cast<const Sudoku*>(searcher.get_solution(0));
            std::wcout<<solution->to_string()<<"\n";
        }
        std::wcout<<searcher.get_stats();
        std::wcout<<"\n\n"<<"==============================================================================================================\n";
    }
}

int main()
{
    setlocale(LC_ALL, "");
    _setmode(_fileno(stdout), _O_U16TEXT);


    testPuzzles(2, 2, 2, puzzle4x4);
    testPuzzles(2, 2, 3, puzzle9x9);
    testPuzzles(2, 2, 4, puzzle16x16);


    return 0;
}


