#ifndef TEMPLATEPARTYPESRELATION_H
#define TEMPLATEPARTYPESRELATION_H

#include "Table.h"

class TypesTable;

class TemplateParTypesRelation : public Table {

public:

    TemplateParTypesRelation(char* name, TypesTable *types);

	~TemplateParTypesRelation();

    virtual void extract(ATCollection &trees);

	virtual void init();

private:

	TypesTable *types;

};
#endif //TEMPLATEPARTYPESRELATION_H