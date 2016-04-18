#ifndef POINTERTOFUNCTIONRETURNTYPE_H
#define POINTERTOFUNCTIONRETURNTYPE_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class Pointer2Function;
class TypesTable;

class PointerToFunctionReturnType : public DataExtractor {

public:    

    PointerToFunctionReturnType(DataExtractor *next, ConcreteTableColumn *prototype, Pointer2Function *condition, TypesTable *types);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //POINTERTOFUNCTIONRETURNTYPE_H