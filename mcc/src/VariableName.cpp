#include "VariableName.h"
#include "ConcreteTableColumn.h"
#include "VariableDeclaration.h"

VariableName::VariableName(DataExtractor *next, ConcreteTableColumn *prototype, VariableDeclaration *condition):DataExtractor(next,prototype,condition) {}

TableColumn* VariableName::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string identifier	 = "identifier";
	std::string qualified_id = "qualified_id";
	std::string op,name;
	VTP_TreeP tmp_tree;

	tmp_tree = tree.tree;
	op = VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree));
	while(op != identifier) {
		if(op == "qualified_id") {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		} else if(op == "func_dcltr") {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		} else if(op == "array_dcltr") {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		} else if(op == "ptr_dcltr") {
			tmp_tree = VTP_TreeDown(tmp_tree,1);
		} else if(op == "ref_dcltr") {
			tmp_tree = VTP_TreeDown(tmp_tree,1);
		} else if(op == "memptr_dcltr") {
			tmp_tree = VTP_TreeDown(tmp_tree,2);
		} else if(op == "parenth_dcltr") {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		} else if(op == "dcltr_noinit") {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		} else if(op == "dcltr_affinit") {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		} else if(op == "dcltr_callinit") {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		} else {
			break;
		}
		op = VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree));
	}
	if(op == identifier) {
		name = VTP_NAME_STRING(VTP_TreeAtomValue(tmp_tree));
	} else {
		name = "<NO_NAME>";
	}
	column->init(name,false);
	return column;
}
