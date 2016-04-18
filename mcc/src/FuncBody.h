#ifndef FUNCBODY_H
#define FUNCBODY_H
#include "TriggerCondition.h"

class FuncBody : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //FUNCBODY_H