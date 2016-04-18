#ifndef TYPEPRACONTEXT_H
#define TYPEPRACONTEXT_H

#include "DelayedDataExtractor.h"

class ConcreteTableColumn;
class PRADecorator;
class TypesTable;

class TypePRAContext : public DelayedDataExtractor {

public:    

    TypePRAContext(DataExtractor *next, ConcreteTableColumn *prototype, PRADecorator *condition, TypesTable *types);

	virtual bool finalizeExtraction(TableColumn *column, IContainer *info);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //TYPEPRACONTEXT_H