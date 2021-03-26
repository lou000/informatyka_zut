#pragma once
#include "SIplusplus/graph_state.hpp"
#include <iostream>
#include <sstream>
#include <assert.h>
#include <cstring>
#include <unordered_set>
#include <functional>
#define SUDOKU_DEBUG
#ifndef SUDOKU_DEBUG
#undef assert
#define assert(x)
#endif

typedef uint8_t uint8;

class Sudoku : public graph_state
{
public:
    Sudoku(uint8 n, uint8* board);
    Sudoku(uint8 n, const char* board);
    ~Sudoku();

    Sudoku(const Sudoku&) = delete;
    Sudoku& operator=(Sudoku const&) = delete;

    uint8 getSize(){return size;}

private:
    uint8* grid = nullptr;
    const uint8 n = 0;
    const uint8 nn = 0;
    const uint8 size = 0;
    void forEachCRB(uint8 cellNr, std::function<bool(uint8)> function) const;
#ifdef SUDOKU_DEBUG
    uint8 count = 0;
#endif

public:
    uint8 at(uint8 cell) const;
    void setCell(uint8 cell, uint8 value) const;
    bool validateCell(uint8 cellNr) const;
    uint8 getConstraintCount(uint8 cellNr) const;
    std::unordered_set<uint8> findPossibleSolutions(uint8 cellNr) const;
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

