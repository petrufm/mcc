#include "T2TRelationID.h"
#include "TemplateArgumentAsTypeInInstance.h"
#include "ConcreteTableColumn.h"
#include "TypesTable.h"
#include "TemplateParTypesRelation.h"
#include "TemplateParameterId.h"
#include "InstantiationTypeId.h"
#include "SetOperations.h"

T2TRelationID::T2TRelationID(DataExtractor *next, ConcreteTableColumn *prototype, TemplateArgumentAsTypeInInstance *condition, TypesTable *types, TemplateParTypesRelation *t2t):DataExtractor(next,prototype,condition) {

	this->t2t = t2t;
	this->types = types;
	this->tmp_tpId = new TemplateParameterId(NULL,prototype,NULL,types);
	this->tmp_itId = new InstantiationTypeId(NULL,prototype,NULL,types);

}

T2TRelationID::~T2TRelationID() {

	delete tmp_tpId;
	delete tmp_itId;

}

TableColumn* T2TRelationID::handleExtraction(AbstractTree &tree) {

	TableColumn *column,*column1;
	Table::RowSet *set1,*set2,*set3;
	std::string tpId = "TemplateParameterId";
	std::string itId = "InstantiationTypeId";
	std::string value;
	SetOperations set_operation;
	int id;
	char buff[12];

	column = tmp_tpId->extract(tree);
	column1 = tmp_itId->extract(tree);

	set1 = t2t->find_set(tpId,column->toString());
	set2 = t2t->find_set(itId,column1->toString());
	set3 = set_operation.intersection_op(set1,set2);
	if(set3->size() == 1) {
		id = t2t->find_id(*set3->begin());
		sprintf(buff,"%d",id);
		value = buff;
	} else {
		value = "<ERROR>";
	}
	delete set1;
	delete set2;
	delete set3;
	delete column1;
	column->init(value,true);
	return column;
}
