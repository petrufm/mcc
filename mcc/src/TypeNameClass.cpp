#include "TypeNameClass.h"	

TypeNameClass::TypeNameClass(DataExtractor *next, ConcreteTableColumn *prototype, ClassDeclaration *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeNameClass::handleExtraction(AbstractTree &tree) {

	std::string name;
	std::string identifier		= "identifier";
	std::string qualified_id	= "qualified_id";
	std::string none			= "none";
	VTP_TreeP temp;

	if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tree.tree,1)))) {
		//When the definition is "class X {"
		name = VTP_NAME_VALUE(VTP_TreeAtomValue(VTP_TreeDown(tree.tree,1)));
	} else if(qualified_id == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tree.tree,1)))) {
		//When the definition is "class name_space::X {"
		temp = VTP_TreeDown(VTP_TreeDown(tree.tree,1),1);
		name = VTP_NAME_VALUE(VTP_TreeAtomValue(temp));
	} else if(none == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tree.tree,1)))) {
		//When the definition is "class {"
		name = "<ANONYMOUS>";
	} else {
		//When unknown
		name = "ERROR";
	}

	TableColumn *column = prototype->clone();

	column->init(name,false);

	return column;
}

