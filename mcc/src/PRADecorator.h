#ifndef PRADECORATOR_H
#define PRADECORATOR_H

#include "TriggerCondition.h"

class PRADecorator : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //PRADECORATOR_H