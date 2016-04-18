#ifndef FINDCLASSCONTEXT_H
#define FINDCLASSCONTEXT_H

#include "Fast_include.h"
#include <string>
#include <vector>

class TypesTable;

class FindClassContext {

public:    

    std::string find(VTP_TreeP &tree);

	std::string find(std::string class_name, std::vector<std::string> *usedTypes, TypesTable *table);

private:

	static int error_no;
};
#endif //FINDCLASSCONTEXT_H