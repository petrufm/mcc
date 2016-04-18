#ifndef TYPESTABLE_H
#define TYPESTABLE_H

#include "Table.h"
#include "PackagesTable.h"
#include "NamespaceTable.h"
#include "BodyTable.h"

class TypesTable : public Table {

public:    

    TypesTable(char *name, PackagesTable *packages, NamespaceTable *namespaces, BodyTable *bodies);

	~TypesTable();

    virtual void extract(ATCollection &trees);

	virtual void init();

private:

	PackagesTable *packages;
	NamespaceTable *namespaces;
	BodyTable *bodies;

};
#endif //TYPESTABLE_H