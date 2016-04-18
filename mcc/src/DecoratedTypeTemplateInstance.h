#ifndef DECORATEDTYPETEMPLATEINSTANCE_H
#define DECORATEDTYPETEMPLATEINSTANCE_H

#include "DelayedDataExtractor.h"

class TemplateInstance;
class ConcreteTableColumn;
class TypesTable;

class DecoratedTypeTemplateInstance : public DelayedDataExtractor {

public:    

    DecoratedTypeTemplateInstance(DataExtractor *next, ConcreteTableColumn *prototype, TemplateInstance *condition, TypesTable *types);

	virtual bool finalizeExtraction(TableColumn *column, IContainer *info);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //DECORATEDTYPETEMPLATEINSTANCE_H