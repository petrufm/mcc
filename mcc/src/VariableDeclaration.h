#ifndef VARIABLEDECLARATION_H
#define VARIABLEDECLARATION_H

#include "TriggerCondition.h"

class VariableDeclaration : public TriggerCondition {

public:

	bool hasStorageClass(VTP_TreeP &tree,std::string op);
	bool hasTypeQualifier(VTP_TreeP &tree,std::string op);
	bool isNotFunctionDefinition(VTP_TreeP &tree,std::string &qualified);
	virtual std::string getIndentifierString() = 0;

};
#endif //VARIABLEDECLARATION_H
