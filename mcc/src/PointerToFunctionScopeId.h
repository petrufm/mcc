#ifndef POINTERTOFUNCTIONSCOPEID_H
#define POINTERTOFUNCTIONSCOPEID_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class Pointer2Function;
class TypesTable;

class PointerToFunctionScopeId : public DataExtractor {

public:    

    PointerToFunctionScopeId(DataExtractor *next, ConcreteTableColumn *prototype, Pointer2Function *condition, TypesTable *types);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //POINTERTOFUNCTIONSCOPEID_H