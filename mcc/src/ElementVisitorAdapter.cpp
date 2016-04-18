#include "ElementVisitorAdapter.h"
#include <iostream>

ElementVisitorAdapter::ElementVisitorAdapter(ATCollection &trees, VectorOfChain *chain, VectorOfTrigger *triggers) {
	//Be careful!!! The collection is copied.
	this->trees = trees;
	this->chains = chain;
	this->triggers = triggers;
}

int ElementVisitorAdapter::callback(VTP_TreeP tree, int level, void *param) {

	AbstractTree tmp_tree;

	tmp_tree = *((CallBackStructure*)param)->currentIterator;
	tmp_tree.tree = tree;

	if(((CallBackStructure*)param)->called_back->visitCondition(tmp_tree)) {
		return ((CallBackStructure*)param)->called_back->calledBack(tmp_tree,((CallBackStructure*)param)->table);
	}
	return 1;
}

int ElementVisitorAdapter::calledBack(AbstractTree &tree, Table *table) {

	TableRow *row = new TableRow();

	VectorOfChain::iterator i;

	for(i = chains->begin(); i != chains->end(); ++i) {
		row->add((*i)->extract(tree));
	}

	if(!table->insertRow(row)) {
		delete row;
	}

	return 1;
}

bool ElementVisitorAdapter::visitCondition(AbstractTree &tree) {
	return protectedVisitCondition(triggers,tree);
}

bool ElementVisitorAdapter::protectedVisitCondition(VectorOfTrigger *t,AbstractTree &tree) {

	VectorOfTrigger::iterator i;
	bool res = false;
	//TODO:Can this be made compiler independent?
	//__try {
		for(i = t->begin(); i != t->end(); ++i) {
			res = res || (*i)->isTriggered(tree);
		}
		return res;
	//} __except(EXCEPTION_EXECUTE_HANDLER) {
	//	CIO_PositionS start;
	//	CIO_PositionS stop;
	//	char buff[12];
	//	VTP_TreeGetCoord(tree.tree,&start,&stop);
	//	sprintf(buff,"%d",start.line);
	//	cout << endl << " - unpredicted error caught in trigger: " << tree.file.c_str() << '@' << start.line << flush << endl;
	//	return false;
	//}

}
