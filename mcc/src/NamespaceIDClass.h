#ifndef NAMESPACEIDCLASS_H
#define NAMESPACEIDCLASS_H

#include "DataExtractor.h"
#include "NamespaceName.h"
#include "NamespaceTable.h"
#include "Always.h"
#include "ClassDeclaration.h"

class NamespaceIDClass : public DataExtractor {

public:

	NamespaceIDClass(DataExtractor *next, ConcreteTableColumn *prototype, ClassDeclaration *condition, NamespaceTable *namespaces);

	~NamespaceIDClass();

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	NamespaceTable *namespaces;

	Always *tmp_condition;

    /**
     * @supplierCardinality 1 
     */
    NamespaceName * lnkNamespaceName;
};
#endif //NAMESPACEIDCLASS_H
