#ifndef FUNCTIONCALL_H
#define FUNCTIONCALL_H

#include "TriggerCondition.h"
#include "AccessTo.h"

class FunctionCall : public AccessTo {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //FUNCTIONCALL_H