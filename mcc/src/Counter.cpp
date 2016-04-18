#include "Counter.h"
#include "ConcreteTableColumn.h"
#include "TriggerCondition.h"

Counter::Counter(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition) : DataExtractor(next,prototype,condition) {}

TableColumn* Counter::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string value = "1";

	column->init(value,false,1,TableColumn::MergeByAdd);

	return column;
	
}

