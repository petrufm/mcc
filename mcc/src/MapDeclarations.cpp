#include "MapDeclarations.h"
#include <iostream>

MapDeclarations::MapDeclarations(ATCollection &trees, VectorOfChain *chains,VectorOfTrigger *triggers):ElementVisitorAdapter(trees,chains,triggers) {}

void MapDeclarations::accept(Table *table) {

	ATCollection::iterator i;
	CallBackStructure calling;
	int current,progress;
	int total = trees.size();

	current = 0;
	for(i = trees.begin(); i != trees.end(); ++i) {
		calling.currentIterator = i;
		calling.called_back = this;
		calling.table = table;
		protectedCall((*i).tree,&calling,(*i).file);
		current++;
		progress = current * 100 / total;
		std::cout << progress << "%  " << std::flush << '\r';
	}

}

void MapDeclarations::protectedCall(VTP_TreeP tree,CallBackStructure *calling, std::string &file) {
	//TODO:Can this be made compiler independent?
	//__try {
		C_MapDeclarations(tree,callback,calling);
	//} __except(EXCEPTION_EXECUTE_HANDLER) {
	//	cout << endl << " - unpredicted error caught in MapDeclarations. Abord analysis of file " << file.c_str() << flush << endl;
	//}
}
