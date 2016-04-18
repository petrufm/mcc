#ifndef CLASSDECLARATION_H
#define CLASSDECLARATION_H

#include "TriggerCondition.h"

class ClassDeclaration : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //CLASSDECLARATION_H