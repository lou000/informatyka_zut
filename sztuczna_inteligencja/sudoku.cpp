#include "sudoku.h"

Sudoku::Sudoku(const uint16 n, Cell* grid, std::unordered_set<uint16> emptyIndexes,
               Heuristic heuristic)
    :grid(grid), emptyIndexes(emptyIndexes), n(n), nn(n*n), size(n*n*n*n), heuristic(heuristic)
{
    assert(n != 0);
    assert(grid != nullptr);
#ifdef SUDOKU_DEBUG
    for(int i=0; i<size; i++)
        assert(validateCell(i));
#endif
}

Sudoku::Sudoku(const uint16 n, const char *str, Heuristic heuristic)
    :n(n), nn(n*n), size(n*n*n*n), heuristic(heuristic)
{
    //Well better make sure
    assert(n != 0 && n<8);  //cant have more than
    assert(std::strlen(str) == size);

    grid = new Cell[size];

    int i = 0;
    while(str[i] != '\0')
    {
        const auto sChar = str[i];
        if(n == 4)  // in 16x16 '0' is used in solution so move everything by 1
        {
            if(sChar == '.')
                grid[i].value = 0;
            else
            {
                if(sChar<='9')
                    grid[i].value = (sChar - '0') + 1;
                else
                    grid[i].value = (sChar - 'A') + 11;
            }
        }
        else // 9x9 and smaller
        {
            grid[i].value = sChar - '0';
        }
        i++;
    }
    setupGridInfo();
}

Sudoku::~Sudoku()
{
    delete [] grid;
}

void Sudoku::setupGridInfo()
{
    for(int i=0; i<size; i++)
    {
        if(grid[i].value == 0)
        {
            setConstraintsAndSolutions(i);
            emptyIndexes.insert(i);
        }
        assert(validateCell(i));
    }
}

void Sudoku::setCell(uint16 cell, uint16 value) const
{
    assert(value>0 && value<= nn);
    grid[cell].value = value;
    updateConstraintsAndSolutions(cell);
    emptyIndexes.erase(cell);
}

// This is a foreach type loop that iterates over column row and box coresponding
// to cells constraints.
// Takes a lambda that returns a bool, loop terminates when lambda evaluates to false.
// It doesnt bring joy.
void Sudoku::forEachCRB(uint16 cellNr, std::function<bool(Cell*)> function) const
{
    assert(cellNr < size && cellNr >= 0);
    int x = (cellNr) % nn;
    int y = (cellNr) / nn;

    // Loop row
    for(int i=0; i<nn; i++)
    {
        if(i == x) continue;
        Cell* cc = &grid[y*nn + i];
        if(!function(cc)) return;
    }

    // Loop column
    for(int i=0; i<nn; i++)
    {
        if(i == y) continue;
        Cell* cc = &grid[i*nn + x];
        if(!function(cc)) return;
    }

    // Loop square
    int startX = x-((x%n) - 1)-1;
    int startY = y-((y%n) - 1)-1;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            if(startX + j == x && startY + i == y) continue;
            Cell* cc = &grid[(startY+i)*nn + startX+j];
            if(!function(cc)) return;
        }
}

// Check if all constraints are met (unique in column, row and box)
bool Sudoku::validateCell(uint16 cellNr) const
{
    int cc = grid[cellNr].constraintCount;
    if(cc > nn-1)
        return false;
    int number = grid[cellNr].value;
    if(number == 0) return true;
    bool valid = true;
    forEachCRB(cellNr, [&](Cell* v){
        if(v->value == number)
        {
            valid = false;
            return false;
        }
        return true;
    });
    return valid;
}

// Find number of other cells constraining this one and get available solutions
// this function is called only in constructor
void Sudoku::setConstraintsAndSolutions(uint16 cellNr) const
{
    // Start with all solutions and remove ones we encounter.
    Cell* cell = &grid[cellNr];
    for(int i=1; i<=nn; i++)
        cell->solutions[i-1] = i;

    forEachCRB(cellNr, [&](Cell* v){
        if(v->value!=0)
        {
            cell->solutions[v->value-1] = 0;
        }
        return true;
    });
    for(int i=0; i<nn; i++)
        if(cell->solutions[i] == 0)
            cell->constraintCount++;

}

// After each time we set a cell, we have to update every cell in corresponding row,
// column and box. (if this is new constraint, remove solution and ++ constraint count)
void Sudoku::updateConstraintsAndSolutions(uint16 cellNr) const
{
    Cell* cell = &grid[cellNr];

    forEachCRB(cellNr, [&](Cell* v){
        if(v->value == 0)
        {
            if(v->solutions[cell->value-1]!=0)
                v->constraintCount++;
            v->solutions[cell->value-1] = 0;
        }
        return true;
    });
}

bool Sudoku::compare(const graph_state &a, const graph_state &b)
{
    return a.get_h()<b.get_h();
}

