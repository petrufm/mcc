#ifndef TYPEPOINTERTOFUNCTIONNAME_H
#define TYPEPOINTERTOFUNCTIONNAME_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class Pointer2Function;

class TypePointerToFunctionName : public DataExtractor {

public:    

    TypePointerToFunctionName(DataExtractor *next, ConcreteTableColumn *prototype, Pointer2Function *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //TYPEPOINTERTOFUNCTIONNAME_H