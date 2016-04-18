#ifndef INHERITANCEACCESS_H
#define INHERITANCEACCESS_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class InheritanceRelation;

class InheritanceAccess : public DataExtractor {

public:    

    InheritanceAccess(DataExtractor *next, ConcreteTableColumn *prototype, InheritanceRelation *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //INHERITANCEACCESS_H