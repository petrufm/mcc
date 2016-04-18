#ifndef COUTER_H
#define COUTER_H

#include "DataExtractor.h"
#include "ConcreteTableColumn.h"

class Counter : public DataExtractor {

public:    

    Counter(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //COUTER_H
