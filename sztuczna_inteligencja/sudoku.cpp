#include "sudoku.h"

Sudoku::Sudoku(const uint16 n, uint16 *board, uint16 blankCount)
    :grid(board), n(n), nn(n*n), size(n*n*n*n), blankCount(blankCount)
{
    assert(n != 0);
#ifdef SUDOKU_DEBUG
    for(int i=0; i<size; i++)
        assert(validateCell(i));
#endif
}

uint16 Sudoku::at(uint16 cell) const
{
    return grid[cell];
}

void Sudoku::setCell(uint16 cell, uint16 value) const
{
    assert(value>0 && value<= nn);
    grid[cell] = value;
}

Sudoku::Sudoku(const uint16 n, const char *str)
    :n(n), nn(n*n), size(n*n*n*n)
{
    assert(n != 0);
    this->grid = new uint16[size];

    int i = 0;
    //Well better make sure
    assert(std::strlen(str) == size);
    while(str[i] != '\0')
    {
        const auto sChar = str[i];
        if(n == 4)  // in 16x16 '0' is used in solution so move everything by 1
        {
            if(sChar == '.')
            {
                this->grid[i] = 0;
                blankCount++;
            }
            else
            {
                if(sChar<'9')
                    this->grid[i] = (sChar - '0') + 1;
                else if(sChar == '9')
                    this->grid[i] = 10;
                else
                    this->grid[i] = (sChar - 'A') + 11;
            }
        }
        else // 9x9 and smaller
        {
            this->grid[i] = sChar - '0';
            if(sChar == '0')
                blankCount++;
        }
        i++;
    }

    //Check if sudoku imported from string is valid
    for(int i=0; i<size; i++)
        assert(validateCell(i));

}

Sudoku::~Sudoku()
{
    delete [] grid;
}

// This is a foreach type loop that iterates over column row and box coresponding
// to cells constraints.
// Takes a lambda that returns a bool, loop terminates when lambda evaluates to false.
// It doesnt bring joy.
void Sudoku::forEachCRB(uint16 cellNr, std::function<bool(uint16)> function) const
{
    assert(cellNr < size && cellNr >= 0);
    int x = (cellNr) % nn;
    int y = (cellNr) / nn;

    //Check row
    for(int i=0; i<nn; i++)
    {
        if(i == x) continue;
        int cv = grid[y*nn + i];
        if(!function(cv)) return;
    }

    //Check column
    for(int i=0; i<nn; i++)
    {
        if(i == y) continue;
        int cv = grid[i*nn + x];
        if(!function(cv)) return;
    }

    //Check square
    int startX = x-((x%n) - 1)-1;
    int startY = y-((y%n) - 1)-1;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            if(startX + j == x && startY + i == y) continue;
            int cv = grid[(startY+i)*nn + startX+j];
            if(!function(cv)) return;
        }
}

// Check if all constraints are met (unique in column, row and box)
bool Sudoku::validateCell(uint16 cellNr) const
{
    int number = grid[cellNr];
    if(number == 0) return true;
    bool valid = true;
    forEachCRB(cellNr, [&](uint16 v){
        if(v == number)
        {
            valid = false;
            return false;
        }
        return true;
    });
    return valid;
}

// Find number of other cells constraining this one
uint16 Sudoku::getConstraintCount(uint16 cellNr) const
{
    std::unordered_set<uint16> constraints;
    forEachCRB(cellNr, [&](uint16 v){
        if(v!=0)
            constraints.emplace(v);
        return true;
    });
    return constraints.size();
}

// Find numbers that satisfy constraints
std::unordered_set<uint16>  Sudoku::findPossibleSolutions(uint16 cellNr) const
{
    std::unordered_set<uint16> solutions;
    for(int i=1; i<=nn; i++)
        solutions.emplace(i);
    forEachCRB(cellNr, [&](uint16 v){
        if(v!=0)
            solutions.erase(v);
        return true;
    });
    return solutions;

}

bool Sudoku::compare(const graph_state &a, const graph_state &b)
{
    return a.get_h()<b.get_h();
}

std::unique_ptr<graph_state> Sudoku::clone() const
{
    uint16* board = new uint16[size];
    memcpy(board, this->grid, sizeof(uint16)*size);
    return std::make_unique<Sudoku>(n, board, blankCount);
}

size_t Sudoku::hash_code() const
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

std::vector<std::unique_ptr<graph_state> > Sudoku::get_successors() const
{
    //Find the field with highest number of constraints and spawn successors from there.
    int maxConstr = -1;
    int maxCell = -1;

    for(int i=0; i<size; i++)
    {
        if(grid[i] == 0)
        {
            int constr = getConstraintCount(i);
            if(constr > maxConstr)
            {
                maxConstr = constr;
                maxCell = i;
            }
        }
    }
    // We didnt find any empty cells
    if(maxCell == -1)
        return std::vector<std::unique_ptr<graph_state>>();

    // Create successor for every number that creates valid state in this cell
    auto solutions = findPossibleSolutions(maxCell);
    std::vector<std::unique_ptr<graph_state>> successors;
    for(auto sol : solutions)
    {
        uint16* newGrid = new uint16[size];
        memcpy(newGrid, grid, size * sizeof(uint16));

        auto child = std::make_unique<Sudoku>(n, newGrid, blankCount-1);
        child->setCell(maxCell, sol);
        successors.push_back(std::move(child));
    }
    return successors;
}

//This right here expects the board to always be in valid state.
bool Sudoku::is_solution() const
{
    return blankCount == 0;
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
        int num = grid[i-1];
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
    // Validate board
    // C# script tells us to do this here...
    // We shouldnt have to do it on every cell, we can just validate initial state of the grid
    // and validate new addition when spawning children.

//    for(int i=1; i<=size; i++)
//        validateCell(i);

    // Validation has been moved to constructor and to findPossibleSolutions.


    //Calculate "heuristic"
    return blankCount;
}

bool Sudoku::is_equal(const graph_state &s) const
{
    const Sudoku* st = dynamic_cast<const Sudoku*>(&s);
    assert(size == st->size);
    int eq = memcmp(grid, st->grid, size * sizeof (uint16)); //wow who knew memcmp = 0 if equal
    return eq == 0;
}

