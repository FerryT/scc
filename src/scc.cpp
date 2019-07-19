
#include "scc.h"
#include "tarjan.h"

namespace SCC {

components_t find_all(const graph_t &graph)
{
	return tarjan_find_all(graph);
}

// Todo: implement

struct QueryDelete::Internal
{
};

QueryDelete::QueryDelete(const graph_t &graph)
	: internal_(new Internal)
{
}

QueryDelete::~QueryDelete()
{
	delete internal_;
	internal_ = nullptr;
}

bool QueryDelete::query(node_t u, node_t v)
{
	return false;
}

void QueryDelete::remove(const edge_t &edge)
{
}


} /* namespace SCC */
