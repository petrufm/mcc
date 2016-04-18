#ifndef VARIABLENAME_H
#define VARIABLENAME_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class VariableDeclaration;

class VariableName : public DataExtractor {

public:    

    VariableName(DataExtractor *next, ConcreteTableColumn *prototype, VariableDeclaration *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //VARIABLENAME_H