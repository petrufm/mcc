#ifndef FUNCTIONPARAMETERS_H
#define FUNCTIONPARAMETERS_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class FuncDeclaration;

class FunctionParameters : public DataExtractor {

public:    

    FunctionParameters(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //FUNCTIONPARAMETERS_H