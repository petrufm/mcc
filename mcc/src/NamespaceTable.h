#ifndef NAMESPACETABLE_H
#define NAMESPACETABLE_H

#include "Table.h"

class NamespaceTable : public Table {

public:    

    NamespaceTable(char* name);

	~NamespaceTable();

    virtual void extract(ATCollection &trees);

    virtual void init();

};
#endif //NAMESPACETABLE_H