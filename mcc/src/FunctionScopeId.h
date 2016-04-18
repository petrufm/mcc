#ifndef FUNCTIONSCOPEID_H
#define FUNCTIONSCOPEID_H
#include "DataExtractor.h"

class ConcreteTableColumn;
class FuncDeclaration;
class TypesTable;

class FunctionScopeId : public DataExtractor {

public:    

    FunctionScopeId(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition, TypesTable *types);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //FUNCTIONSCOPEID_H