std::unique_ptr<graph_state> Sudoku::clone() const
{
    Cell* newGrid = new Cell[size];
    memcpy(newGrid, grid, sizeof(Cell)*size);
    return std::make_unique<Sudoku>(n, newGrid, emptyIndexes, heuristic);
}

size_t Sudoku::hash_code() const
{
    size_t hash = 0;
    for(int i=0; i<size; i++)
    {
        // This hash function is shamelessly stolen from boost::hash_combine.
        // https://www.boost.org/doc/libs/1_35_0/doc/html/boost/hash_combine_id241013.html
        hash ^= grid[i].value + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    return hash;
}

std::vector<std::unique_ptr<graph_state> > Sudoku::get_successors() const
{
    // We didnt find any empty cells
    if(emptyIndexes.size() == 0)
        return std::vector<std::unique_ptr<graph_state>>();

    int maxConstraints = -1;
    int maxIndex = -1;
    for(auto index : emptyIndexes)
    {
        int cnt = grid[index].constraintCount;
        if(cnt>maxConstraints)
        {
            maxIndex = index;
            maxConstraints = cnt;
        }
    }
    // Create successor for every number that creates valid state in this cell
    auto maxCell = grid[maxIndex];
    std::vector<std::unique_ptr<graph_state>> successors;
    for(int i=0; i<nn; i++)
    {
        uint16 sol = maxCell.solutions[i];
        if(sol)
        {
            Cell* newGrid = new Cell[size];
            memcpy(newGrid, grid, size * sizeof(Cell));
            auto child = std::make_unique<Sudoku>(n, newGrid, emptyIndexes, heuristic);
            child->setCell(maxIndex, sol);
            child->update_score(0);
//            std::wcout<<child->to_string()<<"\n";
            successors.push_back(std::move(child));
        }
    }
    return successors;
}

//This right here expects the board to always be in valid state.
bool Sudoku::is_solution() const
{
    return emptyIndexes.size() == 0;
}

//In an effort to make this look pretty I've made it extremely complicated. Also requires wstream.
std::wstring Sudoku::to_string() const
{
    std::wstringstream stream;

    //Top of the table
    stream<<L"╔";
    for(int i=1; i<=nn; i++)
    {
        if(i == nn)    //if end of the row
            stream<<L"═══╗";
        else
        {
            if(i % n == 0) //if end of the square
                stream<<L"═══╦";
            else
                stream<<L"═══╤";
        }
    }
    stream<<"\n";

    //Body of the table
    for(int i=1; i<=size; i++)
    {

        //Convert number to display . when 0 and letter if above 9
        int num = grid[i-1].value;
        wchar_t disp;
        if(num > 9)
            disp = num - 10 + 'A';
        else if(num == 0)
            disp = '.';
        else
            disp = num + '0';

        if(n == 4) //if 16x16 drop down by 1
        {
            if(disp == 'A')
                disp = '9';
            else if(disp != '.')
                disp = disp-1;
        }

        //Display body of the table
        if(i % n == 1)      //if start of the row
            stream<<L"║ "<<disp<<" ";
        else
            stream<<L"│ "<<disp<<" ";

        if(i % nn == 0)  //if end of the row
            stream<<L"║\n";

        if(i % nn == 0 && i<size-nn+1) // stuff between rows but not at the end
        {
            if(i % (nn*n) != 0)        // if end of the square vertical
            {
                for(int j=1; j<=nn; j++)
                {
                    if(j == 1)          //if start of the row
                        stream<<L"╟───";
                    else if(j % n == 1) //if end of the square horizontal
                        stream<<L"╫───";
                    else
                        stream<<L"┼───";
                }
                stream<<L"╢\n";
            }
            else
            {
                for(int j=1; j<=nn; j++)
                {
                    if(j == 1)          //if start of the row
                        stream<<L"╠═══";
                    else if(j % n == 1) //if end of the square horizontal
                        stream<<L"╬═══";
                    else
                        stream<<L"╪═══";
                }
                stream<<L"╣\n";
            }
        }
    }

    //Bottom of the table
    stream<<L"╚";
    for(int i=1; i<=nn; i++)
    {
        if(i == nn)    //if end of the row
            stream<<L"═══╝";
        else
        {
            if(i % n == 0) //if end of the square
                stream<<L"═══╩";
            else
                stream<<L"═══╧";
        }
    }
    stream<<"\n";
    return stream.str();
}

double Sudoku::get_heuristic_grade() const
{
    //Calculate "heuristic"
    switch (heuristic) {
    case NumberOfUnknowns:
        return  emptyIndexes.size();
    case SumOfRemainingSolutions:
    {
        int sum = 0;
        for(auto indx : emptyIndexes)
        {
            sum += nn - grid[indx].constraintCount;
        }
        return sum;
    }
    }
}

bool Sudoku::is_equal(const graph_state &s) const
{
    const Sudoku* st = dynamic_cast<const Sudoku*>(&s);
    assert(size == st->size);
    int eq = memcmp(grid, st->grid, size * sizeof (Cell)); //wow who knew memcmp = 0 if equal
    return eq == 0;
}

