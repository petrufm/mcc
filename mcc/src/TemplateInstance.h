#ifndef TEMPLATEINSTANCE_H
#define TEMPLATEINSTANCE_H
#include "TriggerCondition.h"

class TemplateInstance : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //TEMPLATEINSTANCE_H