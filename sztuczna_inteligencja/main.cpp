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
        Sudoku sud = Sudoku(size, array[i]);
//        std::wcout<<"\n\n"<<"SUDOKU "<<size*size<<"x"<<size*size<<":\n";
//        std::wcout<<"String: "<<array[i]<<"\n";
//        std::wcout<<"Hash  : "<<sud.hash_code()<<"\n\n";
//        std::wcout<<sud.to_string();


//        std::wcout<<"\n\n"<<"SOLUTION:\n";
        auto searcher = informative_searcher(sud, &Sudoku::compare, solutions);
        for(size_t i = 0; i<searcher.get_number_of_solutions(); i++)
        {
            const Sudoku* solution = dynamic_cast<const Sudoku*>(searcher.get_solution(0));
//            std::wcout<<solution->to_string()<<"\n";
        }

//        std::wcout<<searcher.get_stats();
//        std::wcout<<"\n\n"<<"==============================================================================================================\n";
    }
}
int main()
{
    //The files have to be formated in UNIX style to print correctly
    setlocale(LC_ALL, "");
    _setmode(_fileno(stdout), _O_U16TEXT);

    PROFILE_BEGIN_SESSION("main", "prof.json");
//    testPuzzles(2, 2, 2, puzzle4x4);
//    testPuzzles(2, 2, 3, puzzle9x9);
//    testPuzzles(2, 2, 4, puzzle16x16);

    int repeats = 50;
    for(int i=1; i<=repeats; i++)
    {
        testPuzzles(2, 2, 4, puzzle16x16);
        std::wcout<<"Progress: "<<(double)i/repeats*100<<"%\n";
    }
    PROFILE_END_SESSION();
    return 0;
}


