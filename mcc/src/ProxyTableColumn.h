#ifndef PROXYTABLECOLUMN_H
#define PROXYTABLECOLUMN_H

#include "TableColumn.h"
#include "ConcreteTableColumn.h"
#include "DelayedDataExtractor.h"

class ProxyTableColumn : public TableColumn {

public:

    ProxyTableColumn(const std::string &name, ConcreteTableColumn *column, DelayedDataExtractor *extractor, DelayedDataExtractor::IContainer *info);

	~ProxyTableColumn();

	virtual void init(const std::string &value, bool isUnique, short level = 0, short type = 0);

    virtual std::string toString();

	virtual void print(const std::ostream &stream);

 	virtual bool isUnique();

	virtual bool isPrintable();

    virtual TableColumn* clone();

	virtual void addedTo(Table *table);

	virtual void addedTo(TableRow *row);

	virtual bool merge(TableColumn *col);

	ProxyTableColumn* finalize();

	virtual const char* getRepresentation(bool exclude_representation = false);

private:

    /**
     * @supplierCardinality 1 
     */
	ConcreteTableColumn *column;

	DelayedDataExtractor *extractor;

	DelayedDataExtractor::IContainer *info;

	bool finalized;

};
#endif //PROXYTABLECOLUMN_H
