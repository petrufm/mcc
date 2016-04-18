#include "TableColumn.h"
#include "TableRow.h"
#include "Table.h"

const short TableColumn::MergeByCopy = 0;
const short TableColumn::MergeByAdd = 1;
std::set<std::string> TableColumn::names;

TableColumn::TableColumn(const std::string &name) {
	
	table	= NULL;
	row		= NULL;
	mergeLevel = 0;
	it_name = names.insert(name).first;
}

std::string TableColumn::getName() {
	return *it_name;
}

void TableColumn::addedTo(Table *table) {
	this->table = table;
}

void TableColumn::addedTo(TableRow *row) {
	this->row = row;
}

TableRow* TableColumn::getRow() {
	return row;
}

int TableColumn::getMergeLevel() {
	return this->mergeLevel;	
}

TableColumn::~TableColumn() {}
