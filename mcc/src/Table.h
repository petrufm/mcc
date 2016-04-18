#ifndef TABLE_H
#define TABLE_H

#pragma warning(disable : 4786 4503)

#include "FilesParser.h"
#include "TableRow.h"
#include "ProxyTableColumn.h"

#include <map>
#include <set>

class ProxyTableColumn;

class Table {

public:

    Table(char* name);

	virtual ~Table();

    virtual void print(std::ostream &st);

	virtual bool insertRow(TableRow* row);
    
	virtual void extract(ATCollection &trees) = 0;

	virtual void init() = 0;

	virtual std::string getColumnValue(int id,std::string &column);

private:

	std::string* table_name;
	int row_id;

protected:

	virtual void buildColumn(const std::string &name);

	void finalize();

	class Comp {
	public:
		bool operator()(const char* s1,const char* s2) const {
			return strcmp(s1,s2) < 0;
		}
	};

	typedef std::multimap<const char *,TableRow*,Comp> MCMap;
	typedef std::map<std::string,MCMap*> MCMapMapper;
	typedef std::map<int,TableRow*> IdMapper;
	typedef std::map<TableRow*,int> RowMapper;
	typedef std::set<ProxyTableColumn*> ObserversSet;
	typedef std::set<TableColumn*> DelayedKeySet;

	MCMapMapper mMapper;
	IdMapper iMapper;
	RowMapper rMapper;
	ObserversSet observers;
	DelayedKeySet delayedKey;

	int col_counter;
	std::map<std::string,int> col_id;

public:

	typedef std::set<TableRow*> RowSet;
	
	int find_id(const std::string &col, const std::string &value);

	int find_id(TableRow*);

	RowSet* find_set(const std::string &col, const std::string &value);

	void registerObserver(ProxyTableColumn *proxy);

	void unregisterObserver(ProxyTableColumn *proxy);

};
#endif //TABLE_H
