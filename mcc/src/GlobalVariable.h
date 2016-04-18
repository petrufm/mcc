#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include "VariableDeclaration.h"

class GlobalVariable : public VariableDeclaration {
    
public:    

    bool isTriggered(AbstractTree &tree);

	std::string getIndentifierString();

};
#endif //GLOBALVARIABLE_H