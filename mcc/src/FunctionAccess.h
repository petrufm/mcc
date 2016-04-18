#ifndef FUNCTIONACCESS_H
#define FUNCTIONACCESS_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class MethodDeclaration;

class FunctionAccess : public DataExtractor {

public:    

    FunctionAccess(DataExtractor *next, ConcreteTableColumn *prototype, MethodDeclaration *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //FUNCTIONACCESS_H