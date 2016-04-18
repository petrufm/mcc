#include "TypeIsDecoratorTypedef.h"
#include "TypedefDecorator.h"
#include "ConcreteTableColumn.h"

TypeIsDecoratorTypedef::TypeIsDecoratorTypedef(DataExtractor *next, ConcreteTableColumn *prototype, TypedefDecorator *condition):DataExtractor(next,prototype,condition) {}
TableColumn* TypeIsDecoratorTypedef::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string value;
	std::string class_decls	= "class_decls";
	std::string fndef		= "fndef";
	VTP_TreeP tmp_tree;

	value = "typedef-decorator";

	tmp_tree = VTP_TreeUp(tree.tree);

	do {
		tmp_tree = VTP_TreeUp(tmp_tree);
	} while(tmp_tree != NULL && class_decls != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) && fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)));

	if(tmp_tree!=NULL && fndef == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		value+="-in-func";
	}

	column->init(value,false);

	return column;

}
