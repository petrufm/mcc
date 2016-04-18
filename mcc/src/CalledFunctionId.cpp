#include "CalledFunctionId.h"
#include "ConcreteTableColumn.h"
#include "FunctionCall.h"
#include "IdentifyFunction.h"
#include "TemplateParTypesRelation.h"
#include "TableRow.h"
#include "CallTable.h"

CalledFunctionId::CalledFunctionId(DataExtractor *next, ConcreteTableColumn *prototype, FunctionCall *condition,
		VariablesTable *vars,
		BodyTable *bodies, 
		FuncsTable *funcs,
		TypesTable *types,
		InheritanceTable *inh,
		NamespaceTable *namespaces,
		CallTable *call,
		TemplateParTypesRelation *tp2t) : DataExtractor(next,prototype,condition) {

	this->vars = vars;
	this->bodies = bodies;
	this->funcs = funcs;
	this->types = types;
	this->inh = inh;
	this->namespaces = namespaces;
	this->call = call;
	this->tp2t = tp2t;
	this->funcId = new IdentifyFunction(vars,bodies,funcs,types,inh,namespaces,tp2t);
}

CalledFunctionId::~CalledFunctionId() {
	delete funcId;
}

TableColumn* CalledFunctionId::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();

	std::string value,bodyId;
	std::vector<std::string> possibleFuncs;
	std::vector<std::string>::iterator i;

	bodyId = funcId->findFunction(tree,possibleFuncs);

	if(possibleFuncs.size() != 0) {

		for(i = possibleFuncs.begin(); (i + 1) != possibleFuncs.end(); ++i) {

			TableRow *row;
			ConcreteTableColumn *col;
			std::string initVal;

			row = new TableRow();
			col = new ConcreteTableColumn(std::string("BodyId"),true);
			col->init(bodyId,true,0,0);
			row->add(col);
			col = new ConcreteTableColumn(std::string("FuncId"),true);
			col->init(*i,true,0,0);
			row->add(col);
			col = new ConcreteTableColumn(std::string("Counter"),true);
			initVal = "1";
			col->init(initVal,false,1,TableColumn::MergeByAdd);
			row->add(col);

			if(!call->insertRow(row)) {
				delete row;
			};

		}

		value = *i;

	} else {

		value = "<ERROR>";

	}

	column->init(value,true);
	return column;

}

void CalledFunctionId::notifyGoDown(VTP_TreeP &tree) {
	if(!strcmp(VTP_OP_NAME(VTP_TREE_OPERATOR(tree)),"fndef")) {
		funcId->setReset();
	}
}

void CalledFunctionId::notifyGoUp(VTP_TreeP &tree) {
	if(!strcmp(VTP_OP_NAME(VTP_TREE_OPERATOR(tree)),"fndef")) {
		funcId->setReset();
	}
}
