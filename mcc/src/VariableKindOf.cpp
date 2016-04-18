#include "VariableKindOf.h"
#include "ConcreteTableColumn.h"
#include "VariableDeclaration.h"

VariableKindOf::VariableKindOf(DataExtractor *next, ConcreteTableColumn *prototype, VariableDeclaration *condition):DataExtractor(next,prototype,condition) {

	this->cond = condition;
}

TableColumn* VariableKindOf::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string name;

	name = cond->getIndentifierString();

	column->init(name,false);
	return column;

}


