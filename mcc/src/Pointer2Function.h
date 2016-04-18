#ifndef POINTER2FUNCTION_H
#define POINTER2FUNCTION_H

#include "TriggerCondition.h"

class Pointer2Function : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //POINTER2FUNCTION_H