#ifndef ATTRIBUTEACCESS_H
#define ATTRIBUTEACCESS_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class AttributeVariable;

class AttributeAccess : public DataExtractor {

public:    

    AttributeAccess(DataExtractor *next, ConcreteTableColumn *prototype, AttributeVariable *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //ATTRIBUTEACCESS_H