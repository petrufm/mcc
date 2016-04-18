#ifndef FUNCSTABLE_H
#define FUNCSTABLE_H

#include "Table.h"

class PackagesTable;
class NamespaceTable;
class TypesTable;
class BodyTable;

class FuncsTable : public Table {

public:    

    FuncsTable(char *name, NamespaceTable *namespaces, TypesTable *types, BodyTable *body);

	~FuncsTable();

    virtual void extract(ATCollection &trees);

	virtual void init();

private:

	NamespaceTable *namespaces;
	TypesTable *types;
	BodyTable *body;

};
#endif //FUNCSTABLE_H