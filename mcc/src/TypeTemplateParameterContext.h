#ifndef TYPETEMPLATEPARAMETERCONTEXT_H
#define TYPETEMPLATEPARAMETERCONTEXT_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class ClassTemplateParameter;

class TypeTemplateParameterContext : public DataExtractor {

public:    

    TypeTemplateParameterContext(DataExtractor *next, ConcreteTableColumn *prototype, ClassTemplateParameter *condition);

protected:

	virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //TYPETEMPLATEPARAMETERCONTEXT_H