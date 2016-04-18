#ifndef FINDSIGNATURE_H
#define FINDSIGNATURE_H

#include "fast_include.h"
#include <string>
#include <vector>

class FindSignature {

public:    

	std::string find(VTP_TreeP &tree,std::vector<std::string> *types);

	std::string findElement(VTP_TreeP &tree,std::vector<std::string> *types);

	std::string findVariable(VTP_TreeP &tree,std::vector<std::string> *types);

private:

	std::string getTypeObject(VTP_TreeP &tree, bool &decorate, std::vector<std::string> *types, int level = 1);
};
#endif //FINDSIGNATURE_H