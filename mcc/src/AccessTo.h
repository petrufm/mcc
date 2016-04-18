#ifndef ACCESSTO_H
#define ACCESSTO_H

#include "TriggerCondition.h"

class AccessTo : public TriggerCondition {

public:    

     bool isInBody(VTP_TreeP &tree);

};
#endif //ACCESSTO_H