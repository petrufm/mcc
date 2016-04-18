#include "PrimitiveType.h"

bool PrimitiveType::isTriggered(AbstractTree &tree) {

	std::string operatorName = "typespec";
	
	return operatorName == VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree));

}
