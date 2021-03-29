#ifndef UPDATABLE_PRIORITY_QUEUE_HPP
#define UPDATABLE_PRIORITY_QUEUE_HPP

#include <vector>
#include <memory>
#include <unordered_map>
#include <sstream>

/**
 * Implementation of the priority queue allowing update of nodes and fast
 * check whether particular node already exists.
 */
template<typename T, typename Compare>
class updatable_priority_queue
{
public:
	updatable_priority_queue(Compare comp = {}) : comp{comp}
	{
	}

	bool empty() const
	{
		return data.empty();
	}

	std::size_t size() const
	{
		return data.size();
	}

	bool contains(const std::unique_ptr<T> &x) const
	{
		return value_to_idx.find(x.get()) != value_to_idx.end();
	}

    std::wstring to_string() const
	{
        std::wostringstream str;
		str << "Queue's content:\n";
		for (std::size_t i = 0; i < data.size(); i++)
			str << i << ":\n" << *data[i] << ", ";
		return str.str();
	}

	void push(std::unique_ptr<T>&& x)
	{
		auto res = value_to_idx.find(x.get());
		if (res == value_to_idx.end())
		{
			data.push_back(std::move(x));
			swim(data.size() - 1);
		}
		else if (comp(*x, *res->first))
		{
			value_to_idx.erase(res->first);
			data[res->second] = std::move(x);
			swim(res->second);
			sink(res->second);
		}

//		if (!is_consistent())
//			throw std::runtime_error("Inconsistent queue!");
//		if (!is_heap())
//			throw std::runtime_error("Broken heap!");
	}

	std::unique_ptr<T> poll()
	{
		if (data.empty())
			throw std::runtime_error("Empty queue!");
		auto res = std::move(data[0]);
		if (data.size() > 1)
			std::swap(data[0], data.back());
		data.pop_back();
		value_to_idx.erase(res.get());
		if (!data.empty())
			sink(0);

//		if (!is_consistent())
//			throw std::runtime_error("Inconsistent queue!");
//		if (!is_heap())
//			throw std::runtime_error("Broken heap!");

		return res;
	}

	typename std::vector<std::unique_ptr<T>>::const_iterator begin() const
	{
		return data.begin();
	}

	typename std::vector<std::unique_ptr<T>>::const_iterator end() const
	{
		return data.end();
	}

private:
	std::vector<std::unique_ptr<T>> data;
	std::unordered_map<T*, uint32_t> value_to_idx;
	Compare comp;

	void swim(std::size_t idx)
	{
		while (idx != 0 && comp(*data[idx], *data[(idx - 1) >> 1]))
		{
			std::swap(data[idx], data[(idx - 1) >> 1]);
			value_to_idx[data[idx].get()] = idx;
			idx = (idx - 1) >> 1;
		}
		value_to_idx[data[idx].get()] = idx;
	}

	void sink(std::size_t idx)
	{
		std::size_t ind;
		while ((ind = 2 * idx + 1) < data.size())
		{
			if (ind + 1 < data.size() && comp(*data[ind + 1], *data[ind]))
				ind++;
			if (comp(*data[idx], *data[ind]) || !comp(*data[ind], *data[idx]))
				// mniejszy (lub równy!)
				break;
			std::swap(data[idx], data[ind]);
			value_to_idx[data[idx].get()] = idx;
			idx = ind;
		}
		value_to_idx[data[idx].get()] = idx;
	}

	bool is_consistent() const
	{
		for (std::size_t i = 0; i < data.size(); i++)
		{
			auto res = value_to_idx.find(data[i].get());
			if (i != res->second)
				return false;
		}
		return true;
	}

	bool is_heap() const
	{
		for (std::size_t i = 0; i < data.size(); i++)
		{
			std::size_t left = 2 * i + 1, right = 2 * i + 2;
			if (left < data.size() && !(comp(*data[i], *data[left]) || !comp(*data[left], *data[i])))
				return false;
			if (right < data.size() && !(comp(*data[i], *data[right]) || !comp(*data[right], *data[i])))
				return false;
		}
		return true;
	}
};

