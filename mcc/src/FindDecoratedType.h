#ifndef FINDDECORATEDTYPE_H
#define FINDDECORATEDTYPE_H

#include "fast_include.h"
#include <string>
#include <vector>

class FindDecoratedType {

public:    

	std::string find(VTP_TreeP &tree,std::vector<std::string> *types);

};
#endif //FINDDECORATEDTYPE_H