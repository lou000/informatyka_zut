#include "connect4.h"
#include <limits>
#include <iostream>
#include <sstream>

Connect4::Connect4(uint8 w, uint8 h)
    :width(w), height(h), size(w*h)
{
    grid = (char*)malloc(size*sizeof(char));
    for(uint i=0; i<size; i++)
        grid[i] = ' ';
}

Connect4::Connect4(const Connect4 *parent)
    :hGrade(parent->hGrade), userTurn(parent->userTurn), width(parent->width), height(parent->height),
     size(parent->size)
{
    grid = (char*)malloc(size*sizeof(char));
    memcpy(grid, parent->grid, sizeof(char)*size);
}

Connect4::Connect4(const Connect4 *parent, Move move)
    :hGrade(parent->hGrade), userTurn(parent->userTurn), width(parent->width), height(parent->height),
     size(parent->size)

{
    grid = (char*)malloc(size*sizeof(char));
    memcpy(grid, parent->grid, sizeof(char)*size);
    commitMove(move);
}

std::unique_ptr<game_state<Move>> Connect4::clone() const
{
    return std::make_unique<Connect4>(this);
}

std::vector<Move> Connect4::generate_moves() const
{
    //all possible moves
    std::vector<Move> moves;

    for(int i=0; i<width; i++)
    {
        auto move = createMove(i);
        if(move.h_grade >= 0)
            moves.push_back(move);
    }

    return moves;
}

std::unique_ptr<game_state<Move> > Connect4::make_move(const Move &move) const
{
    return std::make_unique<Connect4>(this, move);
}

size_t Connect4::hash_code() const
{
    size_t hash = 0;
    for(uint i=0; i<size; i++)
    {
        // This hash function is shamelessly stolen from boost::hash_combine.
        // https://www.boost.org/doc/libs/1_35_0/doc/html/boost/hash_combine_id241013.html
        hash ^= grid[i] + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    return hash;
}

std::wstring Connect4::to_string() const
{
    std::wstringstream stream;

    //Top of the table
    stream<<L"╔";
    for(int i=1; i<=width; i++)
    {
        if(i == width)    //if end of the row
            stream<<L"═══╗";
        else
            stream<<L"═══╤";
    }
    stream<<"hGrade = "<<hGrade<<"\n";

    for(uint i=0; i<height; i++)
    {
        for(uint j=0; j<width; j++)
        {
            if(j==0)
                stream<<L"║ "<<grid[i*height+j]<<" ";
            else
                stream<<L"│ "<<grid[i*height+j]<<" ";
        }
        stream<<L"║\n";
        if(i!=height-1)
        {
            for(uint j=0; j<width; j++)
            {
                if(j==0)
                    stream<<L"╟───";
                else
                    stream<<L"┼───";
            }
            stream<<L"╢\n";
        }
    }

    stream<<L"╚";
    for(int i=1; i<=width; i++)
    {
        if(i == width)    //if end of the row
            stream<<L"═══╝";
        else
            stream<<L"═══╧";
    }
    stream<<"\n";

    return stream.str();
}

double Connect4::get_h() const
{
    return hGrade;
}

std::optional<double> Connect4::is_terminal() const
{
    if(terminal == 0 || std::isinf(terminal))
        return terminal;
    return {};
}

Move Connect4::createMove(uint8 column) const
{
    Move move;
    move.x = column;
    //Check if the move is valid and where it lands
    int freeIndex = -1;
    for(uint i=0; i<height; i++)
    {
        int indx = i*width+column;
        if(grid[indx] == ' ')
            freeIndex = indx;
        else
            break;
    }

    if(freeIndex == -1)
    {
        move.h_grade = -1;
        return move;
    }


    //calculate heuristic
    char mark = userTurn ? 'O' : 'X';
    int row = freeIndex/width;
    move.y = row;

    //count repeating states in all directions except up
    uint left = 0;
    for(int i=column, j=-1; i>=0; i--, j--)
    {
        if(grid[freeIndex+j] == mark)
            left++;
        else
            break;
    }
    uint right = 0;
    for(int i=column, j= 1; i<width; i++, j++)
    {
        if(grid[freeIndex+j] == mark)
            right++;
        else
            break;
    }
    uint bottom = 0;
    for(int i=row, j= 1; i<height; i++, j++)
    {
        if(grid[freeIndex+width*j] == mark)
            bottom++;
        else
            break;
    }
    uint TR = 0;
    for(int i=row-1, j=column+1; i>=0 && j<width; i--, j++)
    {
        if(grid[i*width+j] == mark)
            TR++;
        else
            break;
    }
    uint TL = 0;
    for(int i=row-1, j=column-1; i>=0 && j>=0; i--, j--)
    {
        if(grid[i*width+j] == mark)
            TL++;
        else
            break;
    }
    uint BR = 0;
    for(int i=row+1, j=column+1; i<height && j<width; i++, j++)
    {
        if(grid[i*width+j] == mark)
            BR++;
        else
            break;
    }
    uint BL = 0;
    for(int i=row+1, j=column-1; i<height && j>=0; i++, j--)
    {
        if(grid[i*width+j] == mark)
            BL++;
        else
            break;
    }
    //god help me if there is a bug in something above


    //Calculate change of the hGrade
    double hGradeIncrement = 0;
    bool over = false;

    auto testPair=[&](std::pair<uint, uint> pair){
        if(pair.first && pair.second)
        {

            if(pair.first + pair.second >= 3)
            {
                // someone won
                move.h_grade = 999;
                over = true;
            }
            else
            {
                // There is only one case here both left and right are = 1
                // and after the move we connect them giving us 3 states in a row
                hGradeIncrement += 16;
            }
        }
        else if(pair.first || pair.second)
        {
            if(pair.first == 1 || pair.second == 1)
                hGradeIncrement += 4; // if there was one we now have two, add 4
            if(pair.first == 2 || pair.second == 2)
                hGradeIncrement += 12; // if there was two we now have three, add 12
            if(pair.first == 3 || pair.second == 3)
            {
                move.h_grade = 999;
                over = true;
            }
        }
    };
    testPair({left, right});
    if(over) return move;
    testPair({BL, TR});
    if(over) return move;
    testPair({BR, TL});
    if(over) return move;

    //never forget about bottom
    if(bottom == 1)
        hGradeIncrement += 4;
    if(bottom == 2)
        hGradeIncrement += 12;
    if(bottom == 3)
        hGradeIncrement = 999;

    move.h_grade = hGradeIncrement;

    return move;
}

void Connect4::commitMove(Move move)
{
    grid[move.y*width+move.x] = userTurn ? 'O' : 'X';
    if(move.h_grade == 999)
    {
        terminal = userTurn ? -std::numeric_limits<double>::infinity() : std::numeric_limits<double>::infinity();
    }
    hGrade += userTurn ? -move.h_grade : move.h_grade;
    userTurn = !userTurn;
}

bool Connect4::is_equal(const game_state<Move> &s) const
{
    const Connect4* st = dynamic_cast<const Connect4*>(&s);
    int eq = memcmp(grid, st->grid, size * sizeof (char));
    return eq == 0;
}
