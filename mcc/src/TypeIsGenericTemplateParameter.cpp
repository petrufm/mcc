#include "TypeIsGenericTemplateParameter.h"

TypeIsGenericTemplateParameter::TypeIsGenericTemplateParameter(DataExtractor *next, ConcreteTableColumn *prototype, ClassTemplateParameter *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeIsGenericTemplateParameter::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();

	std::string value, template_parameter = "template_parameter";

	if(template_parameter == VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {
		value = "1";
	} else {
		value = "0";
	}

	column->init(value,false);

	return column;
}
