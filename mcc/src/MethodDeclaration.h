#ifndef METHODDECLARATION_H
#define METHODDECLARATION_H

#include "TriggerCondition.h"
#include "FuncDeclaration.h"

class MethodDeclaration : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

private:

	FuncDeclaration funcDecl;

};
#endif //METHODDECLARATION_H