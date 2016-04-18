#ifndef ISREALFUNCTION_H
#define ISREALFUNCTION_H
#include "DataExtractor.h"

class ConcreteTableColumn;
class FuncDeclaration;

class IsRealFunction : public DataExtractor {

public:    

	IsRealFunction(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //ISREALFUNCTION_H