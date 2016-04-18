#include "ParameterVariable.h"

bool ParameterVariable::isTriggered(AbstractTree &tree){

	VTP_TreeP tmp_tree;
	std::string parm_decl	= "parm_decl";
	std::string parmlist	= "parmlist";
	std::string fndef		= "fndef";
	std::string func_dcltr	= "func_dcltr";
	std::string class_op	= "class_op";
	std::string qualif;

	//It must have a parm_dctl parent
	tmp_tree = VTP_TreeUp(tree.tree);
	if(tmp_tree == NULL || parm_decl != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return false;
	}

	//And the parent must be a child for parmlist (parm_dcltr may be child for template...)
	tmp_tree = VTP_TreeUp(tmp_tree);
	if(parmlist != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return false;
	}

	//An the parent must be func_dcltr (parmlist appears also at catch handlers)
	tmp_tree = VTP_TreeUp(tmp_tree);
	if(func_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return false;
	}

	//It has to be the second child
	if(VTP_TreeRank(tree.tree) != 1) {
		return false;
	}

	//The declaration should not be a typedef,extern or a function
	//It usually can not be extern (but who knows?)
	tmp_tree = VTP_TreeLeft(tree.tree);
	if(hasStorageClass(tmp_tree,"typedef")) {
		return false;
	}
	if(hasStorageClass(tmp_tree,"extern")) {
		return false;
	}
	if(!isNotFunctionDefinition(tree.tree,qualif)) {
		return false;
	}

	//And we must be at a function definition
	tmp_tree = tree.tree;
	do {
		tmp_tree = VTP_TreeUp(tmp_tree);
	} while(tmp_tree != NULL &&
			class_op != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
			fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)));
	if(tmp_tree == NULL  || fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return false;
	}

	return true;
}

std::string ParameterVariable::getIndentifierString() {
	return "parameter";
}
