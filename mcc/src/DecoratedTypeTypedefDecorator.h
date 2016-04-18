#ifndef DECORATEDTYPETYPEDEFDECORATOR_H
#define DECORATEDTYPETYPEDEFDECORATOR_H

#include "DelayedDataExtractor.h"

class TypedefDecorator;
class TypesTable;
class ConcreteTableColumn;

class DecoratedTypeTypedefDecorator : public DelayedDataExtractor {

public:    

    DecoratedTypeTypedefDecorator(DataExtractor *next, ConcreteTableColumn *prototype, TypedefDecorator *condition, TypesTable *types);

	virtual bool finalizeExtraction(TableColumn *column, IContainer *info);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //DECORATEDTYPETYPEDEFDECORATOR_H