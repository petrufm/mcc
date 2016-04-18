#ifndef FUNCTIONNAME_H
#define FUNCTIONNAME_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class FuncDeclaration;

class FunctionName : public DataExtractor {

public:    

    FunctionName(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //FUNCTIONNAME_H