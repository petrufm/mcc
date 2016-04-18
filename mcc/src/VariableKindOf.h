#ifndef VARIABLEKINDOF_H
#define VARIABLEKINDOF_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class VariableDeclaration;

class VariableKindOf : public DataExtractor {

public:    

    VariableKindOf(DataExtractor *next, ConcreteTableColumn *prototype, VariableDeclaration *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	VariableDeclaration *cond;

};
#endif //VARIABLEKINDOF_H
