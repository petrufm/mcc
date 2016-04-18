#include "MapAll.h"
#include <iostream>

MapAll::MapAll(ATCollection &trees, VectorOfChain *chains, VectorOfTrigger *triggers): ElementVisitorAdapter(trees,chains,triggers) {}

void MapAll::accept(Table *table) {

  	ATCollection::iterator i;
	int skip,current,progress;
	int total = trees.size();

	current = 0;
	for(i = trees.begin(); i != trees.end(); ++i) {
		skip = 0;
		protectedCall(this,*i,table,skip);
		current++;
		progress = current * 100 / total;
		std::cout << progress << "%  " << std::flush << '\r';
	}
	
}

void MapAll::visitTree(AbstractTree &tree, Table *tab, int &skip) {

	VTP_TreeP child;
	AbstractTree nextTree;
	std::string errortree = "errortree",value;
		
	if(errortree == VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {
		value = VTP_STRING_VALUE(VTP_TreeAtomValue(tree.tree));
		for(std::string::iterator i = value.begin(); i != value.end(); ++i) {
			if(*i == '{') skip++;
			else
			if(*i == '}' && skip > 0) skip--;
		}
	}

	if(skip) {
		return;
	}

	if(visitCondition(tree)) {
		if(!calledBack(tree,tab)) return;
	}

    ITERATOR_MAP(VTP_TreeChild, tree.tree, child); {
			notifyDown(child);
			nextTree.directory = tree.directory;
			nextTree.file = tree.file;
			nextTree.tree = child;
			visitTree(nextTree, tab, skip);
			notifyUp(child);
    }
    ITERATOR_END_MAP(VTP_TreeChild);

}

void MapAll::register_observer(VisitProgressObserver *table) {

	observers.push_back(table);

}

void MapAll::notifyDown(VTP_TreeP &tree) {

	for(std::vector<VisitProgressObserver*>::iterator i = observers.begin();
		i != observers.end();
		++i) {
			(*i)->notifyGoDown(tree);
		}
}

void MapAll::notifyUp(VTP_TreeP &tree) {

	for(std::vector<VisitProgressObserver*>::iterator i = observers.begin();
		i != observers.end();
		++i) {
			(*i)->notifyGoUp(tree);
		}
}

void MapAll::protectedCall(MapAll *object, AbstractTree &tree, Table *table, int &skip) {
	//TODO:Can this be made compiler independent?
	//__try {
		object->visitTree(tree,table,skip);
	//} __except(EXCEPTION_EXECUTE_HANDLER) {
	//	cout << endl << " - unpredicted error caught in MapAll. Abord analysis of file " << tree.file.c_str() << flush << endl;
	//}
}
