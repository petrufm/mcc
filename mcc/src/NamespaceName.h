#ifndef NAMESPACENAMENAME_H
#define NAMESAPCENAMENAME_H

#include "DataExtractor.h"
#include "ConcreteTableColumn.h"

class NamespaceName : public DataExtractor {

public:    

	NamespaceName(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	std::string doIt(AbstractTree &tree);

};
#endif //NAMESPACENAME_H