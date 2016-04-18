#ifndef PARAMETERBODYID_H
#define PARAMETERBODYID_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class ParameterVariable;
class BodyTable;

class ParameterBodyID : public DataExtractor {

public:    

    ParameterBodyID(DataExtractor *next, ConcreteTableColumn *prototype, ParameterVariable *condition, BodyTable *bodies);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	BodyTable *bodies;

};
#endif //PARAMETERBODYID_H
