#include "TemplateInstanceChainsTable.h"
#include "MapAll.h"
#include "ConcreteTableColumn.h"
#include "TemplateArgumentAsTypeInInstance.h"
#include "T2TRelationID.h"
#include "TemplateInstanceID.h"
#include "TypesTable.h"
#include "TemplateParTypesRelation.h"

TemplateInstanceChainsTable::TemplateInstanceChainsTable(char *name, TypesTable *types, TemplateParTypesRelation *t2t):Table(name) {
	
	this->types = types;
	this->t2t = t2t;

}

TemplateInstanceChainsTable::~TemplateInstanceChainsTable() {}

void TemplateInstanceChainsTable::init() {

	buildColumn(std::string("TemplateInstanceID"));
	buildColumn(std::string("T2TRelationId"));

}

void TemplateInstanceChainsTable::extract(ATCollection &trees) {

	MapAll::VectorOfChain myVector;
	MapAll::VectorOfTrigger myTrigger;

	ConcreteTableColumn columnRelationId(std::string("T2TRelationId"),true);
	ConcreteTableColumn columnInstanceId(std::string("TemplateInstanceID"),true);

	TemplateArgumentAsTypeInInstance taCondition;
	myTrigger.push_back(&taCondition);

	T2TRelationID columnRelationIdExtractor0(NULL,&columnRelationId,&taCondition,types,t2t);
	
	TemplateInstanceID columnInstanceIdExtractor0(NULL,&columnInstanceId,&taCondition,types,t2t);
	
	myVector.push_back(&columnInstanceIdExtractor0);
	myVector.push_back(&columnRelationIdExtractor0);

	MapAll element(trees,&myVector,&myTrigger);

	element.accept(this);

	finalize();

}