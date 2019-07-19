
#include <cctype>
#include <cstddef>
#include <fstream>
#include <string>
#include <stdexcept>
#include <iostream>

#include "aut.h"

namespace SCC {

using std::invalid_argument;
using std::size_t;
using std::string;

struct aut_header_t
{
	size_t initial_state;
	size_t edge_count;
	size_t node_count;
};

struct aut_edge_t
{
	size_t from;
	string label;
	size_t to;
};

string ltrim(const string &str)
{
	for (string::size_type pos = 0; pos < str.length(); ++pos)
		if (!std::isspace(str[pos]))
			return str.substr(pos);
	return {};
}

aut_header_t aut_parse_header(string str)
{
	aut_header_t header = {0, 0, 0};

	str = ltrim(str);
	if (str.substr(0, 3) != "des")
		throw invalid_argument("expected \"des\"");
	
	str = ltrim(str.substr(3));
	if (str[0] != '(')
		throw invalid_argument("expected \"(\"");

	str = ltrim(str.substr(1));
	{
		string::size_type pos = 0;
		header.initial_state = static_cast<size_t> (stol(str, &pos));
		str = str.substr(pos);
	}

	str = ltrim(str);
	if (str[0] != ',')
		throw invalid_argument("expected \",\"");

	str = ltrim(str.substr(1));
	{
		string::size_type pos = 0;
		header.edge_count = static_cast<size_t> (stol(str, &pos));
		str = str.substr(pos);
	}

	str = ltrim(str);
	if (str[0] != ',')
		throw invalid_argument("expected \",\"");

	str = ltrim(str.substr(1));
	{
		string::size_type pos = 0;
		header.node_count = static_cast<size_t> (stol(str, &pos));
		str = str.substr(pos);
	}

	str = ltrim(str);
	if (str[0] != ')')
		throw invalid_argument("expected \")\"");

	str = ltrim(str.substr(1));
	if (!str.empty())
		throw invalid_argument("expected new line");

	return header;
}

aut_edge_t aut_parse_edge(string str)
{
	aut_edge_t edge = {0, {}, 0};

	str = ltrim(str);
	if (str[0] != '(')
		throw invalid_argument("expected \"(\"");

	str = ltrim(str.substr(1));
	{
		string::size_type pos = 0;
		edge.from = static_cast<size_t> (stol(str, &pos));
		str = str.substr(pos);
	}

	str = ltrim(str);
	if (str[0] != ',')
		throw invalid_argument("expected \",\"");

	str = ltrim(str.substr(1));
	if (str[0] == '"')
	{
		string::size_type pos = str.rfind('"');
		edge.label = str.substr(1, pos - 1);
		str = str.substr(pos + 1);
	}
	else if (std::isalpha(str[0]) || str[0] == '*')
	{
		string::size_type pos = 0;
		while (std::isalnum(str[pos])) pos++;
		
		edge.label = str.substr(0, pos);
		str = str.substr(pos);
	}
	else
		throw invalid_argument("expected a letter or \"*\"");

	str = ltrim(str);
	if (str[0] != ',')
		throw invalid_argument("expected \",\"");

	str = ltrim(str.substr(1));
	{
		string::size_type pos = 0;
		edge.to = static_cast<size_t> (stol(str, &pos));
		str = str.substr(pos);
	}

	str = ltrim(str);
	if (str[0] != ')')
		throw invalid_argument("expected \")\"");

	str = ltrim(str.substr(1));
	if (!str.empty())
		throw invalid_argument("expected new line");

	return edge;
}

graph_t from_aut_stream(std::istream &is)
{
	vector<node_t> nodes;
	vector<edge_t> edges;
	string line;

	getline(is, line);
	aut_header_t header = aut_parse_header(line);

	for (node_t node = 0; node < header.node_count; ++node)
		nodes.push_back(node);

	for (size_t i = 0; i < header.edge_count; ++i)
	{
		if (!is.good())
			throw invalid_argument("unexpected end of input");

		getline(is, line);
		aut_edge_t edge = aut_parse_edge(line);

		if (edge.from >= header.node_count
			|| edge.to >= header.node_count)
			throw invalid_argument("edge contains invalid node");

		node_t from = static_cast<node_t> (edge.from);
		node_t to = static_cast<node_t> (edge.to);
		edges.push_back({from, to});
	}

	return {nodes, edges};
}

graph_t from_aut_file(const char *filename)
{
	std::ifstream file(filename);

	if (!file.good())
		throw std::runtime_error("could not read file");

	return from_aut_stream(file);
}

graph_t from_aut_stdin()
{
	return from_aut_stream(std::cin);
}

} /* namespace SCC */
