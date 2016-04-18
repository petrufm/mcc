#ifndef FUNCTIONNAMESPACEID_H
#define FUNCTIONNAMESPACEID_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class FuncDeclaration;
class FunctionScopeId;
class TypesTable;
class NamespaceTable;
class NamespaceName;

class FunctionNamespaceId : public DataExtractor {

public:    

    FunctionNamespaceId(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition, TypesTable *types, NamespaceTable *namespaces);

	~FunctionNamespaceId();

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;
	NamespaceTable *namespaces;
	FunctionScopeId *the_scope;
	NamespaceName *the_namespace;

};
#endif //FUNCTIONNAMESPACEID_H
