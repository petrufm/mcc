#include "VariableIsStatic.h"
#include "ConcreteTableColumn.h"
#include "VariableDeclaration.h"

VariableIsStatic::VariableIsStatic(DataExtractor *next, ConcreteTableColumn *prototype, VariableDeclaration *condition):DataExtractor(next,prototype,condition) {

	this->cond = condition;

}

TableColumn* VariableIsStatic::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string declaration_specifiers = "declaration_specifiers";
	std::string value;
	VTP_TreeP tmp_tree,tmp;

	value = "<ERROR>";
	tmp_tree = tree.tree;
	while(tmp_tree != NULL) {
		tmp = tmp_tree;
		do {
			tmp = VTP_TreeLeft(tmp);
		} while(tmp != NULL && 
			    declaration_specifiers != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)));
		if(tmp != NULL) {
				if(cond->hasStorageClass(tmp,"static")) {
					value = "1";
				} else {
					value = "0";
				}
				break;
		}
		tmp_tree = VTP_TreeUp(tmp_tree);
	}
	
	column->init(value,false);
	return column;
}
