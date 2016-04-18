#ifndef FINDCLASSOFFUNCTION_H
#define FINDCLASSOFFUNCTION_H

#include <string>
#include "Fast_include.h"

class TypesTable;

class FindClassOfFunction {

public:    

	std::string find(VTP_TreeP &tree, bool all_scope = true);
	std::string find(std::string class_scope,TypesTable *types);

};
#endif //FINDCLASSOFFUNCTION_H