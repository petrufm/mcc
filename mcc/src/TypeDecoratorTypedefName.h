#ifndef TYPEDECORATORTYPEDEFNAME_H
#define TYPEDECORATORTYPEDEFNAME_H

#include "DataExtractor.h"

class TypedefDecorator;
class ConcreteTableColumn;

class TypeDecoratorTypedefName : public DataExtractor {
public:    

    TypeDecoratorTypedefName(DataExtractor *next, ConcreteTableColumn *prototype, TypedefDecorator *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //TYPEDECORATORTYPEDEFNAME_H