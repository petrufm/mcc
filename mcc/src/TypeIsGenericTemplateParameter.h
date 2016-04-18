#ifndef TYPEISGENERICTEMPLATEPARAMETER_H
#define TYPEISGENERICTEMPLATEPARAMETER_H

#include "DataExtractor.h"
#include "ClassTemplateParameter.h"
#include "ConcreteTableColumn.h"

class TypeIsGenericTemplateParameter : public DataExtractor {

public:    

    TypeIsGenericTemplateParameter(DataExtractor *next, ConcreteTableColumn *prototype, ClassTemplateParameter *condition);

protected:

virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //TYPEISGENERICTEMPLATEPARAMETER_H