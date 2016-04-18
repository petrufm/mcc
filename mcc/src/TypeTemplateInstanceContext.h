#ifndef TYPETEMPLATEINSTANCECONTEXT_H
#define TYPETEMPLATEINSTANCECONTEXT_H

#include "DelayedDataExtractor.h"

class ConcreteTableColumn;
class TemplateInstance;
class TypesTable;

class TypeTemplateInstanceContext : public DelayedDataExtractor {

public:    

    TypeTemplateInstanceContext(DataExtractor *next, ConcreteTableColumn *prototype, TemplateInstance *condition, TypesTable *types);

	virtual bool finalizeExtraction(TableColumn *column, IContainer *info);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //TYPETEMPLATEINSTANCECONTEXT_H