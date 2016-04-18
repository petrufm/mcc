#ifndef T2TRELATIONID_H
#define T2TRELATIONID_H

#include "DataExtractor.h"

class TemplateArgumentAsTypeInInstance;
class ConcreteTableColumn;
class TypesTable;
class TemplateParTypesRelation;
class TemplateParameterId;
class InstantiationTypeId;

class T2TRelationID : public DataExtractor {

public:    

    T2TRelationID(DataExtractor *next, ConcreteTableColumn *prototype, TemplateArgumentAsTypeInInstance *condition, TypesTable *table, TemplateParTypesRelation *t2t);

	~T2TRelationID();

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;
	TemplateParTypesRelation *t2t;
	TemplateParameterId *tmp_tpId;
	InstantiationTypeId *tmp_itId;

};
#endif //T2TRELATIONID_H