#pragma once
#include "SIplusplus/graph_state.hpp"
#include <iostream>
#include <sstream>
#include <assert.h>
#include <cstring>

class Sudoku : public graph_state
{
public:
    Sudoku(uint8_t n, int* board);
    Sudoku(uint8_t n, const char* board);

    Sudoku(const Sudoku&) = delete;
    Sudoku& operator=(Sudoku const&) = delete;

private:
    int* board = nullptr;
    uint8_t n = 0;
    uint8_t gridSize = 0;

public:
    virtual std::unique_ptr<graph_state> clone() const override;
    virtual size_t hash_code() const override;
    virtual std::vector<std::unique_ptr<graph_state>> get_successors() const override;
    virtual bool is_solution() const override;
    virtual std::wstring to_string() const override;

protected:
    virtual double get_heuristic_grade() const override;
    virtual bool is_equal(const graph_state &s) const override;
};

