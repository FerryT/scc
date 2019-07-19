
#ifndef _GES_H
#define _GES_H

#include "scc.h"

namespace SCC {

typedef std::intptr_t distance_t;
static const distance_t inf_dist = INTPTR_MAX;

class GESTree
{
	graph_t graph_;
	const node_t root_;
	vector<node_t> selection_;
	const distance_t distance_;

	public:
	GESTree(const graph_t &, node_t root, const vector<node_t> &selection,
		distance_t limit);
	~GESTree();

	/// Returns to minimal number of vertices in 'selection' ('v' not included)
	/// encountered in all paths from 'root' to 'v' in the graph.
	/// If the distance would exceed 'limit' it returns 'inf_dist' instead.
	distance_t distance_to(node_t v) const;
	
	/// Returns to minimal number of vertices in 'selection' ('v' not included)
	/// encountered in all paths from 'v' to 'root' in the graph.
	/// If the distance would exceed 'limit' it returns 'inf_dist' instead.
	distance_t distance_from(node_t v) const;

	/// Removes edge 'e' from the graph
	void remove(const edge_t &e);

	/// Removes all vertices 'vs' and all their incident edges from the graph.
	void remove(const vector<node_t> &vs);

	/// Returns wether there is a vertex in the graph with distance_from or _to
	/// that exceeds 'limit'.
	/// If so the value 'v' will be set to such a vertex.
	bool get_unreachable_vertex(node_t &v) const;
};

} /* namespace SCC */

#endif /* _GES_H */
