#ifndef NEVER_H
#define NEVER_H

#include "TriggerCondition.h"

class Never : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //NEVER_H