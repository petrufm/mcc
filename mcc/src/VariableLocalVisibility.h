#ifndef VARIABLELOCALVISIBILITY_H
#define VARIABLELOCALVISIBILITY_H
#include "DataExtractor.h"

class ConcreteTableColumn;
class LocalVariable;

class VariableLocalVisibility : public DataExtractor {

public:    

    VariableLocalVisibility(DataExtractor *next, ConcreteTableColumn *prototype, LocalVariable *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //VARIABLELOCALVISIBILITY_H