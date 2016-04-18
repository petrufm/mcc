#ifndef NAMESPECEID_H
#define NAMESPECEID_H

#include "DataExtractor.h"

class NamespaceName;
class NamespaceTable;
class TriggerCondition;
class Always;
class ConcreteTableColumn;

class NamespaceID : public DataExtractor {

public:

    NamespaceID(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition, NamespaceTable *namespaces);

	~NamespaceID();

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	NamespaceTable *namespaces;

	Always *tmp_condition;

    /**
     * @supplierCardinality 1 
     */
    NamespaceName *lnkNamespaceName;

};
#endif //NAMESPECEID_H