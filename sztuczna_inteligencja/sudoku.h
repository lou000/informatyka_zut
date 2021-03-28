#pragma once
//#define SUDOKU_DEBUG

#include "SIplusplus_wchar/graph_state.hpp"
#include <iostream>
#include <sstream>
#include <assert.h>
#include <cstring>
#include <unordered_set>
#include <set>
#include <functional>

#ifndef SUDOKU_DEBUG
#undef assert
#define assert(x)
#endif


typedef uint8_t uint8;
typedef uint16_t uint16 ;

// This version is optimized by caching solutions and constraint count
// its about 10x faster at the cost of 2x the memory.
class Sudoku : public graph_state
{
    struct Cell{
        uint16 value = 0;
        uint16 constraintCount = 0;
        uint16 solutions[64] = {};   //this makes it so we can have max 64x64 grids
    };

public:
    Sudoku(uint16 n, const char* grid);
    Sudoku(const uint16 n, Cell* grid, std::unordered_set<uint16> emptyIndexes);
    ~Sudoku();

    Sudoku(const Sudoku&) = delete;
    Sudoku& operator=(Sudoku const&) = delete;

    uint16 getSize(){return size;}

private:
    mutable Cell* grid = nullptr;
    mutable std::unordered_set<uint16> emptyIndexes;

    const uint16 n = 0;
    const uint16 nn = 0;
    const uint16 size = 0;

    void setupGridInfo();
    bool validateCell(uint16 cellNr) const;
    void setCell(uint16 cell, uint16 value) const;
    void setConstraintsAndSolutions(uint16 cellNr) const;
    void updateConstraintsAndSolutions(uint16 cellNr) const;
    void forEachCRB(uint16 cellNr, std::function<bool(Cell*)> function) const;

public:
    static bool compare(const graph_state& a, const graph_state& b);

    virtual std::unique_ptr<graph_state> clone() const override;
    virtual size_t hash_code() const override;
    virtual std::vector<std::unique_ptr<graph_state>> get_successors() const override;
    virtual bool is_solution() const override;
    virtual std::wstring to_string() const override;

protected:
    virtual double get_heuristic_grade() const override;
    virtual bool is_equal(const graph_state &s) const override;
};

