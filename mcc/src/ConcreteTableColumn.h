#ifndef CONCRETETABLECOLUMN_H
#define CONCRETETABLECOLUMN_H

#include "TableColumn.h"
#include <set>
#include <string.h>

class ConcreteTableColumn : public TableColumn {

public:    

    ConcreteTableColumn(const std::string &name, bool printable);

	~ConcreteTableColumn();

	virtual void init(const std::string &value, bool isUnique, short level, short type);

    virtual std::string toString();

	virtual void print(const std::ostream &stream);

 	virtual bool isUnique();

	virtual bool isPrintable();

    virtual TableColumn* clone();

	virtual bool merge(TableColumn *col);

	virtual const char* getRepresentation(bool exclude_representation = false);

private:

	char *value,flag;

	class Comp {
		public:
			bool operator()(char*s1,char*s2) const {
				return strcmp(s1,s2) < 0;
			}
	};
	static std::set<char*,Comp> cache;

	static char* translate(char*);

};
#endif //CONCRETETABLECOLUMN_H
