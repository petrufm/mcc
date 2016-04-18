#include "FunctionIsStatic.h"
#include "ConcreteTableColumn.h"
#include "FuncDeclaration.h"

FunctionIsStatic::FunctionIsStatic(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition):DataExtractor(next,prototype,condition) {};

TableColumn* FunctionIsStatic::handleExtraction(AbstractTree &tree) {
	
	TableColumn *column = prototype->clone();
	std::string declaration_specifiers	= "declaration_specifiers";
	std::string storage_class			= "storage_class";
	std::string static_op				= "static";
	std::string value;
	VTP_TreeP tmp_tree,tmp,child;

	value = "0";
	tmp_tree = tree.tree;
	while(tmp_tree != NULL) {
		tmp = tmp_tree;
		do {
			tmp = VTP_TreeLeft(tmp);
		} while(tmp != NULL && 
			    declaration_specifiers != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)));
		if(tmp != NULL) {
			    ITERATOR_MAP(VTP_TreeChild, tmp, child); {
					if(storage_class == VTP_OP_NAME(VTP_TREE_OPERATOR(child)) &&
						static_op == VTP_NAME_STRING(VTP_TreeAtomValue(child))) {
						value = "1";
					}
				}
				ITERATOR_END_MAP(VTP_TreeChild);
				break;
		}
		tmp_tree = VTP_TreeUp(tmp_tree);
	}

	column->init(value,false);
	return column;
}