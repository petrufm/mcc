#include "ConcreteTableColumn.h"

#include<cstdlib>

std::set<char*,ConcreteTableColumn::Comp> ConcreteTableColumn::cache;

char* ConcreteTableColumn::translate(char* word) {

	if(cache.find(word) == cache.end()) {
		cache.insert(strdup(word));
	}

	return *cache.find(word);
}


ConcreteTableColumn::ConcreteTableColumn(const std::string &name, bool printable):TableColumn(name) {

	this->value = translate("<NOT_INIT>");
	flag = printable ? 2 : 0;

}

ConcreteTableColumn::~ConcreteTableColumn() {
}

void ConcreteTableColumn::init(const std::string &value, bool isUnique, short level, short type) {

	this->value = translate((char*)value.c_str());
	this->mergeLevel = level;
	this->mergeType  = type;
	flag = isUnique ? flag | 1 : flag & ~1;

}

std::string ConcreteTableColumn::toString() {
	
	return value;

}

void ConcreteTableColumn::print(const std::ostream &stream) {

	if(flag & 2) {
		((std::ostream&)stream) << std::string(value);
	}

}

bool ConcreteTableColumn::isUnique() {

	return (flag & 1) != 0;

}

TableColumn* ConcreteTableColumn::clone() {

	ConcreteTableColumn *column = new ConcreteTableColumn(*it_name,(flag & 2) == 2);

	return column;

}

bool ConcreteTableColumn::merge(TableColumn *col) {
	
	int tmp_val;
	char buff[12];

	if(mergeType == TableColumn::MergeByCopy) {
		if(mergeLevel > col->getMergeLevel()) {
			col->init(std::string(value),col->isUnique(),mergeLevel,TableColumn::MergeByCopy);
			return true;
		}
	} else if(mergeType == TableColumn::MergeByAdd) {
		if(mergeLevel == 1) {
			tmp_val =  atoi(col->toString().c_str());
			tmp_val += atoi(toString().c_str());
			sprintf(buff,"%d",tmp_val);
			col->init(std::string(buff),col->isUnique(),mergeLevel,TableColumn::MergeByAdd);
			return true;
		}
	}
	return false;
}

const char* ConcreteTableColumn::getRepresentation(bool exclude_representation) {

	if(!exclude_representation) {
		return value;
	} else {
		char *tmp;
		tmp = value;
		value = NULL;
		return tmp;
	}
}

bool ConcreteTableColumn::isPrintable() {
	return (flag & 2) != 0;
}
