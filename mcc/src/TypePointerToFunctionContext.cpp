#include "TypePointerToFunctionContext.h"
#include "TypesTable.h"
#include "ConcreteTableColumn.h"
#include "ProxyTableColumn.h"
#include "Pointer2Function.h"
#include "FindClassContext.h"
#include "FindPointerToFunctionType.h"

TypePointerToFunctionContext::TypePointerToFunctionContext(DataExtractor *next, ConcreteTableColumn *prototype, Pointer2Function *condition, TypesTable *types):DelayedDataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn* TypePointerToFunctionContext::handleExtraction(AbstractTree &tree) {

	ProxyTableColumn* column;
	IContainer *info = new IContainer();
	FindClassContext context;
	std::string value;
	std::vector<std::string> usedTypes;
	FindPointerToFunctionType p2f;

	//Take the template context
	p2f.find(tree.tree,&usedTypes);
	value = context.find(tree.tree);

	info->push_back(value);
	for(std::vector<std::string>::iterator i = usedTypes.begin(); i != usedTypes.end(); ++i) {
		info->push_back(*i);
	}

	column = new ProxyTableColumn(prototype->getName(),(ConcreteTableColumn*)prototype->clone(),this,info);
	column->init(value,true);
	return column;
}

bool TypePointerToFunctionContext::finalizeExtraction(TableColumn *column, IContainer *info) {

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
