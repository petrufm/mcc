#ifndef INSTANTIATIONTYPEID_H
#define INSTANTIATIONTYPEID_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class TemplateArgumentAsType;
class TypesTable;

class InstantiationTypeId : public DataExtractor {

public:

    InstantiationTypeId(DataExtractor *next, ConcreteTableColumn *prototype, TemplateArgumentAsType *condition, TypesTable *types);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);
private:	
    TypesTable *types;
};
#endif //INSTANTIATIONTYPEID_H