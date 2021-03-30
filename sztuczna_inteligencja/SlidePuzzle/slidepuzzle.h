#pragma once
//#define PUZZLE_DEBUG
#define SHUFFLES_FACTOR 500

#ifdef PUZZLE_DEBUG
#define PPK_ASSERT_ENABLED 1
#else
#define PPK_ASSERT_ENABLED 0
#endif

#include <unordered_set>
#include <cstring>  //for memcmp
#include <vector>
#include "graph_search.hpp"
#include "utils.h"
#include "math.h"


typedef uint8_t uint8;
typedef uint16_t uint16 ;

class SlidePuzzle : public graph_state
{
public:
    enum Heuristic{
        Manhattan, MisplacedTiles
    };
    SlidePuzzle(uint16 n, const char* str, Heuristic heuristic);
    SlidePuzzle(uint16 n, int seed, Heuristic heuristic);
    SlidePuzzle(const SlidePuzzle* parent, uint16 indxToSwap);
    SlidePuzzle(const SlidePuzzle *parent);
    ~SlidePuzzle();

private:
    int seed;
    double hGrade = 0;
    uint16 emptyIndex = 0;
    uint16 gScore = 0;

    mutable uint16* grid = nullptr;
    const uint16 n = 0;
    const uint16 size = 0;
    const Heuristic heuristic;

    std::vector<uint16> getMovableCells(uint16 emptyIndx) const;
    double getHGradeOfTile(uint16 indx) const;
    void swapWithEmpty(uint16 indx);
    void createGrid();


public:
    void shuffleGrid();
    static bool compare(const graph_state &a, const graph_state &b);

    bool is_solution() const override;
    std::unique_ptr<graph_state> clone() const override;
    std::size_t hash_code() const override;
    std::wstring to_string() const override;
    std::vector<std::unique_ptr<graph_state> > get_successors() const override;

protected:
    double get_heuristic_grade() const override;
    bool is_equal(const graph_state &s) const override;
};

