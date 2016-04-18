#include "VariableDeclaration.h"

bool VariableDeclaration::hasStorageClass(VTP_TreeP &tree,std::string op) {

	VTP_TreeP tmp_tree,child;
	std::string storage_class	= "storage_class";

	tmp_tree = tree;
    ITERATOR_MAP(VTP_TreeChild, tmp_tree, child); {
		if(storage_class == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
			if(op == VTP_NAME_STRING(VTP_TreeAtomValue(child))) {
				return true;
			}
		}
	}
	ITERATOR_END_MAP(VTP_TreeChild);
	return false;
}

bool VariableDeclaration::hasTypeQualifier(VTP_TreeP &tree,std::string op) {

	VTP_TreeP tmp_tree,child;
	std::string type_qualifier	= "type_qualifier";

	tmp_tree = tree;
    ITERATOR_MAP(VTP_TreeChild, tmp_tree, child); {
		if(type_qualifier == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
			if(op == VTP_NAME_STRING(VTP_TreeAtomValue(child))) {
				return true;
			}
		}
	}
	ITERATOR_END_MAP(VTP_TreeChild);
	return false;
}


bool VariableDeclaration::isNotFunctionDefinition(VTP_TreeP &tree, std::string &qualified) {

	std::string func_dcltr		= "func_dcltr";
	std::string parenth_dcltr	= "parenth_dcltr";
	std::string memptr_dcltr	= "memptr_dcltr";
	std::string ptr_dcltr		= "ptr_dcltr";
	std::string ref_dcltr		= "ref_dcltr";
	std::string scope			= "scope";
	std::string op;

	VTP_TreeP tmp_tree,child;

	qualified = "";

	//Next, it must not be a function
	tmp_tree = tree;
	while(tmp_tree != NULL) {

		if(func_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
			if(parenth_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
				return false;
			}
			tmp_tree = VTP_TreeDown(tmp_tree,0);
			if( ptr_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
				memptr_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
				ref_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
					return false;
			}
		}
		op = VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree));
		if(op == "identifier") {
			tmp_tree = NULL;
		} else if(op == "qualified_id") {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
			if(tmp_tree != NULL && scope == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
				ITERATOR_MAP(VTP_TreeChild, tmp_tree, child); {
					qualified+= VTP_OP_NAME(VTP_TREE_OPERATOR(child));
				}
				ITERATOR_END_MAP(VTP_TreeChild);
			}
			tmp_tree = NULL;
		} else if(op == "func_dcltr") {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		} else if(op == "array_dcltr") {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		} else if(op == "ptr_dcltr") {
			tmp_tree = VTP_TreeDown(tmp_tree,1);
		} else if(op == "ref_dcltr") {
			tmp_tree = VTP_TreeDown(tmp_tree,1);
		} else if(op == "memptr_dcltr") {
			tmp_tree = VTP_TreeDown(tmp_tree,2);
		} else if(op == "parenth_dcltr") {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		} else if(op == "dcltr_noinit") {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		} else if(op == "dcltr_affinit") {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		} else if(op == "dcltr_callinit") {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		} else {
			break;
		}
	}

	return true;
};
