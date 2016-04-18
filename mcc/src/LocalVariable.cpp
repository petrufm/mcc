#include "LocalVariable.h"

bool LocalVariable::isTriggered(AbstractTree &tree){

	VTP_TreeP tmp_tree;
	std::string dcltr_noinit	= "dcltr_noinit";
	std::string dcltr_affinit	= "dcltr_affinit";
	std::string dcltr_callinit	= "dcltr_callinit";
	std::string fndef			= "fndef";
	std::string cdsection		= "class_decls_section";
	std::string parm_decl		= "parm_decl";
	std::string parmlist		= "parmlist";
	std::string handler			= "handler";
	std::string absdcltr		= "absdcltr";
	std::string qualif;

	//It must be a declarator (or a parm_decl)
	tmp_tree = tree.tree;
	if(dcltr_noinit != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
		dcltr_affinit != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
		dcltr_callinit != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			if(VTP_TreeUp(tmp_tree) == NULL ||
				parm_decl != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(tmp_tree)))) {
					return false;
			}
	}

	//If it is parm_decl then it must be a catch handler parameter
	if(VTP_TreeUp(tmp_tree) != NULL && parm_decl == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(tmp_tree)))) {
		//It has to be the second child
		if(VTP_TreeRank(tree.tree) != 1) {
			return false;
		}
		//It must not be abstract
		if(absdcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {
			return false;
		}
		//Be a handler parameters
		tmp_tree = VTP_TreeUp(VTP_TreeUp(tree.tree));
		if(parmlist != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			return false;
		}
		//An the parent must be handler
		tmp_tree = VTP_TreeUp(tmp_tree);
		if(handler != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			return false;
		}
		//The declaration should not be a typedef,extern or a function
		//A parameter can not be extern (but for protection...)
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
	} else {
		//The declaration should not be a typedef or a function function
		//It can be extern!!!
		tmp_tree = VTP_TreeLeft(VTP_TreeUp(tree.tree));
		if(hasStorageClass(tmp_tree,"typedef")) {
			return false;
		}
		if(!isNotFunctionDefinition(tree.tree,qualif)) {
			return false;
		}
	}

	//It must have a fndef defore a class_decls_section
	tmp_tree = tree.tree;
	do {
		tmp_tree = VTP_TreeUp(tmp_tree);
	} while(tmp_tree != NULL &&
		    fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
			cdsection != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)));
	if(tmp_tree == NULL || cdsection == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return false;
	}

	return true;

}

std::string LocalVariable::getIndentifierString() {
	return "local";
}
