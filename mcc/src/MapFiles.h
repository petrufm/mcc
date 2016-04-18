#ifndef MAPFILES_H
#define MAPFILES_H

#include "ElementVisitorAdapter.h"

class MapFiles : public ElementVisitorAdapter {

public:    

    MapFiles(ATCollection &trees, VectorOfChain *chains, VectorOfTrigger *triggers);
    
	virtual void accept(Table *table);    

};
#endif //MAPFILES_H