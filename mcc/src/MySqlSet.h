#ifndef MYSQLSET_H
#define MYSQLSET_H

class TableRow;

class MySqlSet {

private:

	std::string query;

	std::vector<TableRow*> sequence;

public:
	
	MySqlSet(std::string &colName,std::string &colValue);

	MysqlSet(std::string &query);

	typedef std::vector<TableRow*>::iterator iterator;

	int size();

	iterator begin();

	iterator end();

};
#endif //MYSQLSET