#ifndef LOCALVARIABLE_H
#define LOCALVARIABLE_H

#include "VariableDeclaration.h"

class LocalVariable : public VariableDeclaration {

public:    

    bool isTriggered(AbstractTree &tree);

	std::string getIndentifierString();

};
#endif //LOCALVARIABLE_H