#include "MethodDeclaration.h"

bool MethodDeclaration::isTriggered(AbstractTree &tree) {


	std::string class_decls = "class_decls";
	VTP_TreeP tmp_tree;

	if(!funcDecl.isTriggered(tree)) {
		return false;
	}

	//It must be in a class declaration
	tmp_tree = tree.tree;
	do {
		tmp_tree = VTP_TreeUp(tmp_tree);
	} while(tmp_tree != NULL &&
			class_decls != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)));
	if(tmp_tree == NULL) {
		return false;
	}

	return true;
}
