#ifndef FUNCTIONBODYID_H
#define FUNCTIONBODYID_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class BodyTable;
class FuncDeclaration;

class FunctionBodyId : public DataExtractor {

public:    

    FunctionBodyId(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition, BodyTable *body);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

private:

	BodyTable *body;

};
#endif //FUNCTIONBODYID_H



