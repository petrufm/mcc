#include "TypeTemplateInstanceContext.h"
#include "TypesTable.h"
#include "ConcreteTableColumn.h"
#include "ProxyTableColumn.h"
#include "TemplateInstance.h"
#include "FindClassContext.h"
#include "FindBaseType.h"

TypeTemplateInstanceContext::TypeTemplateInstanceContext(DataExtractor *next, ConcreteTableColumn *prototype, TemplateInstance *condition, TypesTable *types):DelayedDataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn* TypeTemplateInstanceContext::handleExtraction(AbstractTree &tree) {

	ProxyTableColumn* column;
	IContainer *info = new IContainer();
	FindClassContext context;
	std::string value;
	std::vector<std::string> usedTypes;

	//Take the template context
	FindBaseType base_type;
	base_type.find(tree.tree,&usedTypes);
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

bool TypeTemplateInstanceContext::finalizeExtraction(TableColumn *column, IContainer *info) {

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