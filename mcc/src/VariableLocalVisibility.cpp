#include "VariableLocalVisibility.h"
#include "ConcreteTableColumn.h"
#include "LocalVariable.h"

VariableLocalVisibility::VariableLocalVisibility(DataExtractor *next, ConcreteTableColumn *prototype, LocalVariable *condition) : DataExtractor(next,prototype,condition) {}

TableColumn* VariableLocalVisibility::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string handler = "handler";
	std::string compound= "compound";
	std::string value;
	char buff[12];
	CIO_PositionS start;
	CIO_PositionS stop;
	int st,en;

	VTP_TreeP tmp_tree = tree.tree;

	VTP_TreeGetCoord(tmp_tree,&start,&stop);
	st = stop.rank;

	while(handler != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
		compound!= VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeUp(tmp_tree);
	}

	VTP_TreeGetCoord(tmp_tree,&start,&stop);
	en = stop.rank;

	sprintf(buff,"%d %d",st,en);
	value = buff;
	column->init(value,false);
	return column;
}
