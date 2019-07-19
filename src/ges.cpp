
#include "ges.h"

namespace SCC {

// Todo: implement

GESTree::GESTree(const graph_t &graph, node_t root,
	const vector<node_t> &selection, distance_t distance)
	: graph_(graph), root_(root), selection_(selection), distance_(distance)
{}

GESTree::~GESTree()
{}

distance_t GESTree::distance_to(node_t v) const
{
	return inf_dist;
}

distance_t GESTree::distance_from(node_t v) const
{
	return inf_dist;
}

void GESTree::remove(const edge_t &e)
{
}

void GESTree::remove(const vector<node_t> &vs)
{
}

bool GESTree::get_unreachable_vertex(node_t &v) const
{
	return false;
}

} /* namespace SCC */
