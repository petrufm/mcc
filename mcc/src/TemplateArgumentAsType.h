#ifndef TEMPLATEARGUMENTASTYPE_H
#define TEMPLATEARGUMENTASTYPE_H

#include "TriggerCondition.h"

class TemplateArgumentAsType : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //TEMPLATEARGUMENTASTYPE_H