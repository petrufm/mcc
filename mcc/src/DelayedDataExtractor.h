#ifndef DELAYEDDATAEXTRACTOR_H
#define DELAYEDDATAEXTRACTOR_H

#include "DataExtractor.h"
#include "TriggerCondition.h"
#include "ConcreteTableColumn.h"
#include <vector>

class DelayedDataExtractor : public DataExtractor {

public:

	typedef std::vector<std::string> IContainer;

	DelayedDataExtractor(DataExtractor *next,ConcreteTableColumn *prototype,TriggerCondition *condition);

	virtual bool finalizeExtraction(TableColumn *column,IContainer *info) = 0;

	virtual ~DelayedDataExtractor();

};
#endif //DELAYEDDATAEXTRACTOR_H
