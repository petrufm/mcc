#ifndef TABLEROW_H
#define TABLEROW_H

#include "TableColumn.h"
#include <vector>

class TableRow {

public:

	TableRow();

	~TableRow();

    void add(TableColumn *column);

	void print(const std::ostream &stream);

	void freeze();

	std::string getValue(int id);

private:

	typedef std::vector<TableColumn*> ColumnVector;

public:

	typedef ColumnVector::iterator ColumnVectorIterator;

	ColumnVectorIterator begin();

	ColumnVectorIterator end();

private:    

    /**
     * @link aggregation
     * @supplierCardinality 0..* 
     */
	
	ColumnVector *row;
	char **columns;
	char *printFlags; 
	short freezed;

};
#endif //TABLEROW_H
