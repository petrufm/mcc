#ifndef VARIABLESTABLE_H
#define VARIABLESTABLE_H

#include "Table.h"

class PackagesTable;
class NamespaceTable;
class TypesTable;
class BodyTable;

class VariablesTable : public Table {

public:

    VariablesTable(char *name, PackagesTable *packages, NamespaceTable *namespaces, TypesTable *types, BodyTable *bodies);

	~VariablesTable();

    virtual void extract(ATCollection &trees);

	virtual void init();

private:

	PackagesTable *packages;
	NamespaceTable *namespaces;
	TypesTable *types;
	BodyTable *bodies;

};
#endif //VARIABLESTABLE_H
