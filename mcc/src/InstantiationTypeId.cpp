#include "InstantiationTypeId.h"
#include "TemplateArgumentAsType.h"
#include "ConcreteTableColumn.h"
#include "TypesTable.h"
#include "FindSignature.h"
#include "FindClassContext.h" 
#include "SetOperations.h"

InstantiationTypeId::InstantiationTypeId(DataExtractor *next, ConcreteTableColumn *prototype, TemplateArgumentAsType *condition, TypesTable *types):DataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn *InstantiationTypeId::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::vector<std::string> usedTypes;
	std::string value,mycontext;
	std::string typeName	= "TypeName";
	std::string contextcol	= "Context";
	FindSignature signature;
	FindClassContext context;
	SetOperations set_operation;
	int id;
	char buff[12];

	value = signature.findElement(tree.tree,&usedTypes);
	//We know the instantiation type. Check it's context
	mycontext = context.find(context.find(tree.tree),&usedTypes,types);
	//Find all the types that have the name value
	Table::RowSet *set,*set1,*set2;
	set = types->find_set(typeName,value);
	if(set->size() == 1) {
		id = types->find_id(*set->begin());
		sprintf(buff,"%d",id);
		value = buff;		
		delete set;
	} else {
		set1= types->find_set(contextcol,mycontext);
		set2 = set_operation.intersection_op(set,set1);
		delete set;
		delete set1;
		if(set2->size() == 1) {
			id = types->find_id(*set2->begin());
			sprintf(buff,"%d",id);
			value = buff;
		} else {
			value = "<ERROR>";
		}
		delete set2;
	}
	column->init(value,true);
	return column;
}
