#ifndef TYPESCOPEIDTEMPLATEPARAMETER_H
#define TYPESCOPEIDTEMPLATEPARAMETER_H

#include "DelayedDataExtractor.h"
#include "ClassTemplateParameter.h"
#include "TypesTable.h"

class TypeScopeIDTemplateParameter : public DelayedDataExtractor {

private:
	TypesTable *types;
public:    

	TypeScopeIDTemplateParameter(DataExtractor *next, ConcreteTableColumn *prototype, ClassTemplateParameter *condition, TypesTable *types);

	virtual bool finalizeExtraction(TableColumn *column, IContainer *info);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);
};
#endif //TYPESCOPEIDTEMPLATEPARAMETER_H