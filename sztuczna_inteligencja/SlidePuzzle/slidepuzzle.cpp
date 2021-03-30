#include "slidepuzzle.h"

SlidePuzzle::SlidePuzzle(uint16 n, const char *str, SlidePuzzle::Heuristic heuristic)
    :n(n), size(n*n), heuristic(heuristic)
{
    ASSERT(n!=0);
    ASSERT(strlen(str) == size);
    grid = new uint16[size];
    for(int i=0; i<size;i++)
    {
        grid[i] = str[i] - '0';
        if(grid[i]==0)
            emptyIndex = i;
        else
            hGrade+=getHGradeOfTile(i);
    }

}

SlidePuzzle::SlidePuzzle(uint16 n, int seed, SlidePuzzle::Heuristic heuristic)
    :seed(seed), n(n), size(n*n), heuristic(heuristic)
{
    ASSERT(n!=0);
    createGrid();
    shuffleGrid();
}

SlidePuzzle::SlidePuzzle(const SlidePuzzle *parent, uint16 indxToSwap)
    : hGrade(parent->hGrade), emptyIndex(parent->emptyIndex),
      n(parent->n), size(parent->size), heuristic(parent->heuristic)
{
    // Copy the parent exactly and then swap cells
    grid = new uint16[size];
    memcpy(grid, parent->grid, sizeof(uint16)*size);
    swapWithEmpty(indxToSwap);
    gScore++;
}

SlidePuzzle::SlidePuzzle(const SlidePuzzle *parent)
    : hGrade(parent->hGrade), emptyIndex(parent->emptyIndex),
      n(parent->n), size(parent->size), heuristic(parent->heuristic)
{
    // Copy the parent exactly
    grid = new uint16[size];
    memcpy(grid, parent->grid, sizeof(uint16)*size);
}

SlidePuzzle::~SlidePuzzle()
{
    delete [] grid;
}

std::vector<uint16> SlidePuzzle::getMovableCells(uint16 emptyIndx) const
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
    auto cell = grid + indx;
    auto empty = grid + emptyIndex;
    ASSERT(empty!=nullptr && cell!=nullptr);
    ASSERT(*empty == 0, "Empty index is not empty! empty: grid[%d] = %d", emptyIndex, *empty);
#ifdef PUZZLE_DEBUG
    int emptyRow = emptyIndex / n;
    int cellRow  = indx / n;
    int emptyCol = emptyIndex % n;
    int cellCol  = indx % n;

    ASSERT(emptyCol == cellCol || emptyRow == cellRow, "Cells must be on the same rows or columns!\n"
           "empty: %d (%d,%d),  cell: %d = (%d,%d)", emptyIndex, emptyCol, emptyRow, indx, cellCol, cellRow);
    if(emptyCol == cellCol)
        ASSERT(abs(emptyIndex-indx) == n);
    else if(emptyRow == cellRow)
        ASSERT(abs(emptyIndex-indx) == 1);
#endif
    // Subtract heuristic of old position from total then
    // move the cell, and add new heuristic
    hGrade -= getHGradeOfTile(indx);
    std::swap(*cell, *empty);
    hGrade += getHGradeOfTile(emptyIndex);
    emptyIndex = indx;
}

void SlidePuzzle::createGrid()
{
    grid = new uint16[size];
    for(int i=1; i<size; i++)
        grid[i-1] = i;
    grid[size-1] = 0; // intended place for '0' is at the end
    emptyIndex = size-1;
}

void SlidePuzzle::shuffleGrid()
{
    rndSeed(seed);
    for(int i=0; i<SHUFFLES_FACTOR*size; i++)
    {
        auto cells = getMovableCells(emptyIndex);
        int r = rndInt(0, cells.size());
        swapWithEmpty(cells[r]);
    }
}

bool SlidePuzzle::compare(const graph_state &a, const graph_state &b)
{
    return a.get_f()<b.get_f();
}

bool SlidePuzzle::is_solution() const
{
    return hGrade == 0;
}

std::unique_ptr<graph_state> SlidePuzzle::clone() const
{
    return std::make_unique<SlidePuzzle>(this);
}

