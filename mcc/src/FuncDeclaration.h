#ifndef FUNCDECLARATION_H
#define FUNCDECLARATION_H

#include "TriggerCondition.h"

class FuncDeclaration : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //FUNCDECLARATION_H