#ifndef TYPEISDECORATORTYPEDEF_H
#define TYPEISDECORATORTYPEDEF_H

#include "DataExtractor.h"
struct _AbstractTree;
class TableColumn;

class ConcreteTableColumn;
class TypedefDecorator;

class TypeIsDecoratorTypedef : public DataExtractor {

public:    

    TypeIsDecoratorTypedef(DataExtractor *next, ConcreteTableColumn *prototype, TypedefDecorator *condition);
protected:    

    virtual TableColumn *handleExtraction(_AbstractTree &tree);
};
#endif //TYPEISDECORATORTYPEDEF_H