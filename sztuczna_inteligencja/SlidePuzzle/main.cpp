#include <iostream>
#include <sstream>
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include "slidepuzzle.h"
#include <chrono>


int main()
{
    //The source files have to be formated in UNIX style to print correctly
    setlocale(LC_ALL, "");
    _setmode(_fileno(stdout), _O_U16TEXT);

//    auto seed =std::chrono::steady_clock::now().time_since_epoch().count();
//    SlidePuzzle puzzle = SlidePuzzle(6, seed, SlidePuzzle::Manhattan);
//    std::wcout<<puzzle.to_string();

//    auto searcher = informative_searcher(puzzle, &SlidePuzzle::compare);
//    for(size_t i = 0; i<searcher.get_number_of_solutions(); i++)
//    {
//        const SlidePuzzle* solution = dynamic_cast<const SlidePuzzle*>(searcher.get_solution(0));
//        std::wcout<<solution->to_string();
//    }
//    std::wcout<<searcher.get_stats();

    std::vector<SlidePuzzle*> puzzlesMan;
    std::vector<SlidePuzzle*> puzzlesMis;
    int count = 1000;
    for(int i=0; i<count; i++)
    {
        auto seed =std::chrono::steady_clock::now().time_since_epoch().count();
        puzzlesMan.push_back(new SlidePuzzle(3, seed, SlidePuzzle::Manhattan));
        puzzlesMis.push_back(new SlidePuzzle(3, seed, SlidePuzzle::MisplacedTiles));
    }
    auto timeStart = std::chrono::steady_clock::now();
    for(auto puzzle : puzzlesMan)
        auto searcher = informative_searcher(*puzzle, &SlidePuzzle::compare);
    auto timeEnd = std::chrono::steady_clock::now();
    std::wcout<<(double)std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count()/count/1000<<"ms\n";

    timeStart = std::chrono::steady_clock::now();
    for(auto puzzle : puzzlesMis)
        auto searcher = informative_searcher(*puzzle, &SlidePuzzle::compare);
    timeEnd = std::chrono::steady_clock::now();
    std::wcout<<(double)std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count()/count/1000<<"ms\n";

    return 0;
}
