
#ifndef _DOT_H
#define _DOT_H

#include "scc.h"

namespace SCC {

void to_dot_file(const graph_t &, const char *filename,
	const components_t &ranks = {});

void to_dot_stdout(const graph_t &, const components_t &ranks = {});

} /* namespace SCC */

#endif /* _DOT_H */
