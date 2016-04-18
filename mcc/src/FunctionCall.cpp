#include "FunctionCall.h"

bool FunctionCall::isTriggered(AbstractTree &tree) {

	std::string call = "call";

	//It has to be a call
	if(call != VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {
		return false;
	}

	//It has to be in a body
	if(!isInBody(tree.tree)) {
		return false;
	}

	return true;
}
