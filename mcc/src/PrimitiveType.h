#ifndef PRIMITIVETYPE_H
#define PRIMITIVETYPE_H

#include "TriggerCondition.h"

class PrimitiveType : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //PRIMITIVETYPE_H