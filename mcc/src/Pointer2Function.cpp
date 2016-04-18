#include "Pointer2Function.h"

bool Pointer2Function::isTriggered(AbstractTree &tree){

	std::string func_dcltr		= "func_dcltr";
	std::string parenth_dcltr	= "parenth_dcltr";
	std::string memptr_dcltr	= "memptr_dcltr";
	std::string ptr_dcltr		= "ptr_dcltr";
	std::string ref_dcltr		= "ref_dcltr";

	if(parenth_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {
		return false;
	}

	if(func_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(tree.tree)))) {
		return false;
	}

	if(ptr_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tree.tree,0))) &&
	   memptr_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tree.tree,0))) &&
	   ref_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tree.tree,0)))) {
	   return false;
	}

	return true;
}
