#ifndef INHERITANCERELATION_H
#define INHERITANCERELATION_H

#include "TriggerCondition.h"

class InheritanceRelation : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //INHERITANCERELATION_H