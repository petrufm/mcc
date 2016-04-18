#ifndef MAPDECLARATIONS_H
#define MAPDECLARATIONS_H

#include "ElementVisitorAdapter.h"

class MapDeclarations : public ElementVisitorAdapter {

public:    

	MapDeclarations(ATCollection &trees, VectorOfChain *chains, VectorOfTrigger *triggers);
    
	virtual void accept(Table *table);

private:

	static void protectedCall(VTP_TreeP tree,CallBackStructure *calling, std::string &file);
};
#endif //MAPDECLARATIONS_H