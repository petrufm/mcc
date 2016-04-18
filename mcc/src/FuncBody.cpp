#include "FuncBody.h"

bool FuncBody::isTriggered(AbstractTree &tree) {

	std::string compound = "compound";
	std::string fndef = "fndef";
	std::string ctor_initializer = "ctor_initializer";

	if(compound == VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree)) &&
	   fndef == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(tree.tree)))) {
		return true;
	}

	if(compound == VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree)) &&
	   ctor_initializer == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(tree.tree))) &&
	   fndef == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(VTP_TreeUp(tree.tree))))) {
		return true;
	}

	return false;
}
