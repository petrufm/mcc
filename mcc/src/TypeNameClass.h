#ifndef TYPENAMECLASS_H
#define TYPENAMECLASS_H

#include "DataExtractor.h"
#include "ConcreteTableColumn.h"
#include "ClassDeclaration.h"

class TypeNameClass : public DataExtractor {

public:    

    TypeNameClass(DataExtractor *next, ConcreteTableColumn *prototype, ClassDeclaration *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //TYPENAMECLASS_H