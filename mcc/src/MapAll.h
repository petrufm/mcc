#ifndef MAPALL_H
#define MAPALL_H

#include "ElementVisitorAdapter.h"

class MapAll : public ElementVisitorAdapter {

public:    

    MapAll(ATCollection &trees, VectorOfChain *chains, VectorOfTrigger *triggers);

	virtual void accept(Table *table);

	void register_observer(VisitProgressObserver *table);

	void notifyUp(VTP_TreeP &tree);

	void notifyDown(VTP_TreeP &tree);


protected:

	virtual void visitTree(AbstractTree &treem, Table *tab, int &skip);

private:

	std::vector<VisitProgressObserver*> observers;

	static void protectedCall(MapAll *object, AbstractTree &tree, Table *table, int &skip);


};
#endif //MAPALL_H