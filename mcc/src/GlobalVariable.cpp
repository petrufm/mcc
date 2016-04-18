#include "GlobalVariable.h"

bool GlobalVariable::isTriggered(AbstractTree &tree){

	VTP_TreeP tmp_tree;
	std::string dcltr_noinit	= "dcltr_noinit";
	std::string dcltr_affinit	= "dcltr_affinit";
	std::string dcltr_callinit	= "dcltr_callinit";
	std::string fndef			= "fndef";
	std::string cdsection		= "class_decls_section";
	std::string qualif;

	//It must be a declarator
	tmp_tree = tree.tree;
	if(dcltr_noinit != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
		dcltr_affinit != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
		dcltr_callinit != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return false;
	}

	//The declaration should not be a typedef or a function function
	//It can be extern!!!
	tmp_tree = VTP_TreeLeft(VTP_TreeUp(tree.tree));
	if(hasStorageClass(tmp_tree,"typedef")) {
		return false;
	}
	if(!isNotFunctionDefinition(tree.tree,qualif)) {
		return false;
	}

	//It must not have a class_decls_section or fndef
	tmp_tree = tree.tree;
	do {
		tmp_tree = VTP_TreeUp(tmp_tree);
	} while(tmp_tree != NULL &&
		    fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
			cdsection != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)));
	if(tmp_tree != NULL) {
		return false;
	}

	//There is an exception: declaration at the file level for a static field
	if(qualif != "") {
		return false;
	}

	return true;
}

std::string GlobalVariable::getIndentifierString() {
	return "global";
}
