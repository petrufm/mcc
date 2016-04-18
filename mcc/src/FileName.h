#ifndef FILENAME_H
#define FILENAME_H

#include "DataExtractor.h"
#include "ConcreteTableColumn.h"

class FileName : public DataExtractor {

public:    

	FileName(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //FILENAME_H