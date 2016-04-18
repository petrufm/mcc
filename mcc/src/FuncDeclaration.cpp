#include "FuncDeclaration.h"

bool FuncDeclaration::isTriggered(AbstractTree &tree) {

	std::string func_dcltr				= "func_dcltr";
	std::string parenth_dcltr			= "parenth_dcltr";
	std::string memptr_dcltr			= "memptr_dcltr";
	std::string ptr_dcltr				= "ptr_dcltr";
	std::string ref_dcltr				= "ref_dcltr";
	std::string storage_class			= "storage_class";
	std::string friend_op				= "friend";
	std::string declaration_specifiers	= "declaration_specifiers";
	VTP_TreeP tmp_tree,tmp,child;

	//Is has to be a function declaration
	if(func_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {
		return false;
	}

	//Is must not be a pointer to function
	if(parenth_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tree.tree,0))) &&
	   (ptr_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(VTP_TreeDown(tree.tree,0),0))) ||
	    memptr_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(VTP_TreeDown(tree.tree,0),0))) ||
	    ref_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(VTP_TreeDown(tree.tree,0),0))))) {
	   return false;
	}

	//It must not be a friend declaration
	//For protection (do not have a parent func_dcltr)
	tmp_tree = tree.tree;
	while(tmp_tree != NULL) {
		tmp = tmp_tree;
		do {
			tmp = VTP_TreeLeft(tmp);
		} while(tmp != NULL && 
			    declaration_specifiers != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)));
		if(tmp != NULL) {
			    ITERATOR_MAP(VTP_TreeChild, tmp, child); {
					if(storage_class == VTP_OP_NAME(VTP_TREE_OPERATOR(child)) &&
						friend_op == VTP_NAME_STRING(VTP_TreeAtomValue(child))) {
						return false;
					}
				}
				ITERATOR_END_MAP(VTP_TreeChild);
			break;
		}
		tmp_tree = VTP_TreeUp(tmp_tree);
		if(func_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			return false;
		}
	}

	return true;
}
