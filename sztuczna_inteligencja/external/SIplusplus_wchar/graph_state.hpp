#ifndef GRAPH_STATE_HPP
#define GRAPH_STATE_HPP

#include <vector>
#include <memory>
#include <string>
#include <iostream>

class graph_state
{
public:
	graph_state();

	virtual ~graph_state();

	/**
	 * @brief Method creates copy of the current object.
	 * @return Unique pointer to the copied object.
	 */
	virtual std::unique_ptr<graph_state> clone() const = 0;

	/**
	 * @brief Method calculates hash of the current object.
	 * @return Number representing hash.
	 */
	virtual std::size_t hash_code() const = 0;

	/**
	 * @brief get_successors
	 * @return vector of unique pointers containing children states.
	 */
	virtual std::vector<std::unique_ptr<graph_state>> get_successors() const = 0;

	/**
	 * @brief is_solution
	 * @return true if current state is a terminal node, false otherwise.
	 */
	virtual bool is_solution() const = 0;

	/**
	 * @brief Method creates string representation of the current state.
	 * @return string containing character representation.
	 */
    virtual std::wstring to_string() const = 0;

    bool operator== (const graph_state &s) const;

	/**
	 * @brief get_f
	 * @return sum of true distance from initial node and estimated distance to
	 * terminal node.
	 */
	double get_f() const;

	/**
	 * @brief get_g
	 * @return true distance from initial node.
	 */
	double get_g() const;

	/**
	 * @brief get_h
	 * @return estimated distance to terminal node; must be non-negative.
	 */
	double get_h() const;

	/**
	 * @brief Method updates f, g and h of the current state.
	 * @param new_g Actual distance from inital node to current state.
	 */
	void update_score(double new_g);

	/**
	 * @brief get_parent
	 * @return Pointer to the parent or nullptr if it is initial node.
	 */
	const graph_state* get_parent() const;

	/**
	 * @brief set_parent
	 * @param parent Pointer to the parent.
	 */
	void set_parent(const graph_state *parent);

protected:
	/**
	 * @brief Method computes estimated distance to terminal node. Returned
	 * value must be non-negative.
	 * @return estimated distance to terminal node.
	 */
	virtual double get_heuristic_grade() const;

	/**
	 * @brief Method compares state with the other state.
	 * @param s state to compare with.
	 * @return true when current state is the same as state s, false otherwise.
	 */
	virtual bool is_equal(const graph_state &s) const = 0;

private:
	const graph_state *parent;
	double fscore, gscore, hscore;
};

namespace std
{
    template<>
    struct hash<graph_state*>
    {
        size_t operator()(const graph_state* s) const
        {
            return s->hash_code();
        }
    };

	template<>
	struct equal_to<graph_state*>
	{
		bool operator()(const graph_state* a, const graph_state* b) const
        {
            return *a == *b;
		}
	};

	template<>
	struct equal_to<std::unique_ptr<graph_state>>
	{
		bool operator()(const std::unique_ptr<graph_state> &a,
						const std::unique_ptr<graph_state> &b) const
		{
			return a && b && *a == *b;
		}
	};

    wostream& operator << (wostream& out, const graph_state &s);
}

#endif
