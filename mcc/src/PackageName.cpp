#include "PackageName.h"

PackageName::PackageName(DataExtractor *next, ConcreteTableColumn *prototype,TriggerCondition *condition):DataExtractor(next,prototype,condition) {}

TableColumn* PackageName::handleExtraction(AbstractTree &tree) {

	std::string package, name;
	std::string::size_type pos;

	package = tree.file;
	pos = package.find_last_of("\\");
	if(pos > package.size()) {
		name = ".";
	} else {
		name = package.substr(0,pos);
	}

	TableColumn *column = prototype->clone();

	column->init(name,true);

	return column;
}

