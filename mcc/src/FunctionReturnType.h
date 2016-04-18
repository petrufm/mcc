#ifndef FUNCTIONRETURNTYPE_H
#define FUNCTIONRETURNTYPE_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class FuncDeclaration;
class TypesTable;

class FunctionReturnType : public DataExtractor {

public:    

    FunctionReturnType(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition, TypesTable *types);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //FUNCTIONRETURNTYPE_H