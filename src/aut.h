
#ifndef _AUT_H
#define _AUT_H

#include "scc.h"

namespace SCC {

graph_t from_aut_file(const char *filename);
graph_t from_aut_stdin();

} /* namespace SCC */

#endif /* _AUT_H */