std::size_t SlidePuzzle::hash_code() const
{
    size_t hash = 0;
    for(int i=0; i<size; i++)
    {
        // This hash function is shamelessly stolen from boost::hash_combine.
        // https://www.boost.org/doc/libs/1_35_0/doc/html/boost/hash_combine_id241013.html
        hash ^= grid[i] + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    return hash;
}

// This time supports any digit numbers
std::wstring SlidePuzzle::to_string() const
{
    std::wstringstream stream;

    int charsNeeded = std::log10(size)+1;

    //Top of the table
    stream<<L"╔";
    for(int i=1; i<=n; i++)
    {
        for(int i=1; i<=charsNeeded; i++) //add space for all the chars
            stream<<L"═";
        if(i == n)    //if end of the row
            stream<<L"══╗";
        else
            stream<<L"══╤";
    }
    stream<<"\n";

    //Body of the table
    for(int i=0; i<size; i++)
    {
        int num = grid[i];
        int charSize = num == 0 ? 2 : std::log10(num);
        int charDiff = charsNeeded - charSize;

        //Convert number to display
        std::wstring numStr = L" ";
        if(num == 0)
            for(int i=0; i<charsNeeded; i++)
                numStr += L"▓";
        else
            numStr += std::to_wstring(num);
        numStr+=L" ";

        int col = i % n;
        int row = i / n;

        if(col == 0)
            stream<<L"║";
        else
            stream<<L"│";

        int offset = charDiff/2;
        if((charDiff) % 2 == 1)
        {
            for(int j=0; j<offset; j++)
                stream<<" ";
            stream<<numStr;
            for(int j=0; j<offset; j++)
                stream<<" ";
        }
        else
        {
            for(int j=0; j<offset; j++)
                stream<<" ";
            stream<<numStr;
            for(int j=0; j<offset-1; j++)
                stream<<" ";
        }

        if(col == n-1)
            stream<<L"║\n";

        if(col == n-1 && row != n-1)
        {
            for(int j=1; j<=n; j++)
            {
                if(j == 1)   //if start of the row
                    stream<<L"╟";

                for(int k=1; k<=charsNeeded; k++) //add space for all the chars
                    stream<<L"─";
                if(j != n)
                    stream<<L"──┼";
            }
            stream<<L"──╢\n";
        }

    }


    //Bottom of the table
    stream<<L"╚";
    for(int i=1; i<=n; i++)
    {
        for(int i=1; i<=charsNeeded; i++) //add space for all the chars
            stream<<L"═";
        if(i == n)    //if end of the row
            stream<<L"══╝";
        else
            stream<<L"══╧";
    }
    stream<<"\n";

    return stream.str();
}

std::vector<std::unique_ptr<graph_state> > SlidePuzzle::get_successors() const
{
    auto vec = std::vector<std::unique_ptr<graph_state>>();

    auto possibleMoves = getMovableCells(emptyIndex);
    for(auto indx : possibleMoves)
    {
        auto child = std::make_unique<SlidePuzzle>(this, indx);
        child->update_score(gScore);
        vec.push_back(std::move(child));
    }
    return vec;
}

double SlidePuzzle::getHGradeOfTile(uint16 indx) const
{
    double h = 0;
    ASSERT(n!=0);
    switch (heuristic) {
    case Manhattan:
    {
        // Lets hope compiler takes care of this
        // it looks much more readable like that
        int col = indx % n;
        int row = indx / n;
        int val = grid[indx];
        int goal = val-1;
        int goalCol = goal % n;
        int goalRow = goal / n;
        if(val != 0)
            h = abs(col-goalCol) + abs(row-goalRow);
    }break;
    case MisplacedTiles:
    {
        if(grid[indx]!=indx+1 && grid[indx]!=0)
            h++;
    }break;
    }
    return h;
}

double SlidePuzzle::get_heuristic_grade() const
{
    return hGrade;
}

bool SlidePuzzle::is_equal(const graph_state &s) const
{
    const SlidePuzzle* st = dynamic_cast<const SlidePuzzle*>(&s);
    ASSERT(size == st->size);
    int eq = memcmp(grid, st->grid, size * sizeof (uint16));
    return eq == 0;
}

