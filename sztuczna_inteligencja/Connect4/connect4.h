#include "game_searcher.hpp"
#include "utils.h"
#include <math.h>
#include <optional>

typedef uint32_t uint;
typedef uint8_t uint8;

struct Move{
    uint8 x, y;
    double h_grade;
};

class Connect4 : public game_state<Move>
{
public:
    Connect4(uint8 width, uint8 height, uint difficulty);
    Connect4(const Connect4 *parent, Move move);
    Connect4(const Connect4* parent);
    virtual std::unique_ptr<game_state<Move>> clone() const;
    virtual std::vector<Move> generate_moves() const;
    virtual std::unique_ptr<game_state<Move>> make_move(const Move &move) const;
    virtual size_t hash_code() const;
    virtual std::wstring to_string() const;
    virtual double get_h() const;
    virtual std::optional<double> is_terminal() const;
    Move createMove(uint8 column, bool user = true) const;
    void addUserMove(Move move);

protected:
    virtual bool is_equal(const game_state<Move> &s) const;

private:
    double hGrade = 0;

    mutable char* grid = nullptr;
    const uint8 width, height;
    const uint size;
    const uint difficulty;
};
