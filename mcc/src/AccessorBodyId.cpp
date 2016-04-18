#include "AccessorBodyId.h"
#include "ConcreteTableColumn.h"
#include "Accessto.h"
#include "SetOperations.h"
#include "BodyTable.h"
#include "VisitProgressObserver.h"

AccessorBodyId::AccessorBodyId(DataExtractor *next, ConcreteTableColumn *prototype, AccessTo *condition, BodyTable *bodies) : DataExtractor(next,prototype,condition) {

	this->bodies = bodies;
	reset = true;

}

void AccessorBodyId::notifyGoUp(VTP_TreeP &tree) {
	if(!strcmp(VTP_OP_NAME(VTP_TREE_OPERATOR(tree)),"fndef")) {
		reset = true;
	}
}

void AccessorBodyId::notifyGoDown(VTP_TreeP &tree) {
	if(!strcmp(VTP_OP_NAME(VTP_TREE_OPERATOR(tree)),"fndef")) {
		reset = true;
	}
}

TableColumn* AccessorBodyId::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string fndef				= "fndef";
	std::string compound			= "compound";
	std::string ctor_initializer	= "ctor_initializer";
	std::string	value;

	VTP_TreeP tmp_tree;

	if(!reset) {
	
		value = last_bodyId;
	
	} else {

		tmp_tree = tree.tree;
		while(fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			tmp_tree = VTP_TreeUp(tmp_tree);
		}
		tmp_tree = VTP_TreeDown(tmp_tree,3);
		if(compound != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			if(ctor_initializer == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
				tmp_tree = VTP_TreeDown(tmp_tree,1);
			} else {
				value = "<ERROR>";
				column->init(value,false);
				reset = true;
				return column;
			}
		}

		Table::RowSet *set1,*set2,*set3;
		std::string fileName	= "FileName";
		std::string startLine	= "StartLine";
		SetOperations set_operator;
		int id;
		char buff[12];
		CIO_PositionS start;
		CIO_PositionS stop;

		VTP_TreeGetCoord(tmp_tree,&start,&stop);
		set1 = bodies->find_set(fileName,tree.file);
		sprintf(buff,"%d",start.line);
		value = buff;
		set2 = bodies->find_set(startLine,value);
		set3 = set_operator.intersection_op(set1,set2);
		delete set1;
		delete set2;
		if(set3->size() == 1) {
			id = bodies->find_id(*set3->begin());
			sprintf(buff,"%d",id);
			value = buff;
			last_bodyId = value;
			reset = false;
		} else {
			value = "<ERROR>";
			reset = true;
		}
		delete set3;
	}

	column->init(value,true);
	return column;

}