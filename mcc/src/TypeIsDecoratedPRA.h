#ifndef TYPEISDECORATEDPRA_H
#define TYPEISDECORATEDPRA_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class PRADecorator;

class TypeIsDecoratedPRA : public DataExtractor {

public:    

    TypeIsDecoratedPRA(DataExtractor *next, ConcreteTableColumn *prototype, PRADecorator *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //TYPEISDECORATEDPRA_H