#include "TypeIsPrimitive.h"

TypeIsPrimitive::TypeIsPrimitive(DataExtractor *next, ConcreteTableColumn *prototype,PrimitiveType *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeIsPrimitive::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();

	column->init(std::string("primitive"),false);

	return column;
}
