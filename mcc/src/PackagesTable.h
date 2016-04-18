#ifndef PACKAGESTABLE_H
#define PACKAGESTABLE_H

#include "Table.h"

class PackagesTable : public Table {

public:    

    PackagesTable(char* name);

	~PackagesTable();

    virtual void extract(ATCollection &trees);

	virtual void init();

};
#endif //PACKAGESTABLE_H