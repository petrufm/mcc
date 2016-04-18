#ifndef FINDPOINTERTOFUNCTIONTYPE_H
#define FINDPOINTERTOFUNCTIONTYPE_H

#include "fast_include.h"
#include <string>
#include <vector>

class FindPointerToFunctionType {

public:    

	std::string find(VTP_TreeP & tree,std::vector<std::string> *types);

};
#endif //FINDPOINTERTOFUNCTIONTYPE_H