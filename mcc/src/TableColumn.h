#ifndef TABLECOLUMN_H
#define TABLECOLUMN_H

#include <string>
#include <set>

class Table;

class TableRow;

class TableColumn {

public:

	TableColumn(const std::string &name);

	virtual void init(const std::string &value, bool isUnique, short level = 0, short type = 0) = 0;

    virtual std::string toString() = 0;

	virtual void print(const std::ostream &stream) = 0;

 	virtual bool isUnique() = 0;

	virtual bool isPrintable() = 0;

    virtual TableColumn* clone() = 0;

	virtual void addedTo(Table *table);

	virtual void addedTo(TableRow *row);

	virtual TableRow* getRow();

	virtual std::string getName();

	virtual int getMergeLevel();

	virtual bool merge(TableColumn *col) = 0;

	virtual ~TableColumn();

	virtual const char* getRepresentation(bool exclude_representation = false) = 0;

public:

	static const short MergeByCopy;

	static const short MergeByAdd;

protected:

	Table *table;

	TableRow *row;

	short mergeLevel,mergeType;

	static std::set<std::string> names;

	std::set<std::string>::iterator it_name;

};
#endif //TABLECOLUMN_H
