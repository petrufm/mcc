#include "PointerToFunctionReturnType.h"
#include "ConcreteTableColumn.h"
#include "TypesTable.h"
#include "Pointer2function.h"
#include "FindDecoratedType.h"
#include "FindClassContext.h"
#include "SetOperations.h"

PointerToFunctionReturnType::PointerToFunctionReturnType(DataExtractor *next, ConcreteTableColumn *prototype, Pointer2Function *condition, TypesTable *types):DataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn *PointerToFunctionReturnType::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::vector<std::string> usedTypes;
	VTP_TreeP tmp_tree;
	FindDecoratedType ret_type;
	FindClassContext the_context;
	SetOperations set_operation;

	std::string name,mycontext;
	std::string typeName = "TypeName";
	std::string contextCol = "Context";
	Table::RowSet *set1,*set2,*set3;
	int id;
	char buff[12];

	tmp_tree = VTP_TreeUp(tree.tree);
	name = ret_type.find(tmp_tree,&usedTypes);
	mycontext = the_context.find(the_context.find(tmp_tree),&usedTypes,types);
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

	column->init(name,false);
	return column;
}
