#pragma once
#define PUZZLE_DEBUG

#ifdef PUZZLE_DEBUG
#define PPK_ASSERT_ENABLED 1
#else
#define PPK_ASSERT_ENABLED 0
#endif

#include <unordered_set>
#include <vector>
#include "l_assert.h"
#include "graph_search.hpp"
#include "utils.h"
#define NUMBER_OF_SHUFFLES 200


typedef uint8_t uint8;
typedef uint16_t uint16 ;

class SlidePuzzle : graph_state
{
public:
    enum Heuristic{
        Manhattan, WrongPlace
    };
    SlidePuzzle(uint16 n, Heuristic heuristic);
    SlidePuzzle(uint16 n, uint16* grid, Heuristic heuristic);

private:
    uint16 emptyIndex = 0;

    mutable uint16* grid = nullptr;
    const uint16 n = 0;
    const uint16 size = 0;
    const Heuristic heuristic;

    std::vector<uint16> getMovableCells(uint16 emptyIndx);
    void swapWithEmpty(uint16 indx);
    void createGrid();
    void shuffleGrid();


public:
    static bool compare(const graph_state& a, const graph_state& b);

    bool is_solution() const override;
    std::unique_ptr<graph_state> clone() const override;
    std::size_t hash_code() const override;
    std::wstring to_string() const override;
    std::vector<std::unique_ptr<graph_state> > get_successors() const override;

protected:
    double get_heuristic_grade() const override;
    bool is_equal(const graph_state &s) const override;
};

