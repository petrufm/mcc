#include "TypeDecoratorTypedefName.h"
#include "TypedefDecorator.h"
#include "ConcreteTableColumn.h"

TypeDecoratorTypedefName::TypeDecoratorTypedefName(DataExtractor *next, ConcreteTableColumn *prototype, TypedefDecorator *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeDecoratorTypedefName::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string value;
	
	value = VTP_NAME_STRING(VTP_TreeAtomValue(tree.tree));

	column->init(value,false);

	return column;

}
