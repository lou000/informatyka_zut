#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <vector>
#include <memory>
#include <string>
#include <optional>

template<typename Move>
class game_state
{
public:
	game_state() = default;

	virtual ~game_state() = default;

	/**
	 * @brief Method creates copy of the current object.
	 * @return Unique pointer to the copied object.
	 */
	virtual std::unique_ptr<game_state> clone() const = 0;

	/**
	 * @brief Method generates possible moves of current state.
	 * @return Vector of valid moves.
	 */
	virtual std::vector<Move> generate_moves() const = 0;

	/**
	 * @brief Method creates new state corresponding to the made move.
	 * @param move - move to make.
	 * @return New state after move or nullptr if move was invalid.
	 */
	virtual std::unique_ptr<game_state> make_move(const Move &move) const = 0;

	/**
	 * @brief Method calculates hash of the current object.
	 * @return Number representing hash.
	 */
	virtual size_t hash_code() const = 0;

	/**
	 * @brief Method creates string representation of the current state.
	 * @return string containing character representation.
	 */
	virtual std::string to_string() const = 0;

	/**
	 * @brief Method computes score of the current state. Positive value
	 * represents advantage of the first player, while negative value represents
	 * advantage of the second player.
	 * @return Value of the score.
	 */
	virtual double get_h() const = 0;

	/**
	 * @brief Method returns information if current state is won, lost or drawn.
	 * @param val Optional parameter containing score (+inf when the first
	 * player won, -inf when the second player won, 0 when there is draw).
	 * @return true for terminal state, false otherwise.
	 */
	virtual std::optional<double> is_terminal() const = 0;

	bool operator== (const game_state &s) const
	{
		return is_equal(s);
	}

protected:
	/**
	 * @brief Method compares state with the other state.
	 * @param s state to compare with.
	 * @return true when current state is the same as state s, false otherwise.
	 */
	virtual bool is_equal(const game_state &s) const = 0;
};

namespace std
{
	template<typename Move>
	struct hash<game_state<Move>*>
	{
		size_t operator()(const game_state<Move>* s) const
		{
			return s->hash_code();
		}
	};

	template<typename Move>
	struct equal_to<game_state<Move>*>
	{
		bool operator()(const game_state<Move>* a,
						const game_state<Move>* b) const
		{
			return *a == *b;
		}
	};

	template<typename Move>
	struct equal_to<std::unique_ptr<game_state<Move>>>
	{
		bool operator()(const std::unique_ptr<game_state<Move>> &a,
						const std::unique_ptr<game_state<Move>> &b) const
		{
			return a && b && *a == *b;
		}
	};

	template<typename Move>
    wostream& operator << (wostream& out, const game_state<Move>& s)
	{
		return (out << s.to_string());
	}
}

#endif
