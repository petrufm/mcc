#ifndef COLUMNMARKER_H
#define COLUMNMARKER_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class TriggerCondition;

class ColumnMarker : public DataExtractor {

public:    

    ColumnMarker(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //COLUMNMARKER_H