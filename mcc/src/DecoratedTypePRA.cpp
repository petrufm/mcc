#include "DecoratedTypePRA.h"
#include "TypesTable.h"
#include "ConcreteTableColumn.h"
#include "PRADecorator.h"
#include "TableColumn.h"
#include "ProxyTableColumn.h"
#include "FindBaseType.h"
#include "FindChildByName.h"
#include "FindDecoratedType.h"
#include "stdio.h"
#include "SetOperations.h"
#include "FindClassContext.h"

DecoratedTypePRA::DecoratedTypePRA(DataExtractor *next, ConcreteTableColumn *prototype, PRADecorator *condition, TypesTable *types):DelayedDataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn* DecoratedTypePRA::handleExtraction(AbstractTree &tree) {

	ProxyTableColumn* column;
	IContainer *info = new IContainer();

	FindDecoratedType algorithm;
	FindChildByName child_by_name;
	FindBaseType base_type;

	std::string declaration_specifiers = "declaration_specifiers";
	std::string type_specifiers = "type_specifiers";
	std::string type_id = "type_id";

	VTP_TreeP tmp_tree,tmp;

	std::string value,value1;
	std::vector<std::string> usedTypes;

	//Find it's name
	tmp_tree = VTP_TreeUp(tree.tree);
	if((tmp = child_by_name.find(tmp_tree,declaration_specifiers)) != NULL) {
		value = base_type.find(tmp,&usedTypes);
	} else if((tmp = child_by_name.find(tmp_tree,type_specifiers)) != NULL) {
		value = base_type.find(tmp,&usedTypes);
	} else if((tmp = child_by_name.find(tmp_tree,type_id)) != NULL) {
		value = base_type.find(tmp,&usedTypes);
	} else {
		tmp_tree = VTP_TreeUp(tree.tree);
		value = algorithm.find(tmp_tree,&usedTypes);
	}

	if(value == "") {
		value = "<ERROR>";
	}

	FindClassContext context;
	value1 = context.find(tree.tree);

	info->push_back(value);
	info->push_back(value1);
	for(std::vector<std::string>::iterator i = usedTypes.begin(); i != usedTypes.end(); ++i) {
		info->push_back(*i);
	}

	TableColumn *CColumn = prototype->clone();
	if(finalizeExtraction(CColumn,info)) {
		CColumn->init(CColumn->toString(),true);
		delete info;
		return CColumn;
	} else {
		column = new ProxyTableColumn(prototype->getName(),(ConcreteTableColumn*)CColumn,this,info);
		column->init(column->toString(),true);
		return column;
	}
}

bool DecoratedTypePRA::finalizeExtraction(TableColumn *column, IContainer *info) {

	std::string value  = (*info)[0];
	std::string value1 = (*info)[1];
	std::string column_name		= "TypeName";
	std::string column_context	= "Context";
	std::string null = "NULL";
	Table::RowSet *set,*set1,*set2;
	int id;
	char buff[12];
	FindClassContext context;
	SetOperations operations;
	bool decorated_base = false;
	std::vector<std::string> usedTypes;

	if(value.at(value.size()-1) == '*' || value.at(value.size()-1) == ']' || value.at(value.size()-1) == '&') {
		decorated_base = true;
	}

	for(IContainer::iterator i=info->begin()+2; i!=info->end(); ++i) {
		usedTypes.push_back(*i);
	}
	value1 = context.find(value1,&usedTypes,types);

	if(value1 == "<?>") {
		return false;
	} else if(value1 != "<NONE>") {
		//We should find a similar context
		set = types->find_set(column_context,value1);
		set1 = types->find_set(column_name,value);
		set2 = operations.intersection_op(set,set1);
		delete set;
		delete set1;
		if(set2->size() == 1) {
			id = types->find_id(*set2->begin());
			sprintf(buff,"%d",id);
			value = buff;
			column->init(value,true);
			delete set2;
			return true;
		} else {
			delete set2;
			return false;
		}
	} else {
		//The context is not important because this is not in a template class
		set = types->find_set(column_name,value);
		if(set->size() == 1) {
			id = types->find_id(*set->begin());
			sprintf(buff,"%d",id);
			value = buff;
			column->init(value,true);
			delete set;
			return true;
		} else {
			delete set;
			return false;
		}
	}
}
