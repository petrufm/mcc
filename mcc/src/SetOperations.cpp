#include "SetOperations.h"
#include <algorithm>

Table::RowSet* SetOperations::intersection_op(Table::RowSet* set1, Table::RowSet* set2) {

	Table::RowSet *res = new Table::RowSet();
	std::insert_iterator<Table::RowSet> res_insert_iterator(*res,res->begin());
	std::set_intersection(set1->begin(),set1->end(),set2->begin(),set2->end(),res_insert_iterator);

	return res;
}

Table::RowSet* SetOperations::union_op(Table::RowSet* set1, Table::RowSet* set2) {

	Table::RowSet *res = new Table::RowSet();
	std::insert_iterator<Table::RowSet> res_insert_iterator(*res,res->begin());
	std::set_union(set1->begin(),set1->end(),set2->begin(),set2->end(),res_insert_iterator);

	return res;
}

Table::RowSet* SetOperations::difference_op(Table::RowSet* set1, TableRow* row) {

	Table::RowSet *res = new Table::RowSet(),*set2 = new Table::RowSet();
	set2->insert(row);
	std::insert_iterator<Table::RowSet> res_insert_iterator(*res,res->begin());
	std::set_difference(set1->begin(),set1->end(),set2->begin(),set2->end(),res_insert_iterator);
	delete set2;

	return res;
}

Table::RowSet* SetOperations::difference_op(Table::RowSet* set1, Table::RowSet* set2) {

	Table::RowSet *res = new Table::RowSet();

	std::insert_iterator<Table::RowSet> res_insert_iterator(*res,res->begin());
	std::set_difference(set1->begin(),set1->end(),set2->begin(),set2->end(),res_insert_iterator);

	return res;
}
