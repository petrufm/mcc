#ifndef VARIABLEEXTERN_H
#define VARIABLEEXTERN_H

#include "DataExtractor.h"
#include "DelayedDataExtractor.h"

class ConcreteTableColumn;
class VariableDeclaration;
class VariablesTable;
class VariableName;
class NamespaceTable;
class NamespaceID;

class VariableExtern : public DelayedDataExtractor {

public:    

    VariableExtern(DataExtractor *next, ConcreteTableColumn *prototype, VariableDeclaration *condition, VariablesTable *vars, NamespaceTable *namespaces);

	virtual bool finalizeExtraction(TableColumn *column, IContainer *info);

	~VariableExtern();

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	VariablesTable *vars;
	NamespaceID *var_namespaces;
	VariableDeclaration *cond;
	VariableName *var_name;
};
#endif //VARIABLEEXTERN_H

