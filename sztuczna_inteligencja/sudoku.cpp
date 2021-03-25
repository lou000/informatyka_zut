#include "sudoku.h"

Sudoku::Sudoku(const uint8_t n, int *board)
    :board(board), n(n), nn(n*n), gridSize(n*n*n*n)
{
    assert(n != 0);
}

Sudoku::Sudoku(const uint8_t n, const char *str)
    :n(n), nn(n*n), gridSize(n*n*n*n)
{
    assert(n != 0);
    this->board = new int[gridSize];

    int i = 0;
    //Well better make sure
    assert(std::strlen(str) == gridSize);
    while(str[i] != '\0')
    {
        this->board[i] = str[i] - '0';
        i++;
    }
}


bool Sudoku::validateCell(uint8_t cellNr) const
{
    assert(cellNr - 1 < gridSize && cellNr - 1 >= 0);
    int number = board[cellNr-1];
    if(number == 0) return true;
    int x = (cellNr-1) % nn;
    int y = (cellNr-1) / nn;

    //Check row
    for(int i=0; i<nn; i++)
    {
        if(i == x) continue;
        int cv = board[y*nn + i];
        if(cv == number)
            return false;
    }

    //Check column
    for(int i=0; i<nn; i++)
    {
        if(i == y) continue;
        int cv = board[i*nn + x];
        if(cv == number)
            return false;
    }

    //Check square
    int startX = x-((x%n) - 1)-1;
    int startY = y-((y%n) - 1)-1;
    //    std::wcout<<"X: "<<x<<"            "<<"Y: "<<y<<"\n";
    //    std::wcout<<"startX: "<<startX<<"   "<<"startY: "<<startY<<"\n";
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            if(startX + j == x && startY + i == y) continue;
            int cv = board[(startY+i)*nn + startX+j];
            if(cv == number)
                return false;
        }

    return true;
}

std::unique_ptr<graph_state> Sudoku::clone() const
{
    int* board = new int[gridSize];
    memcpy(board, this->board, sizeof(int)*gridSize);
    return std::make_unique<Sudoku>(gridSize, board);
}

// From what I could gather from this unreadable mess of a codebase, this hash function is only here for unordered_map.
size_t Sudoku::hash_code() const
{
    size_t hash = 0;
    for(int i=0; i<gridSize; i++)
    {
        // This hash function is shamelessly stolen from boost::hash_combine.
        // https://www.boost.org/doc/libs/1_35_0/doc/html/boost/hash_combine_id241013.html
        hash ^= board[i] + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    return hash;
}

std::vector<std::unique_ptr<graph_state> > Sudoku::get_successors() const
{
    return std::vector<std::unique_ptr<graph_state>>();
}

//This right here expects the board to always be in valid state.
bool Sudoku::is_solution() const
{
    return get_heuristic_grade() == 0;
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
    for(int i=1; i<=gridSize; i++)
    {

        //Convert number to display . when 0 and letter if above 9
        int num = board[i-1];
        wchar_t disp;
        if(num > 9)
            disp = num - 10 + 'A';
        else if(num == 0)
            disp = '.';
        else
            disp = num + '0';

        //Display body of the table
        if(i % n == 1)      //if start of the row
            stream<<L"║ "<<disp<<" ";
        else
            stream<<L"│ "<<disp<<" ";

        if(i % nn == 0)  //if end of the row
            stream<<L"║\n";

        if(i % nn == 0 && i<gridSize-nn+1) // stuff between rows but not at the end
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
    double empty = 0;

    // Validate board
    // We shouldnt have to do it on every cell, we can just validate initial state of the grid
    // and validate new addition when spawning children.
    // This is awfuly inefficiant
    for(int i=1; i<=gridSize; i++)
        validateCell(i);


    //Calculate "heuristic"
    for(int i=0; i<gridSize; i++)
        if(board[i]==0) empty++;
    return empty;
}

bool Sudoku::is_equal(const graph_state &s) const
{
    const Sudoku* st = dynamic_cast<const Sudoku*>(&s);
    assert(gridSize == st->gridSize);
    return memcmp(board, st->board, gridSize * sizeof (int));
}
