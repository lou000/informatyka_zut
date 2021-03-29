#include "graph_state.hpp"
#include <cmath>

graph_state::graph_state()
	: parent {nullptr},
	  fscore(std::nan("")),
	  gscore(0),
	  hscore(std::nan(""))
{
}

graph_state::~graph_state()
{
}

bool graph_state::operator== (const graph_state &s) const
{
	return is_equal(s);
}

double graph_state::get_f() const
{
	return fscore;
}

double graph_state::get_g() const
{
	return gscore;
}

double graph_state::get_h() const
{
	return hscore;
}

void graph_state::update_score(double new_g)
{
	gscore = new_g;
	hscore = get_heuristic_grade();
	fscore = gscore + hscore;
}

const graph_state* graph_state::get_parent() const
{
	return parent;
}

void graph_state::set_parent(const graph_state *parent)
{
	this->parent = parent;
}

double graph_state::get_heuristic_grade() const
{
	return 0;
}

namespace std
{
    wostream& operator << (wostream& out, const graph_state &s)
	{
		out << s.to_string();
		return out;
	}
}
