#include "TypeTemplateParameterName.h"
#include "FindBaseType.h"

TypeTemplateParameterName::TypeTemplateParameterName(DataExtractor *next, ConcreteTableColumn *prototype, ClassTemplateParameter *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeTemplateParameterName::handleExtraction(AbstractTree &tree) {

	std::string name;
	VTP_TreeP child;
	std::string class_head		= "class_head";
	std::string identifier		= "identifier";
	std::string typename_id		= "typename_id";
	std::string declaration_specifiers = "declaration_specifiers";
	FindBaseType base_type;
	std::vector<std::string> usedTypes;

	TableColumn* column = prototype->clone();

	child = VTP_TreeDown(tree.tree,0);

	if(class_head == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
		child = VTP_TreeDown(child,1);
		if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
			name = VTP_NAME_VALUE(VTP_TreeAtomValue(child));
		} else {
			name = "<ANONYMOUS>";
		}
	} else if(typename_id == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
		child = VTP_TreeDown(child,0);
		if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
			name = VTP_NAME_VALUE(VTP_TreeAtomValue(child));
		} else {
			name = "<ANONYMOUS>";
		}
	} else if(declaration_specifiers == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
		name = base_type.find(child,&usedTypes);
	} else {
		//It is a template parameter
		child = VTP_TreeDown(VTP_TreeRight(child),1);
		if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
			name = VTP_NAME_VALUE(VTP_TreeAtomValue(child));
		} else {
			name = "<ANONYMOUS>";
		}
	}

	column->init(name,false);

	return column;

}
