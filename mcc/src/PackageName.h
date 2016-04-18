#ifndef PACKAGENAME_H
#define PACKAGENAME_H

#include "DataExtractor.h"
#include "ConcreteTableColumn.h"

class PackageName : public DataExtractor {

public:    

	PackageName(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //PACKAGENAME_H