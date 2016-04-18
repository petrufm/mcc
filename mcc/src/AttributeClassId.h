#ifndef ATTRIBUTECLASSID_H
#define ATTRIBUTECLASSID_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class AttributeVariable;
class TypesTable;

class AttributeClassId : public DataExtractor {

public:

    AttributeClassId(DataExtractor *next, ConcreteTableColumn *prototype, AttributeVariable *condition, TypesTable *types);    

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //ATTRIBUTECLASSID_H
