#include "TypePRAContext.h"
#include "TypesTable.h"
#include "ConcreteTableColumn.h"
#include "ProxyTableColumn.h"
#include "PRADecorator.h"
#include "FindClassContext.h"
#include "FindDecoratedType.h"
#include "FindChildByName.h"
#include "FindBaseType.h"

TypePRAContext::TypePRAContext(DataExtractor *next, ConcreteTableColumn *prototype, PRADecorator *condition, TypesTable *types):DelayedDataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn* TypePRAContext::handleExtraction(AbstractTree &tree) {

	ProxyTableColumn* column;
	IContainer *info = new IContainer();
	FindClassContext context;
	std::string value;

	std::string declaration_specifiers	= "declaration_specifiers";
	std::string type_specifiers			= "type_specifiers";
	std::string type_id					= "type_id";

	FindDecoratedType algorithm;
	FindChildByName child_by_name;
	FindBaseType base_type;
	std::vector<std::string> usedTypes;

	VTP_TreeP tmp_tree,tmp;
	
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

	//Take the template context
	value = context.find(tree.tree);

	info->push_back(value);
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

bool TypePRAContext::finalizeExtraction(TableColumn *column, IContainer *info) {

	std::string value = (*info)[0];
	FindClassContext context;
	std::vector<std::string> usedTypes;

	for(IContainer::iterator i=info->begin()+1; i!=info->end(); ++i) {
		usedTypes.push_back(*i);
	}

	value = context.find(value,&usedTypes,types);

	if(value == "<?>") {
		return false;
	}

	column->init(value,true);
	return true;
}
