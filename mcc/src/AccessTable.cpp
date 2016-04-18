#include "AccessTable.h"
#include "MapAll.h"
#include "ConcreteTableColumn.h"
#include "VariableAccess.h"
#include "AccessorBodyId.h"
#include "AccessedVariableId.h"
#include "Counter.h"

AccessTable::AccessTable(char *name, BodyTable *bodies, VariablesTable *var, FuncsTable *funcs, TypesTable *types,
						 InheritanceTable *inh, NamespaceTable *namespaces,TemplateParTypesRelation *tp2t) : Table(name) {
	this->bodies = bodies;
	this->vars = var;
	this->funcs = funcs;
	this->types = types;
	this->inh = inh;
	this->namespaces = namespaces;
	this->tp2t = tp2t;

};

AccessTable::~AccessTable() {}

void AccessTable::init() {

	buildColumn(std::string("BodyId"));
	buildColumn(std::string("VarId"));
	buildColumn(std::string("Counter"));

}

void AccessTable::extract(ATCollection &trees) {

	MapAll::VectorOfChain myVector;
	MapAll::VectorOfTrigger myTrigger;

	
	ConcreteTableColumn columnBodyId(std::string("BodyId"),true);
	ConcreteTableColumn columnVarId(std::string("VarId"),true);
	ConcreteTableColumn columnCounter(std::string("Counter"),true);

	VariableAccess aCondition;
	myTrigger.push_back(&aCondition);

	AccessorBodyId columnBodyIdExtractor0(NULL,&columnBodyId,&aCondition,bodies);

	AccessedVariableId columnVarIdExtractor0(NULL,&columnVarId,&aCondition,
		vars,bodies,funcs,types,inh,namespaces,tp2t);

	Counter columnCounterExtractor0(NULL,&columnCounter,&aCondition);

	myVector.push_back(&columnBodyIdExtractor0);
	myVector.push_back(&columnVarIdExtractor0);
	myVector.push_back(&columnCounterExtractor0);

	MapAll element(trees,&myVector,&myTrigger);
	element.register_observer(&columnBodyIdExtractor0);
	element.register_observer(&columnVarIdExtractor0);
	element.accept(this);

	finalize();
	
}