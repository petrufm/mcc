#ifndef LOCALBODYID_H
#define LOCALBODYID_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class LocalVariable;
class BodyTable;

class LocalBodyId : public DataExtractor {

public:    

    LocalBodyId(DataExtractor *next, ConcreteTableColumn *prototype, LocalVariable *condition, BodyTable *bodies);    

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	BodyTable *bodies;

};
#endif //LOCALBODYID_H