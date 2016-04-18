#include "AccessTo.h"

bool AccessTo::isInBody(VTP_TreeP &tree) {

	std::string fndef			= "fndef";
	std::string class_op		= "class";
	std::string compound		= "compound";
	std::string ctor_initializer= "ctor_initializer";
	
	VTP_TreeP tmp_tree;

	tmp_tree = tree;
	while(tmp_tree != NULL && 
		  fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
		  class_op != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeUp(tmp_tree);
	}

	if(tmp_tree == NULL || fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return false;
	}

	tmp_tree = VTP_TreeDown(tmp_tree,3);
	if(compound == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return true;
	} else if(ctor_initializer == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return true;
	} else {
		return false;
	}

}
