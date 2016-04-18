#include "InheritanceParent.h"
#include "ConcreteTableColumn.h"
#include "InheritanceRelation.h"
#include "FindBaseType.h"
#include "TypesTable.h"
#include "SetOperations.h"
#include "FindClassContext.h"

InheritanceParent::InheritanceParent(DataExtractor *next, ConcreteTableColumn *prototype, InheritanceRelation *condition, TypesTable *types) : DataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn* InheritanceParent::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::vector<std::string> usedTypes;
	VTP_TreeP tmp_tree;
	FindBaseType base_type;
	std::string name;
	Table::RowSet *set1,*set2,*set3;
	SetOperations set_operation;
	int id;
	char buff[12];

	tmp_tree = tree.tree;
	name = base_type.find(tmp_tree,&usedTypes);
	
	//THIS IS ONLY A TEMPORARY PATCH
	//A PARENTH CLASS Template<int> IS NOT SEEN AS A CLASS
	name = name.substr(0,name.find_first_of('<'));
	//END OF THE PATCH
	
	std::string typeName	  = "TypeName";
	std::string kindOf		  = "KindOf";

	set2 = types->find_set(typeName,name);
	if(set2->size() == 1) {
		id = types->find_id(*set2->begin());
		sprintf(buff,"%d",id);
		name = buff;
		delete set2;
	} else if(set2->size() == 0) {
		name = "<ERROR>";
		delete set2;
	} else {
		//Take the context into account
		std::string contextCol = "Context";
		std::string myContext;
		FindClassContext the_context;
		myContext = the_context.find(the_context.find(tmp_tree),&usedTypes,types);
		set1 = types->find_set(contextCol,myContext);
		set3 = set_operation.intersection_op(set1,set2);
		delete set1;
		delete set2;
		if(set3->size() == 1) {
			id = types->find_id(*set3->begin());
			sprintf(buff,"%d",id);
			name = buff;
		} else {
			name = "<ERROR>";
		}
		delete set3;
	}

	column->init(name,false);
	return column;
}