#ifndef VARIABLEISSTATIC_H
#define VARIABLEISSTATIC_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class VariableDeclaration;

class VariableIsStatic : public DataExtractor {

public:    

    VariableIsStatic(DataExtractor *next, ConcreteTableColumn *prototype, VariableDeclaration *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	VariableDeclaration *cond;

};
#endif //VARIABLEISSTATIC_H