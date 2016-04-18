#include "TypeIsDecoratorTemplateInstance.h"
#include "TemplateInstance.h"
#include "ConcreteTableColumn.h"

TypeIsDecoratorTemplateInstance::TypeIsDecoratorTemplateInstance(DataExtractor *next, ConcreteTableColumn *prototype, TemplateInstance *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeIsDecoratorTemplateInstance::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string value;

	value = "template-instance";

	column->init(value,false);

	return column;

}