template<typename T, typename Compare>
class stable_updatable_priority_queue
{
public:
	stable_updatable_priority_queue(Compare comp = {}) : comp{comp}, cnt {0}
	{
	}

	bool empty() const
	{
		return data.empty();
	}

	std::size_t size() const
	{
		return data.size();
	}

	bool contains(const std::unique_ptr<T> &x) const
	{
		return value_to_idx.find(x.get()) != value_to_idx.end();
	}

	std::string to_string() const
	{
		std::ostringstream str;
		str << "Queue's content:\n";
		for (std::size_t i = 0; i < data.size(); i++)
			str << i << ":\n" << *data[i].first << ", ";
		return str.str();
	}

	void push(std::unique_ptr<T>&& x)
	{
		auto res = value_to_idx.find(x.get());
		if (res == value_to_idx.end())
		{
			data.push_back(std::make_pair(std::move(x), cnt++));
			swim(data.size() - 1);
		}
		else if (comp(*x, *res->first))
		{
			value_to_idx.erase(res->first);
			data[res->second].first = std::move(x);
			swim(res->second);
			sink(res->second);
		}

//		if (!is_consistent())
//			throw std::runtime_error("Inconsistent queue!");
//		if (!is_heap())
//			throw std::runtime_error("Broken heap!");
	}

	std::unique_ptr<T> poll()
	{
		if (data.empty())
			throw std::runtime_error("Empty queue!");
		auto res = std::move(data[0]);
		if (data.size() > 1)
			std::swap(data[0], data.back());
		data.pop_back();
		value_to_idx.erase(value_to_idx.find(res.first.get()));
		if (!data.empty())
			sink(0);

//		if (!is_consistent())
//			throw std::runtime_error("Inconsistent queue!");
//		if (!is_heap())
//			throw std::runtime_error("Broken heap!");

		return std::move(res.first);
	}

	auto begin() const
	{
		return data.cbegin();
	}

	auto end() const
	{
		return data.cend();
	}

private:
	std::vector<std::pair<std::unique_ptr<T>, uint32_t>> data;
	std::unordered_map<T*, uint32_t> value_to_idx;
	Compare comp;
	uint32_t cnt;

	void swim(std::size_t idx)
	{
		while (idx != 0 && (comp(*data[idx].first, *data[(idx - 1) >> 1].first) || (!comp(*data[idx].first, *data[(idx - 1) >> 1].first) && data[idx].second < data[(idx - 1) >> 1].second)))
		{
			std::swap(data[idx], data[(idx - 1) >> 1]);
			value_to_idx[data[idx].first.get()] = idx;
			idx = (idx - 1) >> 1;
		}
		value_to_idx[data[idx].first.get()] = idx;
	}

	void sink(std::size_t idx)
	{
		std::size_t ind;
		while ((ind = 2 * idx + 1) < data.size())
		{
			if (ind + 1 < data.size() && (comp(*data[ind + 1].first, *data[ind].first) || (!comp(*data[ind + 1].first, *data[ind].first) && data[ind + 1].second < data[ind].second)))
				ind++;
			if (comp(*data[idx].first, *data[ind].first) || (!comp(*data[ind].first, *data[idx].first) && data[idx].second < data[ind].second))
				break;
			std::swap(data[idx], data[ind]);
			value_to_idx[data[idx].first.get()] = idx;
			idx = ind;
		}
		value_to_idx[data[idx].first.get()] = idx;
	}

	bool is_consistent() const
	{
		for (std::size_t i = 0; i < data.size(); i++)
		{
			auto res = value_to_idx.find(data[i].first.get());
			if (i != res->second)
				return false;
		}
		return true;
	}

	bool is_heap() const
	{
		for (std::size_t i = 0; i < data.size(); i++)
		{
			std::size_t left = 2 * i + 1, right = 2 * i + 2;
			if (left < data.size() && !(comp(*data[i].first, *data[left].first) || !comp(*data[left].first, *data[i].first)))
				return false;
			if (right < data.size() && !(comp(*data[i].first, *data[right].first) || !comp(*data[right].first, *data[i].first)))
				return false;
		}
		return true;
	}
};

#endif
