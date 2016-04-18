#ifndef BODYTABLE_H
#define BODYTABLE_H

#include "Table.h"

class PackagesTable;

class BodyTable : public Table {

public:    

    BodyTable(char *name, PackagesTable *packages);

	~BodyTable();

    virtual void extract(ATCollection &trees);

	virtual void init();

private:

	PackagesTable *packages;

};
#endif //BODYTABLE_H