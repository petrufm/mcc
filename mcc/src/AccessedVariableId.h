#ifndef ACCESSEDVARIABLEID_H
#define ACCESSEDVARIABLEID_H

#include "DataExtractor.h"
#include "VisitProgressObserver.h"

class ConcreteTableColumn;
class VariableAccess;
class VariablesTable;
class BodyTable;
class FuncsTable;
class TypesTable;
class InheritanceTable;
class NamespaceTable;
class IdentifyVariable;
class TemplateParTypesRelation;

class AccessedVariableId : public DataExtractor, public VisitProgressObserver {

public:    

    AccessedVariableId(DataExtractor *next, ConcreteTableColumn *prototype, VariableAccess *condition,
		VariablesTable *vars,
		BodyTable *bodies, 
		FuncsTable *funcs,
		TypesTable *types,
		InheritanceTable *inh,
		NamespaceTable *namespaces,
		TemplateParTypesRelation *tp2t);

	void notifyGoDown(VTP_TreeP &tree);

	void notifyGoUp(VTP_TreeP &tree);

	~AccessedVariableId();

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

	IdentifyVariable *varId;
	VariablesTable *vars;
	BodyTable *bodies;
	FuncsTable *funcs;
	TypesTable *types;
	InheritanceTable *inh;
	NamespaceTable *namespaces;
	TemplateParTypesRelation  *tp2t;

};
#endif //ACCESSEDVARIABLEID_H
