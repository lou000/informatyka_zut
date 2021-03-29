#include "slidepuzzle.h"

SlidePuzzle::SlidePuzzle(uint16 n, SlidePuzzle::Heuristic heuristic)
    :n(n), size(n*n), heuristic(heuristic)
{

}

SlidePuzzle::SlidePuzzle(uint16 n, uint16 *grid, SlidePuzzle::Heuristic heuristic)
    :n(n), size(n*n), heuristic(heuristic)
{

}

bool SlidePuzzle::swapCells(uint16 indx1, uint16 indx2)
{
    auto& cell1 = grid[indx1];
    auto& cell2 = grid[indx2];


}

void SlidePuzzle::createGrid()
{
    for(int i=1; i<size-1; i++)
        grid[i] = i;
    grid[size-1] = 0;
}

void SlidePuzzle::shuffleGrid()
{

}

bool SlidePuzzle::compare(const graph_state &a, const graph_state &b)
{

}

bool SlidePuzzle::is_solution() const
{

}

std::unique_ptr<graph_state> SlidePuzzle::clone() const
{

}

std::size_t SlidePuzzle::hash_code() const
{

}

std::wstring SlidePuzzle::to_string() const
{

}

std::vector<std::unique_ptr<graph_state> > SlidePuzzle::get_successors() const
{

}

double SlidePuzzle::get_heuristic_grade() const
{

}

bool SlidePuzzle::is_equal(const graph_state &s) const
{

}

