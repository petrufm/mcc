#include "FunctionBodyId.h"
#include "ConcreteTableColumn.h"
#include "FuncDeclaration.h"
#include "BodyTable.h"
#include "FindChildByName.h"
#include "SetOperations.h"

FunctionBodyId::FunctionBodyId(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition, BodyTable *body):DataExtractor(next,prototype,condition) {

	this->body = body;

};

TableColumn* FunctionBodyId::handleExtraction(AbstractTree &tree) {
	
	TableColumn *column = prototype->clone();
	std::string fndef			= "fndef";
	std::string dcltr_noinit	= "dcltr_noinit";
	std::string dcltr_affinit	= "dcltr_affinit";
	std::string class_op		= "class";
	std::string compound		= "compound";
	std::string ctor_initializer= "ctor_initializer";
	std::string value;
	int level = 0;
	VTP_TreeP tmp_tree;

	tmp_tree = tree.tree;
	do {
		tmp_tree = VTP_TreeUp(tmp_tree);
	} while(tmp_tree != NULL &&
			class_op != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
			fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
			dcltr_noinit != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
			dcltr_affinit != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)));

	if(tmp_tree == NULL || 
	   class_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) ||
	   dcltr_noinit == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		value = "<ONLY_DECLARED>";
		level = 0;
	} else if(dcltr_affinit == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		value = "<INIT_NULL_BODY>";
		level = 1;
	} else if(fndef == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		Table::RowSet *set1,*set2,*set3;
		std::string fileName = "FileName";
		std::string startLine = "StartLine";
		FindChildByName child;
		SetOperations set_operator;
		int id;
		char buff[12];
		CIO_PositionS start;
		CIO_PositionS stop;

		tmp_tree = VTP_TreeDown(tmp_tree,3);
		if(ctor_initializer == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))){
			tmp_tree = child.find(tmp_tree,"compound");
		}
		if(tmp_tree != NULL && compound == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			VTP_TreeGetCoord(tmp_tree,&start,&stop);
			sprintf(buff,"%d",start.line);
			value = buff;
			set1 = body->find_set(fileName,tree.file);
			set2 = body->find_set(startLine,value);
			set3 = set_operator.intersection_op(set1,set2);
			delete set1;
			delete set2;
			if(set3->size() == 1) {
				id = body->find_id(*set3->begin());
				sprintf(buff,"%d",id);
				value = buff;
				level = 1;
			} else {
				value = "<ERROR>";
				level = 0;
			}
			delete set3;
		} else {
			value = "<ERROR>";
			level = 0;
		}
	}
	column->init(value,false,level,TableColumn::MergeByCopy);
	return column;
}
