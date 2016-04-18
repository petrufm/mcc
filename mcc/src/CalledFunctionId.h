#ifndef CALLEDFUNCTIONID_H
#define CALLEDFUNCTIONID_H

#include "DataExtractor.h"
#include "VisitProgressObserver.h"

class ConcreteTableColumn;
class FunctionCall;
class VariablesTable;
class BodyTable;
class FuncsTable;
class TypesTable;
class InheritanceTable;
class NamespaceTable;
class CallTable;
class IdentifyFunction;
class TemplateParTypesRelation;

class CalledFunctionId : public DataExtractor, public VisitProgressObserver {

public:    

    CalledFunctionId(DataExtractor *next, ConcreteTableColumn *prototype, FunctionCall *condition,
		VariablesTable *vars,
		BodyTable *bodies, 
		FuncsTable *funcs,
		TypesTable *types,
		InheritanceTable *inh,
		NamespaceTable *namespaces,
		CallTable *call,
		TemplateParTypesRelation *tp2t);

	void notifyGoDown(VTP_TreeP &tree);

	void notifyGoUp(VTP_TreeP &tree);

	~CalledFunctionId();

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	VariablesTable *vars;
	BodyTable *bodies;
	FuncsTable *funcs;
	TypesTable *types;
	InheritanceTable *inh;
	NamespaceTable *namespaces;
	CallTable *call;
	IdentifyFunction *funcId;
	TemplateParTypesRelation *tp2t;

};
#endif //CALLEDFUNCTIONID_H
