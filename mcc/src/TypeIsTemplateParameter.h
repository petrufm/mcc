#ifndef TYPEISTEMPLATEPARAMETER_H
#define TYPEISTEMPLATEPARAMETER_H

#include "DataExtractor.h"
#include "ConcreteTableColumn.h"
#include "ClassTemplateParameter.h"

class TypeIsTemplateParameter : public DataExtractor {

public:    

    TypeIsTemplateParameter(DataExtractor *next, ConcreteTableColumn *prototype, ClassTemplateParameter *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //TYPEISTEMPLATEPARAMETER_H