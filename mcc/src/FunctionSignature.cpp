#include "FunctionSignature.h"
#include "FuncDeclaration.h"
#include "ConcreteTableColumn.h"
#include "FindSignature.h"

FunctionSignature::FunctionSignature(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition):DataExtractor(next,prototype,condition){};

TableColumn* FunctionSignature::handleExtraction(AbstractTree &tree) {
	
	TableColumn *column = prototype->clone();
	std::string value;
	VTP_TreeP tmp_tree;
	std::vector<std::string> usedTypes;
	FindSignature sig;

	tmp_tree = VTP_TreeDown(tree.tree,1);
	value = sig.find(tmp_tree,&usedTypes);

	column->init(value,true);
	return column;
}