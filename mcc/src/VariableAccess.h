#ifndef VARIABLEACCESS_H
#define VARIABLEACCESS_H

#include "TriggerCondition.h"
#include "AccessTo.h"
#include <set>

class VariableAccess : public AccessTo {

public:    

	VariableAccess();

    bool isTriggered(AbstractTree &tree);

private:

	std::set<std::string> op_table;

};
#endif //VARIABLEACCESS_H