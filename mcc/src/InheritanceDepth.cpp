#include "InheritanceDepth.h"
#include "ConcreteTableColumn.h"
#include "InheritanceRelation.h"

InheritanceDepth::InheritanceDepth(DataExtractor *next, ConcreteTableColumn *prototype, InheritanceRelation *condition) : DataExtractor(next,prototype,condition) {}

TableColumn* InheritanceDepth::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string value;

	value = "1";

	column->init(value,false);
	return column;
}