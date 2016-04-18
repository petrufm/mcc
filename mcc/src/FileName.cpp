#include "FileName.h"

FileName::FileName(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition):DataExtractor(next,prototype,condition) {}

TableColumn* FileName::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	column->init(tree.file,false);
	return column;

}
