#include "AttributeAccess.h"
#include "ConcreteTableColumn.h"
#include "AttributeVariable.h"

AttributeAccess::AttributeAccess(DataExtractor *next, ConcreteTableColumn *prototype, AttributeVariable *condition):DataExtractor(next,prototype,condition) {}

TableColumn* AttributeAccess::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string class_op			= "class";
	std::string class_decls_section	= "class_decls_section";
	std::string access_specifier	= "access_specifier";
	std::string class_kw			= "class_kw";
	std::string value;
	VTP_TreeP tmp_tree;

	tmp_tree = tree.tree;
	do {
		tmp_tree = VTP_TreeUp(tmp_tree);
	} while(class_decls_section != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)));

	if(class_decls_section == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
		access_specifier == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree = VTP_TreeDown(tmp_tree,0)))) {
		value = VTP_NAME_STRING(VTP_TreeAtomValue(tmp_tree));
	} else {
		do {
			tmp_tree = VTP_TreeUp(tmp_tree);
		} while(class_op != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)));
		tmp_tree = VTP_TreeDown(VTP_TreeDown(tmp_tree,0),0);
		if(class_kw == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			value = "private";
		} else {
			value = "public";
		}
	}
	column->init(value,false);
	return column;

}

