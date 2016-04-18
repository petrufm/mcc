#ifndef TYPEPOINTERTOFUNCTIONCONTEXT_H
#define TYPEPOINTERTOFUNCTIONCONTEXT_H
#include "DelayedDataExtractor.h"

class ConcreteTableColumn;
class Pointer2Function;
class TypesTable;

class TypePointerToFunctionContext : public DelayedDataExtractor {

public:    

    TypePointerToFunctionContext(DataExtractor *next, ConcreteTableColumn *prototype, Pointer2Function *condition, TypesTable *types);

	virtual bool finalizeExtraction(TableColumn *column, IContainer *info);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //TYPEPOINTERTOFUNCTIONCONTEXT_H