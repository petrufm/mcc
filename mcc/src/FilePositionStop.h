#ifndef FILEPOSITIONSTOP_H
#define FILEPOSITIONSTOP_H

#include "DataExtractor.h"
#include "ConcreteTableColumn.h"
#include "TriggerCondition.h"

class FilePositionStop : public DataExtractor {

public:    

    FilePositionStop(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition, int levelUp);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	int levelUp;

};
#endif //FILEPOSITIONSTOP_H