#ifndef TYPEISCLASS_H
#define TYPEISCLASS_H

#include "DataExtractor.h"
#include "ConcreteTableColumn.h"
#include "ClassDeclaration.h"

class TypeIsClass : public DataExtractor {

public:    

    TypeIsClass(DataExtractor *next, ConcreteTableColumn *prototype, ClassDeclaration *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //TYPEISCLASS_H