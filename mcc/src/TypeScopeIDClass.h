#ifndef TYPESCOPEIDCLASS_H
#define TYPESCOPEIDCLASS_H

#include "DelayedDataExtractor.h"
#include "ClassDeclaration.h"
#include "TypesTable.h"
#include "BodyTable.h"

class TypeScopeIDClass : public DelayedDataExtractor {

public:    

	TypeScopeIDClass(DataExtractor *next, ConcreteTableColumn *prototype, ClassDeclaration *condition, TypesTable *types, BodyTable *bodies);

	virtual bool finalizeExtraction(TableColumn *column, IContainer *info);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;
	BodyTable *bodies;

};
#endif //TYPESCOPEIDCLASS_H