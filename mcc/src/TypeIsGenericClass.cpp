#include "TypeIsGenericClass.h"

TypeIsGenericClass::TypeIsGenericClass(DataExtractor *next, ConcreteTableColumn *prototype,ClassDeclaration *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeIsGenericClass::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string value, template_def = "template_def";
	std::string class_decls	= "class_decls";
	VTP_TreeP tree_tmp;

	tree_tmp = tree.tree;

	do {
		tree_tmp = VTP_TreeUp(tree_tmp);
	}
	while((tree_tmp != NULL) && 
		  (template_def != VTP_OP_NAME(VTP_TREE_OPERATOR(tree_tmp))) &&
		  (class_decls != VTP_OP_NAME(VTP_TREE_OPERATOR(tree_tmp))));

	if(tree_tmp != NULL && template_def == VTP_OP_NAME(VTP_TREE_OPERATOR(tree_tmp))) {
		value = "1";
	} else {
		value = "0";
	}

	column->init(value,false);

	return column;
}
