#ifndef CLASSTEMPLATEPARAMETER_H
#define CLASSTEMPLATEPARAMETER_H

#include "TriggerCondition.h"

class ClassTemplateParameter : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //CLASSTEMPLATEPARAMETER_H