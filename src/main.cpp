
#include <iostream>
#include <utility>
#include <memory>
#include <string>
#include <sstream>

#include "scc.h"
#include "aut.h"
#include "dot.h"

using std::unique_ptr;
using std::make_unique;

struct command_t
{
	enum
	{
		kQuery,
		kInsertEdge,
		kDeleteEdge,
		kUnknown,
		kError
	} type;
	SCC::node_t u, v;
};

command_t parse_command(const std::string &line)
{
	std::istringstream ss(line);
	char c = '\0';
	SCC::node_t u, v;
	ss >> c >> u >> v;

	if (ss.fail())
		return {command_t::kError, 0, 0};
	switch (c)
	{
		case '?': return {command_t::kQuery, u, v};
		case '+': return {command_t::kInsertEdge, u, v};
		case '-': return {command_t::kDeleteEdge, u, v};
		default: return {command_t::kUnknown, u, v};
	}
}

int main(int argc, char const *argv[])
{
	using namespace SCC;

	unique_ptr<graph_t> graph;
	try
	{
		if (argc < 2 || (argv[1][0] == '-' && argv[1][1] == '\0'))
			graph = make_unique<graph_t>(from_aut_stdin());
		else
			graph = make_unique<graph_t>(from_aut_file(argv[1]));
	}
	catch (const std::exception &e)
	{
		std::cerr << "Parse error: " << e.what() << std::endl;
		return -1;
	}

	/*components_t components = find_all(*graph);

	try
	{
		to_dot_stdout(*graph, components);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Output error: " << e.what() << std::endl;
		return -1;
	}*/

	QueryDelete qd(*graph);

	for (;;)
	{
		std::string line;
		std::getline(std::cin, line);
		command_t command = parse_command(line);
		switch (command.type)
		{
			case command_t::kQuery:
				std::cout << '\t'
					<< (qd.query(command.u, command.v) ? "= " : "! ")
					<< command.u << ' ' << command.v << std::endl;
				break;
			case command_t::kInsertEdge:
				std::cout << "Error: insert is unsupported."<< std::endl;
				break;
			case command_t::kDeleteEdge:
				qd.remove({command.u, command.v});
				break;
			case command_t::kUnknown:
				std::cout << "Error: unknown command." << std::endl;
				break;
			default:
				return 0;
		}
	}

	return 0;
}
