#include "AttributeClassId.h"
#include "ConcreteTableColumn.h"
#include "AttributeVariable.h"
#include "TypesTable.h"
#include "FindBaseType.h"
#include "SetOperations.h"

AttributeClassId::AttributeClassId(DataExtractor *next, ConcreteTableColumn *prototype, AttributeVariable *condition, TypesTable *types):DataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn* AttributeClassId::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string class_op	= "class";
	std::vector<std::string> usedTypes;
	std::string value;
	VTP_TreeP tmp_tree;
	FindBaseType base_type;
	SetOperations set_operation;

	std::string typeName	= "TypeName";
	std::string startLine	= "StartPosition";
	std::string fileName	= "FileName";
	std::string name,line;
	char buff[12];
	int id;
	CIO_PositionS start,stop;

	tmp_tree = tree.tree;
	do {
		tmp_tree = VTP_TreeUp(tmp_tree);
	} while(class_op != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)));
	tmp_tree = VTP_TreeUp(tmp_tree);
	name = base_type.find(tmp_tree,&usedTypes);
	tmp_tree = VTP_TreeDown(tmp_tree,0);
	VTP_TreeGetCoord(tmp_tree,&start,&stop);
	sprintf(buff,"%d",start.line);
	line = buff;

	//We seartch after the name,position,line. 
	//It would be better to search after the KindOf field too (but we lose speed)
	Table::RowSet *set1,*set2,*set3;
	set1 = types->find_set(typeName,name);
	set2 = types->find_set(startLine,line);
	set3 = set_operation.intersection_op(set1,set2);
	delete set1;
	delete set2;
	set1 =types->find_set(fileName,tree.file);
	set2 = set_operation.intersection_op(set3,set1);
	delete set1;
	delete set3;
	if(set2->size() == 1) {
		id = types->find_id(*set2->begin());
		sprintf(buff,"%d",id);
		value = buff;
	} else {
		value = "<ERROR>";
	}
	delete set2;
	
	column->init(value,false);
	return column;

}

