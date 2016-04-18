#ifndef DECORATEDTYPEPRA_H
#define DECORATEDTYPEPRA_H

#include "DelayedDataExtractor.h"

class ConcreteTableColumn;
class PRADecorator;
class TypesTable;

class DecoratedTypePRA : public DelayedDataExtractor {

public:    

	DecoratedTypePRA(DataExtractor *next, ConcreteTableColumn *prototype, PRADecorator *condition, TypesTable *types);

	virtual bool finalizeExtraction(TableColumn *column, IContainer *info);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //DECORATEDTYPEPRA_H