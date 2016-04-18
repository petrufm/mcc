#include "ColumnMarker.h"
#include "ConcreteTableColumn.h"
#include "TriggerCondition.h"

ColumnMarker::ColumnMarker(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition):DataExtractor(next,prototype,condition) {}

TableColumn* ColumnMarker::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string value = "<MARKER>";
	column->init(value,false);
	return column;
}
