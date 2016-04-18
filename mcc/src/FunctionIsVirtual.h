#ifndef FUNCTIONISVIRTUAL_H
#define FUNCTIONISVIRTUAL_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class MethodDeclaration;

class FunctionIsVirtual : public DataExtractor {
    
public:

	FunctionIsVirtual(DataExtractor *next, ConcreteTableColumn *prototype, MethodDeclaration *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //FUNCTIONISVIRTUAL_H