#include "ClassDeclaration.h"

bool ClassDeclaration::isTriggered(AbstractTree &tree) {

	std::string operatorName = "class_head";

	if(operatorName == VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {

		operatorName = "class_decls";
		if(operatorName == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeRight(tree.tree)))) {
			return true;
		} else {
			return false;
		}
	}

	return false;

}
