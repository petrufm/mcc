#include "MapFiles.h"
#include <iostream>

MapFiles::MapFiles(ATCollection &trees, VectorOfChain *chains,VectorOfTrigger *triggers):ElementVisitorAdapter(trees, chains,triggers) {}

void MapFiles::accept(Table *table) {

	ATCollection::iterator i;
	int current,progress;
	int total = trees.size();

	current = 0;
	for(i = trees.begin(); i != trees.end(); ++i) {
		calledBack((*i),table);
		current++;
		progress = current * 100 / total;
		std::cout << progress << "%  " << std::flush << '\r';
	}

}
