#include "AccessedVariableId.h"
#include "ConcreteTableColumn.h"
#include "VariableAccess.h"
#include "IdentifyVariable.h"

AccessedVariableId::AccessedVariableId(DataExtractor *next, ConcreteTableColumn *prototype, VariableAccess *condition,
		VariablesTable *vars,
		BodyTable *bodies, 
		FuncsTable *funcs,
		TypesTable *types,
		InheritanceTable *inh,
		NamespaceTable *namespaces,
		TemplateParTypesRelation *tp2t) : DataExtractor(next,prototype,condition) {

	this->vars = vars;
	this->bodies = bodies;
	this->funcs = funcs;
	this->types = types;
	this->inh = inh;
	this->namespaces = namespaces;
	this->tp2t	= tp2t;
	this->varId = new IdentifyVariable(vars,bodies,funcs,types,inh,namespaces,tp2t);
}

AccessedVariableId::~AccessedVariableId() {
	delete varId;
}

TableColumn* AccessedVariableId::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();

	std::string value = varId->findVariable(tree);

	column->init(value,true);

	return column;

}

void AccessedVariableId::notifyGoDown(VTP_TreeP &tree) {
	if(!strcmp(VTP_OP_NAME(VTP_TREE_OPERATOR(tree)),"fndef")) {
		varId->setReset();
	}
}

void AccessedVariableId::notifyGoUp(VTP_TreeP &tree) {
	if(!strcmp(VTP_OP_NAME(VTP_TREE_OPERATOR(tree)),"fndef")) {
		varId->setReset();
	}
}
