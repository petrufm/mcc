#include "FindChildByName.h"

VTP_TreeP FindChildByName::find(VTP_TreeP &tree,std::string name) {

	VTP_TreeP child;

    ITERATOR_MAP(VTP_TreeChild, tree, child); {
	if(name == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) return child;
	}
	ITERATOR_END_MAP(VTP_TreeChild);
	return NULL;
}
