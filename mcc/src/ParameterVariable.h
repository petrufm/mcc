#ifndef PARAMETERVARIABLE_H
#define PARAMETERVARIABLE_H

#include "VariableDeclaration.h"

class ParameterVariable : public VariableDeclaration {

public:

    bool isTriggered(AbstractTree &tree);

	std::string getIndentifierString();

};
#endif //PARAMETERVARIABLE_H