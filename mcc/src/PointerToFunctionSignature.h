#ifndef POINTERTOFUNCTIONSIGNATURE_H
#define POINTERTOFUNCTIONSIGNATURE_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class Pointer2Function;

class PointerToFunctionSignature : public DataExtractor {

public:    

    PointerToFunctionSignature(DataExtractor *next, ConcreteTableColumn *prototype, Pointer2Function *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //POINTERTOFUNCTIONSIGNATURE_H