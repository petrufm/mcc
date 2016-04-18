#include "PointerToFunctionScopeId.h"
#include "ConcreteTableColumn.h"
#include "Pointer2Function.h"
#include "TypesTable.h"
#include "FindPointerToFunctionType.h"
#include "FindClassContext.h"
#include "SetOperations.h"

PointerToFunctionScopeId::PointerToFunctionScopeId(DataExtractor *next, ConcreteTableColumn *prototype, Pointer2Function *condition, TypesTable *types):DataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn *PointerToFunctionScopeId::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::vector<std::string> usedTypes;
	FindPointerToFunctionType p2f;
	FindClassContext the_context;
	std::string value,mycontext;
	SetOperations set_operation;
	Table::RowSet *set1,*set2,*set3;
	int id;
	char buff[12];

	value = p2f.find(tree.tree,&usedTypes);
	mycontext = the_context.find(the_context.find(tree.tree),&usedTypes,types);

	std::string typeName	= "TypeName";
	std::string kindOf		= "KindOf";
	std::string kindOfVal	= "pointer-to-function";
	std::string	contextCol	= "Context";

	set1 = types->find_set(typeName,value);
	set2 = types->find_set(kindOf,kindOfVal);
	set3 = set_operation.intersection_op(set1,set2);
	delete set1;
	delete set2;
	if(set3->size() == 1) {
		id = types->find_id(*set3->begin());
		sprintf(buff,"%d",id);
		value = buff;
		delete set3;
	} else {
		set1 = types->find_set(contextCol,mycontext);
		set2 = set_operation.intersection_op(set1,set3);
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
	}

	column->init(value,true);
	return column;
}
