#ifndef INHERITANCEDESCENDENT_H
#define INHERITANCEDESCENDENT_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class InheritanceRelation;
class TypesTable;

class InheritanceDescendent : public DataExtractor {

public:    

    InheritanceDescendent(DataExtractor *next, ConcreteTableColumn *prototype, InheritanceRelation *condition, TypesTable *types);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //INHERITANCEDESCENDENT_H