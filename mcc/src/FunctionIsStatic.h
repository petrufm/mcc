#ifndef FUNCTIONISSTATIC_H
#define FUNCTIONISSTATIC_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class FuncDeclaration;

class FunctionIsStatic : public DataExtractor {
    
public:    

    FunctionIsStatic(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //FUNCTIONISSTATIC_H