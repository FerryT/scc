
#include <algorithm>
#include <cstddef>
#include <functional>
#include <stack>
#include <unordered_map>

#include "tarjan.h"

namespace SCC {

using std::function;
using std::min;
using std::reference_wrapper;
using std::size_t;
using std::unordered_map;

struct node_data_t
{
	using ref = reference_wrapper<node_data_t>;

	node_t node;
	size_t number;
	size_t lowlink;
	enum
	{
		kUnvisited,
		kOnStack,
		kDone
	} state;
	vector<ref> neighbors;
};

components_t tarjan_find_all(const graph_t &graph)
{
	// Initialisation, set up the node data
	unordered_map<node_t, node_data_t> nodes;
	for (const node_t &node : graph.nodes)
		nodes.emplace(node,
			node_data_t{node, 0, 0, node_data_t::kUnvisited, {}});

	for (const edge_t &edge : graph.edges)
	{
		node_data_t &from = nodes.at(edge.from);
		node_data_t &to = nodes.at(edge.to);
		from.neighbors.push_back(to);
	}

	components_t components;

	// Tarjan's algorithm
	std::stack<node_data_t::ref> stack;
	size_t i = 0;

	function<void(node_data_t &)> strong_connect = [&](node_data_t &v)
	{
		v.lowlink = v.number = i++;
		stack.push(v); v.state = node_data_t::kOnStack;

		for (node_data_t &w : v.neighbors)
		{
			if (w.state == node_data_t::kUnvisited)
			{
				strong_connect(w);
				v.lowlink = min(v.lowlink, w.lowlink);
			}
			else if (w.state == node_data_t::kOnStack)
			{
				v.lowlink = min(v.lowlink, w.number);
			}
		}

		if (v.lowlink == v.number)
		{
			component_t component;

			while (!stack.empty() && stack.top().get().number >= v.number)
			{
				node_data_t &w = stack.top();
				stack.pop(); w.state = node_data_t::kDone;
				component.push_back(w.node);
			}

			components.push_back(component);
		}
	};

	for (decltype(nodes)::value_type it : nodes)
	{
		node_data_t &v = it.second;
		if (v.state == node_data_t::kUnvisited)
			strong_connect(v);
	}

	return components;
}

} /* namespace SCC */

