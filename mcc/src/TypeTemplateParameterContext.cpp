#include "TypeTemplateParameterContext.h"
#include "ConcreteTableColumn.h"
#include "ClassTemplateParameter.h"

TypeTemplateParameterContext::TypeTemplateParameterContext(DataExtractor *next, ConcreteTableColumn *prototype, ClassTemplateParameter *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeTemplateParameterContext::handleExtraction(AbstractTree &tree) {

	TableColumn* column = prototype->clone();

	std::string value;
	std::string identifier = "identifier";
	VTP_TreeP tmp_tree;

	tmp_tree = VTP_TreeDown(VTP_TreeDown(VTP_TreeDown(VTP_TreeDown(VTP_TreeRight(VTP_TreeUp(tree.tree)),0),0),0),1);

	if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		value = VTP_NAME_VALUE(VTP_TreeAtomValue(tmp_tree));
	} else {
		value = "<ANONYMOUS>";
	}

	column->init(value,false);
	
	return column;
}

