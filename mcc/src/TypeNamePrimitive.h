#ifndef TYPENAMEPRIMITIVE_H
#define TYPENAMEPRIMITIVE_H

#include "DataExtractor.h"
#include "ConcreteTableColumn.h"
#include "PrimitiveType.h"

class TypeNamePrimitive : public DataExtractor {

public:    

    TypeNamePrimitive(DataExtractor *next, ConcreteTableColumn *prototype, PrimitiveType *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //TYPENAMEPRIMITIVE_H