#include "TypeLibraryName.h"
#include "LibraryType.h"
#include "ConcreteTableColumn.h"

TypeLibraryName::TypeLibraryName(DataExtractor *next, ConcreteTableColumn *prototype, LibraryType *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeLibraryName::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();

	std::string value;

	value = VTP_NAME_STRING(VTP_TreeAtomValue(tree.tree));

	column->init(value,true);

	return column;
}


