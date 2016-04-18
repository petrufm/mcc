#include "InheritanceRelation.h"

bool InheritanceRelation::isTriggered(AbstractTree &tree) {

	std::string base_class  = "base_class";
	std::string class_head  = "class_head";
	std::string class_decls = "class_decls";
	VTP_TreeP tmp_tree;

	if(base_class != VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {
		return false;
	}

	tmp_tree = tree.tree;
	while(class_head != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeUp(tmp_tree);
	}

	tmp_tree = VTP_TreeRight(tmp_tree);

	if(class_decls != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return false;
	}

	return true;
}

