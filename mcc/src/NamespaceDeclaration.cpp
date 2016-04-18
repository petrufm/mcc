#include "NamespaceDeclaration.h"

bool NamespaceDeclaration::isTriggered(AbstractTree &tree) {

	std::string operatorName = "namespace_def";
	
	return operatorName == VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree));

}
