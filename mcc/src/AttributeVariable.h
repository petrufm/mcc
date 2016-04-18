#ifndef ATTRIBUTEVARIABLE_H
#define ATTRIBUTEVARIABLE_H

#include "VariableDeclaration.h"

class AttributeVariable : public VariableDeclaration {

public:    

    bool isTriggered(AbstractTree &tree);

	std::string getIndentifierString();

};
#endif //ATTRIBUTEVARIABLE_H