#include "TemplateParTypesRelation.h"
#include "TypesTable.h"
#include "ConcreteTableColumn.h"
#include "TemplateArgumentAsType.h"
#include "MapAll.h"
#include "InstantiationTypeId.h"
#include "TemplateParameterId.h"

TemplateParTypesRelation::TemplateParTypesRelation(char *name, TypesTable *types):Table(name) {

	this->types = types;

}

TemplateParTypesRelation::~TemplateParTypesRelation() {}

void TemplateParTypesRelation::init() {
	buildColumn(std::string("TemplateParameterId"));
	buildColumn(std::string("InstantiationTypeId"));
}

void TemplateParTypesRelation::extract(ATCollection &trees) {

	MapAll::VectorOfChain myVector;
	MapAll::VectorOfTrigger myTrigger;

	ConcreteTableColumn columnTemplateParameterId(std::string("TemplateParameterId"),true);
	ConcreteTableColumn columnInstatiationTypeId(std::string("InstantiationTypeId"),true);

	TemplateArgumentAsType taCondition;
	myTrigger.push_back(&taCondition);

	TemplateParameterId columnTemplateParameterIdExtractor0(NULL,&columnTemplateParameterId,&taCondition,types);
	
	InstantiationTypeId columnITypeIdExtractor0(NULL,&columnInstatiationTypeId,&taCondition,types);
	
	myVector.push_back(&columnTemplateParameterIdExtractor0);
	myVector.push_back(&columnITypeIdExtractor0);

	MapAll element(trees,&myVector,&myTrigger);

	element.accept(this);

	finalize();
}
