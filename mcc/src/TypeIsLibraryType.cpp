#include "TypeIsLibraryType.h"
#include "LibraryType.h"
#include "ConcreteTableColumn.h"

TypeIsLibraryType::TypeIsLibraryType(DataExtractor *next, ConcreteTableColumn *prototype, LibraryType *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeIsLibraryType::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string value;

	value = "library-type";
	column->init(value,false);

	return column;

}

