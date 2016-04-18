#ifndef TRIGGERCONDITION_H
#define TRIGGERCONDITION_H

#include "FilesParser.h"

class TriggerCondition {

public:    

    virtual bool isTriggered(AbstractTree &tree) =0;

};
#endif //TRIGGERCONDITION_H