#ifndef TEMPLATEARGUMENTASTYPEININSTANCE_H
#define TEMPLATEARGUMENTASTYPEININSTANCE_H

#include "TriggerCondition.h"

class TemplateArgumentAsTypeInInstance : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //TEMPLATEARGUMENTASTYPEININSTANCE_H