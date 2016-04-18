#ifndef TYPEISDECORATORTEMPLATEINSTANCE_H
#define TYPEISDECORATORTEMPLATEINSTANCE_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class TemplateInstance;

class TypeIsDecoratorTemplateInstance : public DataExtractor {

public:

    TypeIsDecoratorTemplateInstance(DataExtractor *next, ConcreteTableColumn *prototype, TemplateInstance *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);


};
#endif //TYPEISDECORATORTEMPLATEINSTANCE_H