#ifndef VARIABLETYPE_H
#define VARIABLETYPE_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class VariableDeclaration;
class TypesTable;

class VariableType : public DataExtractor {

public:    

    VariableType(DataExtractor *next, ConcreteTableColumn *prototype, VariableDeclaration *condition, TypesTable *types);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;
};
#endif //VARIABLETYPE_H
