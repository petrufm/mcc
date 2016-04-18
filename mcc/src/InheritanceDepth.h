#ifndef INHERITANCEDEPTH_H
#define INHERITANCEDEPTH_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class InheritanceRelation;

class InheritanceDepth : public DataExtractor {

public:    

    InheritanceDepth(DataExtractor *next, ConcreteTableColumn *prototype, InheritanceRelation *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //INHERITANCEDEPTH_H