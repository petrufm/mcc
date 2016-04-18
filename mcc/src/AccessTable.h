#ifndef ACCESSTABLE_H
#define ACCESSTABLE_H

#include "Table.h"

class BodyTable;
class VariablesTable;
class FuncsTable;
class TypesTable;
class InheritanceTable;
class NamespaceTable;
class TemplateParTypesRelation;

class AccessTable : public Table {

public:    

    AccessTable(char *name, BodyTable *bodies, VariablesTable *var, FuncsTable *funcs, TypesTable *types,
		InheritanceTable *inh, NamespaceTable *namespaces, TemplateParTypesRelation *tp2t);

	~AccessTable();

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
#endif //ACCESSTABLE_H