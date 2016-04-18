#include "AttributeVariable.h"

bool AttributeVariable::isTriggered(AbstractTree &tree){

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

	//The declaration should not be a typedef,extern or a function
	//In MVC it can't be extern (but who knows?)
	tmp_tree = VTP_TreeLeft(VTP_TreeUp(tree.tree));
	if(hasStorageClass(tmp_tree,"typedef")) {
		return false;
	}
	if(hasStorageClass(tmp_tree,"extern")) {
		return false;
	}
	if(!isNotFunctionDefinition(tree.tree,qualif)) {
		return false;
	}

	//It must have a class_decls_section before a fndef
	tmp_tree = tree.tree;
	do {
		tmp_tree = VTP_TreeUp(tmp_tree);
	} while(tmp_tree != NULL &&
		    fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
			cdsection != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)));
	if(tmp_tree == NULL || fndef == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return false;
	}

	return true;
}

std::string AttributeVariable::getIndentifierString() {
	return "attribute";
}

