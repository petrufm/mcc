#ifndef TYPEISPRIMITIVE_H
#define TYPEISPRIMITIVE_H

#include "DataExtractor.h"
#include "ConcreteTableColumn.h"
#include "PrimitiveType.h"

class TypeIsPrimitive : public DataExtractor {

public:    

    TypeIsPrimitive(DataExtractor *next, ConcreteTableColumn *prototype, PrimitiveType *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //TYPEISPRIMITIVE_H