#ifndef FILEPOSITIONSTART_H
#define FILEPOSITIONSTART_H

#include "DataExtractor.h"
#include "ConcreteTableColumn.h"

class FilePositionStart : public DataExtractor {

public:

	FilePositionStart(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //FILEPOSITIONSTART_H