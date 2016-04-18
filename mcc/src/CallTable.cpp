#include "CallTable.h"
#include "MapAll.h"
#include "ConcreteTableColumn.h"
#include "FunctionCall.h"
#include "AccessorBodyId.h"
#include "CalledFunctionId.h"
#include "TemplateParTypesRelation.h"
#include "Counter.h"


CallTable::CallTable(char *name, BodyTable *bodies, FuncsTable *funcs, VariablesTable *var, TypesTable *types,
					 InheritanceTable *inh, NamespaceTable *namespaces, TemplateParTypesRelation *tp2t) : Table(name) {

	this->bodies = bodies;
	this->funcs = funcs;
	this->vars = var;
	this->types = types;
	this->inh = inh;
	this->namespaces = namespaces;
	this->tp2t = tp2t;

};

CallTable::~CallTable() {}

void CallTable::init() {

	buildColumn(std::string("BodyId"));
	buildColumn(std::string("FuncId"));
	buildColumn(std::string("Counter"));

}

void CallTable::extract(ATCollection &trees) {

	MapAll::VectorOfChain myVector;
	MapAll::VectorOfTrigger myTrigger;

	ConcreteTableColumn columnBodyId(std::string("BodyId"),true);
	ConcreteTableColumn columnFuncId(std::string("FuncId"),true);
	ConcreteTableColumn columnCounter(std::string("Counter"),true);

	FunctionCall aCondition;
	myTrigger.push_back(&aCondition);

	AccessorBodyId columnBodyIdExtractor0(NULL,&columnBodyId,&aCondition,bodies);

	CalledFunctionId columnFuncIdExtractor0(NULL,&columnFuncId,&aCondition,
				vars,bodies,funcs,types,inh,namespaces,this,tp2t);

	Counter columnCounterExtractor0(NULL,&columnCounter,&aCondition);

	myVector.push_back(&columnBodyIdExtractor0);
	myVector.push_back(&columnFuncIdExtractor0);
	myVector.push_back(&columnCounterExtractor0);

	MapAll element(trees,&myVector,&myTrigger);
	element.register_observer(&columnBodyIdExtractor0);
	element.register_observer(&columnFuncIdExtractor0);
	element.accept(this);

	finalize();
	
}