#include "TypePointerToFunctionName.h"
#include "ConcreteTableColumn.h"
#include "Pointer2Function.h"
#include "FindPointerToFunctionType.h"

TypePointerToFunctionName::TypePointerToFunctionName(DataExtractor *next, ConcreteTableColumn *prototype, Pointer2Function *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypePointerToFunctionName::handleExtraction(AbstractTree &tree) {

	TableColumn* column = prototype->clone();
	FindPointerToFunctionType p2f;
	std::vector<std::string> usedTypes;

	column->init(p2f.find(tree.tree,&usedTypes),true);

	return column;
}

