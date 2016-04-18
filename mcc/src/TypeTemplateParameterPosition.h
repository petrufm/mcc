#ifndef TYPETEMPLATEPARAMETERPOSITION_H
#define TYPETEMPLATEPARAMETERPOSITION_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class ClassTemplateParameter;

class TypeTemplateParameterPosition : public DataExtractor {

public:    

    TypeTemplateParameterPosition(DataExtractor *next, ConcreteTableColumn *prototype, ClassTemplateParameter *condition);

protected:

	virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //TYPETEMPLATEPARAMETERPOSITION_H