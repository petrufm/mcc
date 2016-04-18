#ifndef TEMPLATEINSTANCECHAINSTABLE_H
#define TEMPLATEINSTANCECHAINSTABLE_H

#include "Table.h"

class TypesTable;
class TemplateParTypesRelation;

class TemplateInstanceChainsTable : public Table {

public:    

    TemplateInstanceChainsTable(char* name, TypesTable *types, TemplateParTypesRelation *t2t);

	~TemplateInstanceChainsTable();

    virtual void extract(ATCollection &trees);

	virtual void init();

private:

	TypesTable *types;
	TemplateParTypesRelation *t2t;

};
#endif //TEMPLATEINSTANCECHAINSTABLE_H