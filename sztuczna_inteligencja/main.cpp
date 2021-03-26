#include <iostream>
#include <sstream>
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include "SIplusplus/graph_search.hpp"
#include "sudoku.h"
#include "puzzles.h"

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);



    for(int i=0; i<5; i++)
    {
        std::wcout<<"\n\n"<<"BOARD 9x9:\n";
        Sudoku sud = Sudoku(3, puzzle9x9[i]);
        std::wcout<<"String: "<<puzzle9x9[i]<<"\n";
        std::wcout<<"Hash  : "<<sud.hash_code()<<"\n\n";
        std::wcout<<sud.to_string();

        std::wcout<<"\n\n"<<"SOLUTION:\n";


        auto searcher = informative_searcher(sud, &Sudoku::compare, 10);
        for(size_t i = 0; i<searcher.get_number_of_solutions(); i++)
        {
            const Sudoku* solution = dynamic_cast<const Sudoku*>(searcher.get_solution(0));
            std::wcout<<solution->to_string();
        }
        std::wcout<<searcher.get_stats();
        std::wcout<<"\n\n"<<"==============================================================================================================\n";
    }

    for(int i=0; i<2; i++)
    {
        std::wcout<<"\n\n"<<"BOARD 16x16:\n";
        Sudoku sud = Sudoku(4, puzzle16x16[i]);
        std::wcout<<"String: "<<puzzle16x16[i]<<"\n";
        std::wcout<<"Hash  : "<<sud.hash_code()<<"\n\n";
        std::wcout<<sud.to_string();

        std::wcout<<"\n\n"<<"SOLUTION:\n";


        auto searcher = informative_searcher(sud, &Sudoku::compare, 1);
        for(size_t i = 0; i<searcher.get_number_of_solutions(); i++)
        {
            const Sudoku* solution = dynamic_cast<const Sudoku*>(searcher.get_solution(0));
            std::wcout<<solution->to_string();
        }
        std::wcout<<searcher.get_stats();
        std::wcout<<"\n\n"<<"==============================================================================================================\n";
    }

    return 0;
}


