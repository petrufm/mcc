#ifndef TYPESCOPEIDPOINTERTOFUNCTION_H
#define TYPESCOPEIDPOINTERTOFUNCTION_H

#include "DelayedDataExtractor.h"

class ConcreteTableColumn;
class Pointer2Function;
class TypesTable;

class TypeScopeIDPointerToFunction : public DelayedDataExtractor {

public:    

	TypeScopeIDPointerToFunction(DataExtractor *next, ConcreteTableColumn *prototype, Pointer2Function *condition, TypesTable *types);

	virtual bool finalizeExtraction(TableColumn *column, IContainer *info);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //TYPESCOPEIDPOINTERTOFUNCTION_H