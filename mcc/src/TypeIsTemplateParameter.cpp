#include "TypeIsTemplateParameter.h"

TypeIsTemplateParameter::TypeIsTemplateParameter(DataExtractor *next, ConcreteTableColumn *prototype,ClassTemplateParameter *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeIsTemplateParameter::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();

	column->init(std::string("template-par"),false);

	return column;
}
