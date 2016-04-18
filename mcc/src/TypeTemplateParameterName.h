#ifndef TYPETEMPLATEPARAMETERNAME_H
#define TYPETEMPLATEPARAMETERNAME_H

#include "DataExtractor.h"
#include "ClassTemplateParameter.h"
#include "ConcreteTableColumn.h"

class TypeTemplateParameterName : public DataExtractor {

public:    

    TypeTemplateParameterName(DataExtractor *next, ConcreteTableColumn *prototype, ClassTemplateParameter *condition);

protected:

	virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //TYPETEMPLATEPARAMETERNAME_H