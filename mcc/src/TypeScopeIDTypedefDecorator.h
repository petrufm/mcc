#ifndef TYPESCOPEIDTYPEDEFDECORATOR_H
#define TYPESCOPEIDTYPEDEFDECORATOR_H
#include "DelayedDataExtractor.h"

class TypesTable;
class ConcreteTablecolumn;
class TypedefDecorator;
class BodyTable;

class TypeScopeIDTypedefDecorator : public DelayedDataExtractor {

public:    

	TypeScopeIDTypedefDecorator(DataExtractor *next, ConcreteTableColumn *prototype, TypedefDecorator *condition, TypesTable *types, BodyTable *bodies);

	virtual bool finalizeExtraction(TableColumn *column, IContainer *info);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;
	BodyTable *bodies;

};
#endif //TYPESCOPEIDTYPEDEFDECORATOR_H