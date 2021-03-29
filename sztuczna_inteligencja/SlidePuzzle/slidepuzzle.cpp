#include "slidepuzzle.h"

SlidePuzzle::SlidePuzzle(uint16 n, SlidePuzzle::Heuristic heuristic)
    :n(n), size(n*n), heuristic(heuristic)
{
    ASSERT(n!=0);
    createGrid();
    shuffleGrid();
}

SlidePuzzle::SlidePuzzle(uint16 n, uint16 *grid, SlidePuzzle::Heuristic heuristic)
    :n(n), size(n*n), heuristic(heuristic)
{

}

std::vector<uint16> SlidePuzzle::getMovableCells(uint16 emptyIndx)
{
    ASSERT(n!=0);
    std::vector<uint16> vec;
    int col = emptyIndx % n;
    int row = emptyIndx / n;
    if(col!=0)
        vec.push_back(emptyIndex - 1);
    if(row!=0)
        vec.push_back(emptyIndex - n);
    if(col!=n-1)
        vec.push_back(emptyIndex + 1);
    if(row!=n-1)
        vec.push_back(emptyIndex + n);
    ASSERT(vec.size()>=2);

    return vec;
}

void SlidePuzzle::swapWithEmpty(uint16 indx)
{
    auto& cell = grid[indx];
    auto& empty = grid[emptyIndex];
    ASSERT(empty == 0, "Empty index is not empty!\empty: grid[%d] = %d", emptyIndex, empty);
#ifdef PUZZLE_DEBUG
    int emptyRow = emptyIndex / n;
    int cellRow  = indx / n;
    int emptyCol = emptyIndex % n;
    int cellCol  = indx % n;

    ASSERT(emptyCol == cellCol || emptyRow == cellRow, "Cells must be on the same rows or columns!\n"
                                     "empty: %d (%d,%d),  cell: %d = (%d,%d)",
                                      emptyIndex, emptyCol, emptyRow, indx, cellCol, cellRow);
    if(emptyCol == cellCol)
        ASSERT(abs(emptyIndex-indx) == n);
    else if(emptyRow == cellRow)
        ASSERT(abs(emptyIndex-indx) == 1);
#endif
    std::swap(cell, empty);
    emptyIndex = indx;
}

void SlidePuzzle::createGrid()
{
    for(int i=1; i<size-1; i++)
        grid[i] = i;
    grid[size-1] = 0;
    emptyIndex = size-1;
}

void SlidePuzzle::shuffleGrid()
{
    for(int i=0; i<NUMBER_OF_SHUFFLES; i++)
    {
        auto cells = getMovableCells(emptyIndex);
        int
    }
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

