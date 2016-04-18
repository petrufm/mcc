#ifndef ALWAYS_H
#define ALWAYS_H

#include "TriggerCondition.h"

class Always : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //ALWAYS_H