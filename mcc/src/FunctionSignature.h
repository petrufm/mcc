#ifndef FUNCTIONSIGNATURE_H
#define FUNCTIONSIGNATURE_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class FuncDeclaration;

class FunctionSignature : public DataExtractor {

public:    

    FunctionSignature(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //FUNCTIONSIGNATURE_H
