#include "TypeIsPointerToFunction.h"
#include "ConcreteTableColumn.h"
#include "Pointer2Function.h"

TypeIsPointerToFunction::TypeIsPointerToFunction(DataExtractor *next, ConcreteTableColumn *prototype, Pointer2Function *condition):DataExtractor(next,prototype,condition){};

TableColumn * TypeIsPointerToFunction::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();

	std::string value = "pointer-to-function";

	column->init(value,false);

	return column;
}
