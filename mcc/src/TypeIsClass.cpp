#include "TypeIsClass.h"

TypeIsClass::TypeIsClass(DataExtractor *next, ConcreteTableColumn *prototype, ClassDeclaration *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeIsClass::handleExtraction(AbstractTree &tree) {

	std::string name;
	std::string class_decls	= "class_decls";
	std::string fndef		= "fndef";
	VTP_TreeP tmp_tree;

	name = VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tree.tree,0)));

	name = name.substr(0,name.find("_"));

	TableColumn *column = prototype->clone();

	//If it is in function/method it is an in-function-class

	tmp_tree = VTP_TreeUp(tree.tree);

	do {
		tmp_tree = VTP_TreeUp(tmp_tree);
	} while(tmp_tree != NULL && class_decls != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) && fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)));

	if(tmp_tree!=NULL && fndef == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		name+="-in-func";
	}

	column->init(name,false);

	return column;

}

