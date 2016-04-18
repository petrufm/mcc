#include "TypeDecoratorTemplateInstanceName.h"
#include "FindBaseType.h"
#include "TemplateInstance.h"
#include "ConcreteTableColumn.h"

TypeDecoratorTemplateInstanceName::TypeDecoratorTemplateInstanceName(DataExtractor *next, ConcreteTableColumn *prototype, TemplateInstance *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeDecoratorTemplateInstanceName::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	FindBaseType base_type;
	std::string value;
	std::vector<std::string> usedTypes;

	value = base_type.find(tree.tree,&usedTypes);
	
	column->init(value,true);
	return column;
}
