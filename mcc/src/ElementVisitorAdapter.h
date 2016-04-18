#ifndef ELEMENTVISITORADAPTER_H
#define ELEMENTVISITORADAPTER_H

#include "Table.h"
#include "DataExtractor.h"
#include <vector>
#include "VisitProgressObserver.h"

class ElementVisitorAdapter {

public:    

	typedef std::vector<DataExtractor*> VectorOfChain;

	typedef std::vector<TriggerCondition*> VectorOfTrigger;

    ElementVisitorAdapter(ATCollection &trees, VectorOfChain *chains, VectorOfTrigger *triggers);

    virtual void accept(Table *table) = 0;

protected:

	typedef struct _CallBackStructure {
		ElementVisitorAdapter *called_back;
		Table *table;
		ATCollection::iterator currentIterator;
	} CallBackStructure;

    virtual bool visitCondition(AbstractTree &tree);

	virtual int calledBack(AbstractTree &tree, Table *table);

	static int callback(VTP_TreeP tree, int level, void *param);

	ATCollection trees;

private:

	static bool protectedVisitCondition(VectorOfTrigger *t, AbstractTree &tree);

	VectorOfChain *chains;

	VectorOfTrigger *triggers;

};
#endif //ELEMENTVISITORADAPTER_H
