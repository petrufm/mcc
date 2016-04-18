#ifndef ACCESSORBODYID_H
#define ACCESSORBODYID_H

#include "DataExtractor.h"
#include "VisitProgressObserver.h"

class ConcreteTableColumn;
class BodyTable;
class AccessTo;

class AccessorBodyId : public DataExtractor, public VisitProgressObserver {

public:    

    AccessorBodyId(DataExtractor *next, ConcreteTableColumn *prototype, AccessTo *condition, BodyTable *bodies);

	void notifyGoDown(VTP_TreeP &tree);

	void notifyGoUp(VTP_TreeP &tree);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

private:

	BodyTable *bodies;
	bool reset;
	std::string last_bodyId;
};
#endif //ACCESSORBODYID_H
