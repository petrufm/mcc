#include "InheritanceAccess.h"
#include "ConcreteTableColumn.h"
#include "InheritanceRelation.h"

InheritanceAccess::InheritanceAccess(DataExtractor *next, ConcreteTableColumn *prototype, InheritanceRelation *condition) : DataExtractor(next,prototype,condition) {}

TableColumn* InheritanceAccess::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string access_specifier= "access_specifier";
	std::string class_head		= "class_head";
	std::string class_kw		= "class_kw";
	std::string value;
	VTP_TreeP tmp_tree,child;

	value = "";
	tmp_tree = VTP_TreeDown(tree.tree,0);
	ITERATOR_MAP(VTP_TreeChild, tmp_tree, child); {
		if(access_specifier == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
			value = VTP_NAME_STRING(VTP_TreeAtomValue(child));
		}
	}
	ITERATOR_END_MAP(VTP_TreeChild);
	if(value == "") {
		tmp_tree = tree.tree;
		while(class_head != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			tmp_tree = VTP_TreeUp(tmp_tree);
		}
		tmp_tree = VTP_TreeDown(tmp_tree,0);
		if(class_kw == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			value = "private";
		} else {
			value = "public";
		}
	}

	column->init(value,false);
	return column;
}
