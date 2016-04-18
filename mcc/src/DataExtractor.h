#ifndef DATAEXTRACTOR_H
#define DATAEXTRACTOR_H

#include "FilesParser.h"
#include "TableColumn.h"
#include "TriggerCondition.h"
#include "ConcreteTableColumn.h"

class DataExtractor {

public:

    DataExtractor(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition);

    TableColumn* extract(AbstractTree &tree);

private:

    /**
     * @supplierCardinality 1 
     */
	DataExtractor *next;    

    /**
     * @supplierCardinality 1 
     */
    TriggerCondition * condition;

	static TableColumn* protectedExecution(DataExtractor *t, AbstractTree &tree, ConcreteTableColumn *prot);

protected:

    /**
     * @clientCardinality 1 
     */
	ConcreteTableColumn *prototype;

	virtual TableColumn* handleExtraction(AbstractTree &tree) = 0;

	virtual std::string& handleExtractionError();

	virtual bool canHandle(AbstractTree &tree);

	virtual ~DataExtractor();
};


#endif //DATAEXTRACTOR_H