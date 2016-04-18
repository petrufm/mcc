#ifndef SETOPERATIONS_H
#define SETOPERATIONS_H

#include "Table.h"

class SetOperations {

public:    

    Table::RowSet* intersection_op(Table::RowSet* set1, Table::RowSet* set2);

	Table::RowSet* union_op(Table::RowSet* set1, Table::RowSet* set2);

	Table::RowSet* difference_op(Table::RowSet* set1, TableRow* set2);

	Table::RowSet* difference_op(Table::RowSet* set1, Table::RowSet* set2);

};
#endif //SETOPERATIONS_H