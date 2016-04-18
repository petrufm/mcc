#include "PointerToFunctionSignature.h"
#include "ConcreteTableColumn.h"
#include "Pointer2Function.h"
#include "FindSignature.h"

PointerToFunctionSignature::PointerToFunctionSignature(DataExtractor *next, ConcreteTableColumn *prototype, Pointer2Function *condition):DataExtractor(next,prototype,condition) {}

TableColumn *PointerToFunctionSignature::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::vector<std::string> usedTypes;
	FindSignature signature;
	std::string value;
	VTP_TreeP tmp_tree;

	tmp_tree = VTP_TreeRight(tree.tree);

	value = signature.find(tmp_tree,&usedTypes);
	column->init(value,false);
	return column;
}

