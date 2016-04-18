#include "DecoratedTypeTemplateInstance.h"
#include "TemplateInstance.h"
#include "ConcreteTableColumn.h"
#include "TypesTable.h"
#include "FindChildByName.h"
#include "SetOperations.h"

DecoratedTypeTemplateInstance::DecoratedTypeTemplateInstance(DataExtractor *next, ConcreteTableColumn *prototype, TemplateInstance *condition, TypesTable *types):DelayedDataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn* DecoratedTypeTemplateInstance::handleExtraction(AbstractTree &tree) {

	TableColumn* column;
	IContainer *info = new IContainer();
	VTP_TreeP tmp_tree;
	FindChildByName child_by_name;

	std::string value;

	//Search the class name
	tmp_tree = child_by_name.find(tree.tree,"template_name");
	if(tmp_tree == NULL) {
		tmp_tree = child_by_name.find(tree.tree,"qualified_id");
		tmp_tree = child_by_name.find(tmp_tree,"template_name");
	}
	tmp_tree = child_by_name.find(tmp_tree,"identifier");
	value = VTP_NAME_STRING(VTP_TreeAtomValue(tmp_tree));

	info->push_back(value);

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

bool DecoratedTypeTemplateInstance::finalizeExtraction(TableColumn *column, IContainer *info) {

	std::string name		= (*info)[0];
	std::string isGeneric	= "1";
	std::string value;
	char buff[12];
	int id;

	Table::RowSet *set1,*set2,*set3;
	SetOperations set_operation;

	std::string typeName = "TypeName";
	std::string generic  = "IsGeneric";
	
	//We search a single class with an known name and that is generic				(~OK)
	set1 = types->find_set(typeName,name);
	if(set1->size() == 1) {
		id = types->find_id(*set1->begin());
		sprintf(buff,"%d",id);
		value = buff;
	} else if(set1->size() == 0) {
		delete set1;
		return false;
	} else {
		set2 = types->find_set(generic,isGeneric);
		set3 = set_operation.intersection_op(set1,set2);
		if(set3->size() == 1) {
			id = types->find_id(*set3->begin());
			sprintf(buff,"%d",id);
			value = buff;
		} else {
			value = "<ERROR>";
		}
		delete set2;
		delete set3;
	}

	delete set1;

	column->init(value,false);
	return true;
}
