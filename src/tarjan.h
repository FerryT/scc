
#ifndef _TARJAN_H
#define _TARJAN_H

#include "scc.h"

namespace SCC {

components_t tarjan_find_all(const graph_t &);

} /* namespace SCC */

#endif /* _TARJAN_H */