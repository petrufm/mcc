#include "VariableType.h"
#include "ConcreteTableColumn.h"
#include "VariableDeclaration.h"
#include "FindSignature.h"
#include "SetOperations.h"
#include "FindClassContext.h"
#include "TypesTable.h"

VariableType::VariableType(DataExtractor *next, ConcreteTableColumn *prototype, VariableDeclaration *condition, TypesTable *types):DataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn* VariableType::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::vector<std::string> usedTypes;
	FindSignature type;
	FindClassContext the_context;
	SetOperations set_operation;
	std::string name,mycontext;
	std::string typeName = "TypeName";
	std::string contextCol = "Context";
	Table::RowSet *set1,*set2,*set3;
	int id;
	char buff[12];

	//Check for return type
	name = type.findVariable(tree.tree,&usedTypes);
	
	//Check for ID
	if(name != "") {
		mycontext = the_context.find(the_context.find(tree.tree),&usedTypes,types);
		set1 = types->find_set(typeName,name);
		if(set1->size() == 1) {
			id = types->find_id(*set1->begin());
			sprintf(buff,"%d",id);
			name = buff;
			delete set1;
		} else {
			set2 = types->find_set(contextCol,mycontext);
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
	} else {
		name = "<NO_ONE>";
	}
	column->init(name,false);
	return column;
}
