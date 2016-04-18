#ifndef INHERITANCETABLE_H
#define INHERITANCETABLE_H

#include "Table.h"
#include "TypesTable.h"

class InheritanceTable : public Table {

public:    

    InheritanceTable(char* name, TypesTable *types);

	~InheritanceTable();

	virtual bool insertRow(TableRow* row);

    virtual void extract(ATCollection &trees);

    virtual void init();

private:

	TypesTable *types;

	std::map<std::string,int> vertex_index;
	std::map<int,std::string> index_vertex;

};
#endif //INHERITANCETABLE_H