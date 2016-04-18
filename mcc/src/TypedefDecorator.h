#ifndef TYPEDEFDECORATOR_H
#define TYPEDEFDECORATOR_H

#include "TriggerCondition.h"

class TypedefDecorator : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //TYPEDEFDECORATOR_H