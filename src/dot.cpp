
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "dot.h"

namespace SCC {

void to_dot_stream(const graph_t &graph, std::ostream &os,
	const components_t &ranks)
{
	using std::cout;
	using std::endl;

	cout << "digraph" << endl << '{' << endl;
	cout << "\tnode [shape = circle]" << endl;
	for (const edge_t &edge : graph.edges)
	{
		cout << '\t' << edge.from << " -> " << edge.to << endl;
	}
	for (const component_t &rank : ranks)
	{
		cout << "\t{ rank = same ";
		for (const node_t &node : rank)
		{
			cout << node << ' ';
		}
		cout << '}' << endl;
	}
	cout << '}' << endl;
}

void to_dot_file(const graph_t &graph, const char *filename,
	const components_t &ranks)
{
	std::ofstream file(filename);

	if (!file.good())
		throw std::runtime_error("unable to write to file");

	to_dot_stream(graph, file, ranks);
}

void to_dot_stdout(const graph_t &graph, const components_t &ranks)
{
	to_dot_stream(graph, std::cout, ranks);
}

} /* namespace SCC */
