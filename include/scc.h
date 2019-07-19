
#ifndef _SCC_H
#define _SCC_H

#include <cstdint>
#include <vector>

namespace SCC {

using std::vector;

typedef std::intptr_t node_t;

struct edge_t
{
	node_t from, to;
};

struct graph_t
{
	vector<node_t> nodes;
	vector<edge_t> edges;
};


using component_t = vector<node_t>;
using components_t = vector<component_t>;

components_t find_all(const graph_t &);

class QueryDelete
{
	struct Internal;
	Internal *internal_;

	public:
	QueryDelete(const graph_t &);
	~QueryDelete();

	/// Queries if two nodes are strongly connected, c.q are in the same SCC
	bool query(node_t u, node_t v);

	/// Removes an edge from the graph
	void remove(const edge_t &);
};

} /* namespace SCC */

#endif /*_SCC_H*/
