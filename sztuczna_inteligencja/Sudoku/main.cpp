#include <iostream>
#include <sstream>
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include "sudoku.h"
#include "puzzles.h"
#include "graph_search.hpp"

void testPuzzles(uint8 count, uint8 solutions, uint8 size, const char** array,
                 Sudoku::Heuristic h = Sudoku::NumberOfUnknowns)
{
    for(int i=0; i<count; i++)
    {
        Sudoku sud = Sudoku(size, array[i], h);
        std::wcout<<"\n\n"<<"SUDOKU "<<size*size<<"x"<<size*size<<":\n";
        std::wcout<<"String: "<<array[i]<<"\n";
        std::wcout<<"Hash  : "<<sud.hash_code()<<"\n\n";
        std::wcout<<sud.to_string();


        std::wcout<<"\n\n"<<"SOLUTION ("<<(h == Sudoku::NumberOfUnknowns ? "NumberOfUnknowns" : "SumOfRemainingSolutions")<<"):\n";
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

void testHeuristics(uint8 count, uint8 solutions, uint8 size, const char** array)
{
    for(int i=0; i<count; i++)
    {
        std::wcout<<size*size<<"x"<<size*size<<"("<<i<<")\n";
        std::wcout<<"NUMBER OF UNKNOWNS:\n";
        Sudoku sud = Sudoku(size, array[i], Sudoku::NumberOfUnknowns);
        auto searcher = informative_searcher(sud, &Sudoku::compare, solutions);
        std::wcout<<searcher.get_stats()<<"\n";

        std::wcout<<"SUM OF REMAINING\n";
        Sudoku sud2 = Sudoku(size, array[i], Sudoku::SumOfRemainingSolutions);
        auto searcher2 = informative_searcher(sud2, &Sudoku::compare, solutions);
        std::wcout<<searcher2.get_stats()<<"\n";

        std::wcout<<"==============================================================================================================\n\n";
    }
}
int main()
{
    //The source files have to be formated in UNIX style to print correctly
    setlocale(LC_ALL, "");
    _setmode(_fileno(stdout), _O_U16TEXT);

    testPuzzles(4, 1, 2, puzzle4x4);
    testPuzzles(8, 1, 3, puzzle9x9);
    testPuzzles(4, 1, 4, puzzle16x16);

//    testHeuristics(4, 1, 2, puzzle4x4);
//    testHeuristics(1, 1, 3, puzzle9x9);
//    testHeuristics(4, 1, 4, puzzle16x16);

//    int repeats = 50;
//    for(int i=1; i<=repeats; i++)
//    {
//        testPuzzles(2, 2, 4, puzzle16x16);
//        std::wcout<<"Progress: "<<(double)i/repeats*100<<"%\n";
//    }
    return 0;
}


