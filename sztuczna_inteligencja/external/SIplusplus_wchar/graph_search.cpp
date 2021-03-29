#include "graph_search.hpp"
#include "queue.hpp"
#include <queue>
#include <iostream>
#include <chrono>

std::wstring parse_time(int64_t ms)
{
    if (ms < 0)
        throw std::runtime_error("Negative measure!");
    wchar_t format[32] = {0};
    swprintf(format,
            L"%02d:%02d:%02d.%03d",
            static_cast<int>(ms / 3600000),
            static_cast<int>((ms / 60000) % 60),
            static_cast<int>((ms / 1000) % 60),
            static_cast<int>(ms % 1000));
    return format;
}

bool depth_first_search(const graph_state &s,
                        std::function<bool(const std::unique_ptr<graph_state> &)> callback)
{
    if (s.is_solution())
        return true;
    for (auto &&t : s.get_successors())
        if (depth_first_search(*t, callback) && !callback(std::move(t)))
            break;
    return false;
}

std::vector<std::unique_ptr<graph_state>> breadth_first_search(const graph_state &initial,
                                                               bool print_stats)
{
    std::unordered_set<std::unique_ptr<graph_state>> closed;
    std::unordered_set<graph_state*> open_copy;
    std::queue<std::unique_ptr<graph_state>> open;
    std::vector<std::unique_ptr<graph_state>> path;

    auto start_time = std::chrono::high_resolution_clock::now();
    auto initial_clone = initial.clone();
    initial_clone->set_parent(nullptr);
    initial_clone->update_score(0);
    open.push(std::unique_ptr<graph_state>(std::move(initial_clone)));
    while (!open.empty())
    {
        auto s = std::move(open.front());
        open.pop();
        open_copy.erase(s.get());

        if (s->is_solution())
        {
            if (print_stats)
            {
                auto stop_time = std::chrono::high_resolution_clock::now();
                std::wcout << "elapsed time: "
                          << parse_time(std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count())
                          << std::endl;
                std::wcout << "#closed: " << closed.size()
                          << ", #open: " << open.size() << std::endl;
            }
            const graph_state *parent_state = s->get_parent();
            path.emplace_back(std::move(s));
            while (parent_state != nullptr)
            {
                std::unique_ptr<graph_state> dummy {const_cast<graph_state*>(parent_state)};
                path.emplace_back(std::move(closed.extract(closed.find(dummy)).value()));
                dummy.release();
                parent_state = parent_state->get_parent();
            }
            break;
        }

        for (auto &&t : s->get_successors())
            if (closed.find(t) == closed.end() && open_copy.find(t.get()) == open_copy.end())
            {
                open_copy.emplace(t.get());
                open.emplace(std::move(t));
            }
        closed.emplace(std::move(s));
    }
    return path;
}

void breadth_first_search(const graph_state &initial,
                          std::function<bool(std::unique_ptr<graph_state>&)> callback,
                          bool print_stats)
{
    std::unordered_set<std::unique_ptr<graph_state>> closed;
    std::unordered_set<graph_state*> open_copy;
    std::queue<std::unique_ptr<graph_state>> open;

    auto start_time = std::chrono::high_resolution_clock::now();
    auto initial_clone = initial.clone();
    initial_clone->set_parent(nullptr);
    initial_clone->update_score(0);
    open.push(std::unique_ptr<graph_state>(std::move(initial_clone)));
    while (!open.empty())
    {
        auto s = std::move(open.front());
        open.pop();
        open_copy.erase(s.get());

        if (s->is_solution())
        {
            if (callback(s))
                continue;
            else
                break;
        }

        for (auto &&t : s->get_successors())
            if (closed.find(t) == closed.end() && open_copy.find(t.get()) == open_copy.end())
            {
                open_copy.emplace(t.get());
                open.emplace(std::move(t));
            }
        closed.emplace(std::move(s));
    }

    if (print_stats)
    {
        auto stop_time = std::chrono::high_resolution_clock::now();
        std::wcout << "elapsed time: " << parse_time(std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count()) << std::endl;
        std::wcout << "#closed: " << closed.size() << ", #open: " << open.size() << std::endl;
    }
}

informative_searcher::informative_searcher(const graph_state &initial,
                                           std::function<bool(const graph_state &, const graph_state &)> comp,
                                           std::size_t max_solutions)
    : open {comp}
{
    start_time = std::chrono::high_resolution_clock::now();
    if (max_solutions == 0)
    {
        stop_time = start_time;
        return;
    }
    auto initial_clone = initial.clone();
    initial_clone->set_parent(nullptr);
    initial_clone->update_score(0);
    open.push(std::unique_ptr<graph_state>(std::move(initial_clone)));
    int count = 0;
    while (!open.empty())
    {
        count++;
        auto s = std::move(open.poll());

        if (s->is_solution())
        {
            solutions.emplace_back(std::move(s));
            if (solutions.size() >= max_solutions)
                break;
            else
                continue;
        }

        for (auto &&t : s->get_successors())
            if (closed.find(t) == closed.end())
                open.push(std::move(t));
        closed.emplace(std::move(s));
    }
    stop_time  = std::chrono::high_resolution_clock::now();
}

size_t informative_searcher::get_number_of_solutions() const
{
    return solutions.size();
}

std::vector<const graph_state*> informative_searcher::get_solution_path(size_t solution_num) const
{
    std::vector<const graph_state*> path;
    const graph_state *state = solutions.at(solution_num).get();
    while (state != nullptr)
    {
        path.emplace_back(state);
        state = state->get_parent();
    }
    return path;
}

const graph_state* informative_searcher::get_solution(size_t solution_num) const
{
    return solutions.at(solution_num).get();
}

const std::unordered_set<std::unique_ptr<graph_state>>& informative_searcher::get_closed() const
{
    return closed;
}

const updatable_priority_queue<graph_state, std::function<bool(const graph_state&, const graph_state&)>>& informative_searcher::get_open() const
{
    return open;
}

std::wstring informative_searcher::get_stats() const
{
    std::wostringstream out;
    out << "elapsed time: " << parse_time(get_elapsed_time<std::chrono::milliseconds>()) << std::endl;
    out << "number of solutions: " << solutions.size() << std::endl;
    out << "#closed: " << closed.size() << ", #open: " << open.size() << std::endl;
    return out.str();
}
