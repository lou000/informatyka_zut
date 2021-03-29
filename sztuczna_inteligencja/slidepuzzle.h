#pragma once
#include "SIplusplus_wchar/graph_state.hpp"


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

    const uint16* grid = nullptr;
    const uint16 n = 0;
    const uint16 size = 0;
    const Heuristic heuristic;

    bool validateGrid();
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

