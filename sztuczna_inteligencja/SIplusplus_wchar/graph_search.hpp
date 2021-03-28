#ifndef GRAPH_SEARCH_HPP
#define GRAPH_SEARCH_HPP

#include "graph_state.hpp"
#include "queue.hpp"
#include <vector>
#include <memory>
#include <unordered_set>
#include <functional>
#include <chrono>

bool depth_first_search(const graph_state &s,
                        std::function<bool(const std::unique_ptr<graph_state>&)> callback);

std::vector<std::unique_ptr<graph_state>> breadth_first_search(const graph_state &initial,
                                                               bool print_stats = true);

void breadth_first_search(const graph_state &initial,
                          std::function<bool(std::unique_ptr<graph_state>&)> callback,
                          bool print_stats = true);

std::wstring parse_time(int64_t ms);

class informative_searcher
{
public:
    /**
     * @brief Constructs object and performs actual search.
     * @param initial State from which searching is performed.
     * @param comp Comparator used by priority queue.
     * @param max_solutions Maximum number of solutions to find.
     */
    informative_searcher(const graph_state &initial,
                         std::function<bool(const graph_state&, const graph_state&)> comp,
                         size_t max_solutions = 1);

    /**
     * @brief get_number_of_solutions
     * @return number of found solutions
     */
    size_t get_number_of_solutions() const;

    /**
     * @brief get_solution_path
     * @param solution_num Number of solution (0 - first, 1 - second and so on).
     * Throws std::out_of_range if the number is invalid.
     * @return path from selected solution to initial node.
     */
    std::vector<const graph_state *> get_solution_path(size_t solution_num) const;

    /**
     * @brief get_solution
     * @param solution_num Number of solution (0 - first, 1 - second and so on).
     * Throws std::out_of_range if the number is invalid.
     * @return Pointer to selected solution.
     */
    const graph_state* get_solution(size_t solution_num) const;

    /**
     * @brief get_closed
     * @return Reference to "Closed" set.
     */
    const std::unordered_set<std::unique_ptr<graph_state>>& get_closed() const;

    /**
     * @brief get_open
     * @return Reference to "Open" set.
     */
    const updatable_priority_queue<graph_state, std::function<bool(const graph_state&, const graph_state&)>>& get_open() const;

    template<typename T=std::chrono::milliseconds>
    int64_t get_elapsed_time() const
    {
        return std::chrono::duration_cast<T>(stop_time - start_time).count();
    }

    /**
     * @brief get_stats
     * @return String containing some pieces of information about performed
     * search.
     */
    std::wstring get_stats() const;

private:
    std::unordered_set<std::unique_ptr<graph_state>> closed;
    updatable_priority_queue<graph_state, std::function<bool(const graph_state&, const graph_state&)>> open;
    std::vector<std::unique_ptr<graph_state>> solutions;
    std::chrono::high_resolution_clock::time_point start_time, stop_time;
};

#endif
