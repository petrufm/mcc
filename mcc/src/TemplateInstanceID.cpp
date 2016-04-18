#include "TemplateInstanceID.h"
#include "TemplateArgumentAsTypeInInstance.h"
#include "ConcreteTableColumn.h"
#include "TypesTable.h"
#include "TemplateParTypesRelation.h"
#include "FindBaseType.h"
#include "FindClassContext.h"
#include "SetOperations.h"

TemplateInstanceID::TemplateInstanceID(DataExtractor *next, ConcreteTableColumn *prototype, TemplateArgumentAsTypeInInstance *condition, TypesTable *types, TemplateParTypesRelation *t2t):DataExtractor(next,prototype,condition) {

	this->t2t = t2t;
	this->types = types;

}

TableColumn* TemplateInstanceID::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	VTP_TreeP tmp_tree;
	std::string value,contextValue;
	std::string typeName	= "TypeName";
	std::string context		= "Context";
	std::vector<std::string> usedTypes;
	FindBaseType base_type;
	FindClassContext mycontext;
	SetOperations set_operation;
	int id;
	char buff[12];

	tmp_tree = tree.tree;
	tmp_tree = VTP_TreeUp(VTP_TreeUp(VTP_TreeUp(tmp_tree)));
	value = base_type.find(tmp_tree,&usedTypes);
	contextValue = mycontext.find(mycontext.find(tree.tree),&usedTypes,types);
	
	Table::RowSet *set1,*set2,*set3;
	set1 = types->find_set(typeName,value);
	if(set1->size() == 1) {
		id = types->find_id(*set1->begin());
		sprintf(buff,"%d",id);
		value = buff;
		delete set1;
	} else {
		set2 = types->find_set(context,contextValue);
		set3 = set_operation.intersection_op(set1,set2);
		if(set3->size() == 1) {
			id = types->find_id(*set3->begin());
			sprintf(buff,"%d",id);
			value = buff;
		} else {
			value = "<ERROR>";
		}
		delete set1;
		delete set2;
		delete set3;
	}
	column->init(value,true);
	return column;
}
