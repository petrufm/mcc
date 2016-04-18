#include "InheritanceDescendent.h"
#include "ConcreteTableColumn.h"
#include "InheritanceRelation.h"
#include "FindBaseType.h"
#include "SetOperations.h"
#include "TypesTable.h"

InheritanceDescendent::InheritanceDescendent(DataExtractor *next, ConcreteTableColumn *prototype, InheritanceRelation *condition, TypesTable *types) : DataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn* InheritanceDescendent::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::vector<std::string> usedTypes;
	std::string class_head = "class_head";
	std::string name;
	FindBaseType base_type;
	VTP_TreeP tmp_tree;
	CIO_PositionS start,stop;
	Table::RowSet *set1,*set2,*set3;
	SetOperations set_operation;
	int id;
	char buff[12];

	tmp_tree = tree.tree;
	while(class_head != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeUp(tmp_tree);
	}
	
	std::string kind1 = "class";
	std::string kind2 = "struct";
	std::string kind3 = "union";
	std::string kind4 = "class-in-func";
	std::string kind5 = "struct-in-func";
	std::string kind6 = "union-in-func";
	std::string typeName	  = "TypeName";
	std::string kindOf		  = "KindOf";
	std::string startPosition = "StartPosition";
	std::string fileName	  = "FileName";
	std::string start_val;

	name = base_type.find(tmp_tree,&usedTypes);
	VTP_TreeGetCoord(tmp_tree,&start,&stop);
	sprintf(buff,"%d",start.line);
	start_val = buff;

	//This is too time consuming
	//set1 = types->find_set(kindOf,kind1);
	//set2 = types->find_set(kindOf,kind2);
	//posible = set_operation.union_op(set1,set2);
	//delete set1;
	//delete set2;
	//set1 = types->find_set(kindOf,kind3);
	//set2 = set_operation.union_op(posible,set1);
	//delete set1;
	//delete posible;
	//posible = set2;
	//set1 = types->find_set(kindOf,kind4);
	//set2 = set_operation.union_op(posible,set1);
	//delete set1;
	//delete posible;
	//posible = set2;
	//set1 = types->find_set(kindOf,kind5);
	//set2 = set_operation.union_op(posible,set1);
	//delete set1;
	//delete posible;
	//posible = set2;
	//set1 = types->find_set(kindOf,kind6);
	//set2 = set_operation.union_op(posible,set1);
	//delete set1;
	//delete posible;
	//posible = set2;
	
	//Posible contains classes,struct,or unions
	set1 = types->find_set(typeName,name);
	//set2 = set_operation.intersection_op(set1,posible);
	//delete set1;
	//delete posible;
	set2 = types->find_set(fileName,tree.file);
	set3 = set_operation.intersection_op(set1,set2);
	delete set1;
	delete set2;
	set1 = types->find_set(startPosition,start_val);
	set2 = set_operation.intersection_op(set1,set3);
	delete set1;
	delete set3;
	if(set2->size() == 1) {
		id = types->find_id(*set2->begin());
		sprintf(buff,"%d",id);
		name = buff;
	} else {
		name = "<ERROR>";
	}
	delete set2;
	
	column->init(name,false);
	return column;
}
