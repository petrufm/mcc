#ifndef VARIABLEISCONST_H
#define VARIABLEISCONST_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class VariableDeclaration;

class VariableIsConst : public DataExtractor {

public:    

    VariableIsConst(DataExtractor *next, ConcreteTableColumn *prototype, VariableDeclaration *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	VariableDeclaration *cond;

};
#endif //VARIABLEISCONST_H
