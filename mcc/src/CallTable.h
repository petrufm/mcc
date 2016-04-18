#ifndef CALLTABLE_H
#define CALLTABLE_H

#include "Table.h"

class BodyTable;
class FuncsTable;
class VariablesTable;
class TypesTable;
class InheritanceTable;
class NamespaceTable;
class TemplateParTypesRelation;

class CallTable : public Table {

public:    

    CallTable(char *name, BodyTable *bodies, FuncsTable *funcs, VariablesTable *var, TypesTable *types,
		InheritanceTable *inh, NamespaceTable *namespaces, TemplateParTypesRelation *tp2t);

	~CallTable();

    virtual void extract(ATCollection &trees);

	virtual void init();

private:

	BodyTable *bodies;
	FuncsTable *funcs;
	VariablesTable *vars;
	TypesTable *types;
	InheritanceTable *inh;
	NamespaceTable *namespaces;
	TemplateParTypesRelation *tp2t;

};
#endif //CALLTABLE_H
