#include "PRADecorator.h"

bool PRADecorator::isTriggered(AbstractTree &tree){

	std::string ptr_dcltr		= "ptr_dcltr";
	std::string ref_dcltr		= "ref_dcltr";
	std::string array_dcltr		= "array_dcltr";
	std::string parenth_dcltr	= "parenth_dcltr";
	std::string operator_op;

	operator_op = VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree));
	if(operator_op != ptr_dcltr && operator_op != ref_dcltr && operator_op != array_dcltr) {
		return false;
	}

	operator_op = VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(tree.tree)));
	if(operator_op == parenth_dcltr) {
		return false;
	}

	return true;

}
