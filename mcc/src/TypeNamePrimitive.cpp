#include "TypeNamePrimitive.h"

TypeNamePrimitive::TypeNamePrimitive(DataExtractor *next, ConcreteTableColumn *prototype, PrimitiveType *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeNamePrimitive::handleExtraction(AbstractTree &tree) {

	std::string name;
	VTP_TreeP parent,child;
	std::string operatorName = "typespec";

	TableColumn* column = prototype->clone();

	parent = VTP_TreeUp(tree.tree);

    ITERATOR_MAP(VTP_TreeChild, parent, child); {

		if(operatorName == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
			if(!name.empty()) {
				name = name + " " + VTP_NAME_VALUE(VTP_TreeAtomValue(child));
			} else {
				name = VTP_NAME_VALUE(VTP_TreeAtomValue(child));
			}
		}
    }
    ITERATOR_END_MAP(VTP_TreeChild);

	column->init(name,true);

	return column;
}
