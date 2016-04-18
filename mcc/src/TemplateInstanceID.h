#ifndef TEMPLATEINSTANCEID_H
#define TEMPLATEINSTANCEID_H

#include "DataExtractor.h"

class TemplateArgumentAsTypeInInstance;
class ConcreteTableColumn;
class TypesTable;
class TemplateParTypesRelation;

class TemplateInstanceID : public DataExtractor {

public:    

    TemplateInstanceID(DataExtractor *next, ConcreteTableColumn *prototype, TemplateArgumentAsTypeInInstance *condition, TypesTable *types, TemplateParTypesRelation *t2t);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;
	TemplateParTypesRelation *t2t;

};
#endif //TEMPLATEINSTANCEID_H