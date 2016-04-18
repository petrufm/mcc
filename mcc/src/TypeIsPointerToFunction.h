#ifndef TYPEISPOINTERTOFUNCTION_H
#define TYPEISPOINTERTOFUNCTION_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class Pointer2Function;

class TypeIsPointerToFunction : public DataExtractor {

public:    

    TypeIsPointerToFunction(DataExtractor *next, ConcreteTableColumn *prototype, Pointer2Function *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //TYPEISPOINTERTOFUNCTION_H