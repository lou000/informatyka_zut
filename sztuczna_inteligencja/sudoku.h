#pragma once
//#define SUDOKU_DEBUG
#include "SIplusplus/graph_state.hpp"
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

typedef uint16_t uint16;
typedef uint16_t uint16 ;

class Sudoku : public graph_state
{
public:
    Sudoku(uint16 n, uint16* board, uint16 count);
    Sudoku(uint16 n, const char* board);
    ~Sudoku();

    Sudoku(const Sudoku&) = delete;
    Sudoku& operator=(Sudoku const&) = delete;

    uint16 getSize(){return size;}

private:
    uint16* grid = nullptr;
    const uint16 n = 0;
    const uint16 nn = 0;
    const uint16 size = 0;
    uint16 blankCount = 0;
    void forEachCRB(uint16 cellNr, std::function<bool(uint16)> function) const;

public:
    uint16 at(uint16 cell) const;
    void setCell(uint16 cell, uint16 value) const;
    bool validateCell(uint16 cellNr) const;
    uint16 getConstraintCount(uint16 cellNr) const;
    std::unordered_set<uint16> findPossibleSolutions(uint16 cellNr) const;
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

