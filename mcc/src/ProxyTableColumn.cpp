#include "ProxyTableColumn.h"
#include "Table.h"

ProxyTableColumn::ProxyTableColumn(const std::string &name, ConcreteTableColumn *column, DelayedDataExtractor *extractor, DelayedDataExtractor::IContainer *info):TableColumn(name) {

	this->column = column;
	this->extractor = extractor;
	this->info = info;
	this->finalized = false;

}

ProxyTableColumn::~ProxyTableColumn() {

	if(table != NULL) {
		table->unregisterObserver(this);
	}
	delete column;
	if(info != NULL) {
		delete info;
	}

}

void ProxyTableColumn::init(const std::string &value, bool isUnique, short level, short type) {

	column->init(value,isUnique,level,type);

}

std::string ProxyTableColumn::toString() {
	
	return column->toString();

}

void ProxyTableColumn::print(const std::ostream &stream) {

	column->print(stream);

}

bool ProxyTableColumn::isUnique() {

	if(!finalized && column->isUnique()) {
		throw 1;
	} else {
		return column->isUnique();
	}

}

bool ProxyTableColumn::isPrintable() {

	return column->isPrintable();

}

TableColumn* ProxyTableColumn::clone() {

	return new ProxyTableColumn(*it_name, (ConcreteTableColumn*)column->clone(), extractor, info);

}

void ProxyTableColumn::addedTo(Table *table) {

	this->table = table;
	if(!finalized) {
		table->registerObserver(this);
	}

}

void ProxyTableColumn::addedTo(TableRow *row) {

	TableColumn::addedTo(row);
	column->addedTo(row);

}

ProxyTableColumn* ProxyTableColumn::finalize() {
	
	if(finalized) {
		return this;
	}

	if(extractor->finalizeExtraction(column,info)) {
		table->unregisterObserver(this);
		finalized = true;
		table = NULL;
		delete info;
		info = NULL;
		return this;
	} else {
		return NULL;
	};

}

bool ProxyTableColumn::merge(TableColumn *col) {
	if(finalized) {
		return column->merge(col);
	}
	return false;
}

const char* ProxyTableColumn::getRepresentation(bool exclude_representation) {
	return column->getRepresentation(exclude_representation);
}
