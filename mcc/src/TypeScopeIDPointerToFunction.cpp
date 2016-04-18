#include "TypeScopeIDPointerToFunction.h"
#include "Pointer2Function.h"
#include "ConcreteTableColumn.h"
#include "ProxyTableColumn.h"
#include "TypesTable.h"
#include "FindClassContext.h"
#include "SetOperations.h"

TypeScopeIDPointerToFunction::TypeScopeIDPointerToFunction(DataExtractor *next, ConcreteTableColumn *prototype, Pointer2Function *condition, TypesTable *types):DelayedDataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn* TypeScopeIDPointerToFunction::handleExtraction(AbstractTree &tree) {

	ProxyTableColumn* column;
	IContainer *info = new IContainer();
	FindClassContext the_context;
	std::string myContext;
	std::string memptr_dcltr	= "memptr_dcltr";
	std::string scope			= "scope";
	std::string value			= "";
	VTP_TreeP tmp_tree,child;

	tmp_tree = VTP_TreeDown(tree.tree,0);
	if(memptr_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeDown(tmp_tree,0);
		if(scope == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			ITERATOR_MAP(VTP_TreeChild, tmp_tree, child); {
				value = value + VTP_NAME_STRING(VTP_TreeAtomValue(child)) + "::";
			}
			ITERATOR_END_MAP(VTP_TreeChild);
			if(value.at(value.size() - 1) == ':') {
				value = value.substr(0,value.size() - 2);
			}
		}
	}

	myContext = the_context.find(tree.tree);

	info->push_back(value);
	info->push_back(myContext);

	column = new ProxyTableColumn(prototype->getName(),(ConcreteTableColumn*)prototype->clone(),this,info);
	return column;
}

bool TypeScopeIDPointerToFunction::finalizeExtraction(TableColumn *column, IContainer *info) {

	std::string value		= (*info)[0];
	std::string myContext	= (*info)[1];
	std::string name;
	int id;
	char buf[12];

	Table::RowSet *set,*set2,*set3;
	std::string typeName	= "TypeName";
	std::string kindOf		= "KindOf";

	//If there is not any scope then it is a simple pointer to function (OK)
	if(value == "") {
		value = "<NO_ONE>";
		column->init(value,false);
	} else {

		if(value.find_last_of(':') > value.size()) {
			name = value;
		} else {
			name = value.substr(value.find_last_of(':') + 1);
		}

		//Search for the identifier from the scope 
		set = types->find_set(typeName,name);

		//If there is only one then we found the scope					(OK)
		if(set->size() == 1) {
			id = types->find_id(*set->begin());
			sprintf(buf,"%d",id);
			value = buf;
		} else {
		//If there are more than 1 then we will search into this set one that
		//it is in the scope of the left identifier (and so one)
		//This is not yet implemented.

			//First chech to see if this is not a template parameter in this context
			FindClassContext the_context;
			std::vector<std::string> usedTypes;
			std::string contextCol = "Context";
			SetOperations set_operation;

			usedTypes.push_back(name);
			myContext = the_context.find(myContext,&usedTypes,types);
			set2 = types->find_set(contextCol,myContext);
			set3 = set_operation.intersection_op(set,set2);
			delete set2;
			if(set3->size() == 1) {
				id = types->find_id(*set3->begin());
				sprintf(buf,"%d",id);
				value = buf;
			} else {
				value = "<ERROR>";
			}
			delete set3;
		}
			
		delete set;

		column->init(value,false);
	}

	return true;
}
