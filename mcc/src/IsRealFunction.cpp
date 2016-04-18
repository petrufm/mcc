#include "IsRealFunction.h"
#include "ConcreteTableColumn.h"
#include "FuncDeclaration.h"

IsRealFunction::IsRealFunction(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition):DataExtractor(next,prototype,condition){};

TableColumn* IsRealFunction::handleExtraction(AbstractTree &tree) {
	
	TableColumn *column = prototype->clone();
	std::string value;

	value = "real-function";

	column->init(value,true);
	return column;
}
