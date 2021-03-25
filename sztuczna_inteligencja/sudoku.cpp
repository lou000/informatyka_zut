#include "sudoku.h"

Sudoku::Sudoku(uint8_t n, int *board)
{
    this->board = board;
    this->n = n;
    this->gridSize = n*n*n*n;
}

Sudoku::Sudoku(uint8_t n, const char *str)
{
    this->n = n;
    this->gridSize = n*n*n*n;
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

std::unique_ptr<graph_state> Sudoku::clone() const
{
    int* board = new int[gridSize];
    memcpy(board, this->board, sizeof(int)*gridSize);
    return std::make_unique<Sudoku>(gridSize, board);
}

// From what I could gather from this unreadable mess of a codebase, this hash function is only here for unordered_map
size_t Sudoku::hash_code() const
{
    size_t hash = 0;
    for(int i=0; i<gridSize; i++)
    {
        // This hash function is shamelessly stolen from boost::hash_combine
        // https://www.boost.org/doc/libs/1_35_0/doc/html/boost/hash_combine_id241013.html
        hash ^= board[i] + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    return hash;
}

std::vector<std::unique_ptr<graph_state> > Sudoku::get_successors() const
{
    return std::vector<std::unique_ptr<graph_state>>();
}

//This right here expects the board to always be in valid state
bool Sudoku::is_solution() const
{
    for(int i=0; i<gridSize; i++)
        if(board[i] == 0) return false;
    return true;
}

std::wstring Sudoku::to_string() const
{
    std::wstringstream stream;
    int nn = n*n;

    //Top of the table
    stream<<L"╔";
    for(int i=1; i<=nn; i++)
    {
        if(i == nn)    //if end of the row
            stream<<L"═══╗";
        else
        {
            if(i % n == 0) //if end of the cell
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

        if(i % (nn) == 0)  //if end of the row
            stream<<L"║\n";

        if(i%(nn) == 0 && i<(gridSize)-nn+1) // stuff between rows but not at the end
        {
            if(i % (gridSize) != 0)        // if end of the cell vertical
                for(int j=1; j<=nn; j++)
                {
                    if(j == 1)          //if start of the row
                        stream<<L"╟───";
                    else if(j % n == 1) //if end of the cell horizontal
                        stream<<L"╫───";
                    else
                        stream<<L"┼───";
                }
            else
                for(int j=1; j<=nn; j++)
                {
                    if(j == 1)          //if start of the row
                        stream<<L"╠═══";
                    else if(j % n == 1) //if end of the cell horizontal
                        stream<<L"╬═══";
                    else
                        stream<<L"╪═══";
                }
            stream<<L"╢\n";
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
            if(i % n == 0) //if end of the cell
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
    return 0;
}

bool Sudoku::is_equal(const graph_state &s) const
{
    return hash_code() == s.hash_code();
}
