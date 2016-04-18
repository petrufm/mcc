#include "TypeLibraryIsGeneric.h"
#include "ConcreteTableColumn.h"
#include "LibraryType.h"

TypeLibraryIsGeneric::TypeLibraryIsGeneric(DataExtractor *next, ConcreteTableColumn *prototype, LibraryType *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeLibraryIsGeneric::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string template_name = "template_name";
	std::string value;
	int priority;

	VTP_TreeP tmp_tree = VTP_TreeUp(tree.tree);
	value = VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree));
	if(template_name == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		value = "1";
		priority = 1;
	} else {
		value = "0";
		priority = 0;
	}

	column->init(value,false,priority,TableColumn::MergeByCopy);
	return column;
}
