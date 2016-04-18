#ifndef FINDBASETYPE_H
#define FINDBASETYPE_H

#include "fast_include.h"
#include <string>
#include <vector>

class FindBaseType {

public:    

	std::string find(VTP_TreeP &tree, std::vector<std::string> *types);

};
#endif //FINDBASETYPE_H