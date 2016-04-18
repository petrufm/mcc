#ifndef INHERITANCEPARENT_H
#define INHERITANCEPARENT_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class InheritanceRelation;
class TypesTable;

class InheritanceParent : public DataExtractor {

public:    

    InheritanceParent(DataExtractor *next, ConcreteTableColumn *prototype, InheritanceRelation *condition, TypesTable *types);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //INHERITANCEPARENT_H