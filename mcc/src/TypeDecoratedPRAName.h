#ifndef TYPEDECORATEDPRANAME_H
#define TYPEDECORATEDPRANAME_H

#include "DataExtractor.h"

class PRADecorator;
class ConcreteTableColumn;

class TypeDecoratedPRAName : public DataExtractor {

public:    

    TypeDecoratedPRAName(DataExtractor *next, ConcreteTableColumn *prototype, PRADecorator *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //TYPEDECORATEDPRANAME_H