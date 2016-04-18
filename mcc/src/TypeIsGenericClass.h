#ifndef TYPEISGENERICCLASS_H
#define TYPEISGENERICCLASS_H

#include "DataExtractor.h"
#include "ConcreteTableColumn.h"
#include "ClassDeclaration.h"

class TypeIsGenericClass : public DataExtractor {

public:    

    TypeIsGenericClass(DataExtractor *next, ConcreteTableColumn *prototype, ClassDeclaration *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //TYPEISGENERICCLASS_H