#ifndef TYPEDECORATORTEMPLATEINSTANCENAME_H
#define TYPEDECORATORTEMPLATEINSTANCENAME_H

#include "DataExtractor.h"

class TemplateInstance;
class ConcreteTableColumn;

class TypeDecoratorTemplateInstanceName : public DataExtractor {

public:    

    TypeDecoratorTemplateInstanceName(DataExtractor *next, ConcreteTableColumn *prototype, TemplateInstance *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);


};
#endif //TYPEDECORATORTEMPLATEINSTANCENAME_H