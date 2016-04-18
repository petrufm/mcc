#ifndef NAMESPACEDECLARATION_H
#define NAMESPACEDECLARATION_H

#include "TriggerCondition.h"

class NamespaceDeclaration : public TriggerCondition {

public:    

    bool isTriggered(AbstractTree &tree);

};
#endif //NAMESPACEDECLARATION_H