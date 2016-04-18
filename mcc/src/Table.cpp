#include "Table.h"
#include "SetOperations.h"
#include <iostream>

Table::Table(char* name) {

	table_name = new std::string(name);
	row_id = 1;
	col_counter = 0;

}

Table::~Table() {

	MCMapMapper::iterator j;
	for(j = mMapper.begin(); j != mMapper.end(); ++j) {
		delete (*j).second;
	}
	
	IdMapper::iterator i;
	for(i=iMapper.begin();i != iMapper.end(); ++i) {
		delete (*i).second;
	}

	delete table_name;

}

void Table::print(std::ostream &stream) {

	IdMapper::iterator i;

	for(i=iMapper.begin();i != iMapper.end(); ++i) {
		stream << (*i).first << '\t';
		(*i).second->print(stream);
		stream << '\n';
	}

}

bool Table::insertRow(TableRow* row) {

	TableRow::ColumnVectorIterator i;
	TableRow *mergeRow;
	MCMap *mMap;
	RowSet *set1 = NULL,*set2,*set3;
	SetOperations set_operation;

	try {
		for(i = row ->begin(); i != row->end(); ++i) {
			if((*i)->isUnique()) {
				if(set1 == NULL) {
					set1 = find_set((*i)->getName(),(*i)->toString());
				} else {
					set2 = find_set((*i)->getName(),(*i)->toString());
					set3 = set_operation.intersection_op(set1,set2);
					delete set1;
					delete set2;
					set1 = set3;
				}
			}
		}
	}
	catch(int e) {
		e = 0;
		delayedKey.insert(*i);
		(*i)->addedTo(this);
		if(set1 != NULL) {
			delete set1;
		}
		return true;
	}

	//Duplicate key -> do not insert but execute merge
	if(set1 != NULL && set1->size() != 0) {
		if(set1->size() == 1) {
			mergeRow = *set1->begin();
			int position = 0;
			std::string old_value;
			std::string old_name;
			MCMap::iterator row_it;
			TableRow *tmp_row;
			for(i = row ->begin(); i != row->end(); ++i) {
				old_value = (*(mergeRow->begin() + position))->toString();
				old_name = (*(mergeRow->begin() + position))->getName();
				mMap = mMapper[old_name];
				row_it = mMap->find(old_value.c_str());
				tmp_row = row_it->second;
				if((*i)->merge(*(mergeRow->begin() + position))) {
					//Reindex
					while((*(mergeRow->begin() + position))->getRow() != tmp_row) {
						++row_it;
						tmp_row = row_it->second;
					}
					mMap->erase(row_it);
					mMap->insert(MCMap::value_type((*(mergeRow->begin() + position))->getRepresentation(),tmp_row));
				}
				position++;
			}
		}
		delete set1;
		return false;
	}

	//Unique key -> insert it
	if(set1 != NULL) {
		delete set1;
	}
	for(i = row ->begin(); i != row->end(); ++i) {
		mMap = mMapper[(*i)->getName()];
		(*i)->addedTo(this);
		mMap->insert(MCMap::value_type((*i)->getRepresentation(),row));
	}
	
	iMapper[row_id] = row;
	rMapper[row] = row_id;
	row_id++;

	return true;
}

void Table::buildColumn(const std::string &name) {

	mMapper[name] = new MCMap();
	col_id[name] = col_counter;
	col_counter++;

}

int Table::find_id(const std::string &col, const std::string &value) {

	MCMap *mMap;
	MCMap::iterator it;

	mMap = mMapper[col];
	
	if(mMap != NULL && (it = mMap->find(value.c_str())) != mMap->end()) {
		return rMapper[it->second];
	} else {
		return -1;
	}

}

int Table::find_id(TableRow* row) {

	RowMapper::iterator it;

	if((it = rMapper.find(row)) != rMapper.end()) {
		return it->second;
	} else {
		return -1;
	}

}

Table::RowSet* Table::find_set(const std::string &col, const std::string &value) {

	MCMap *mMap;
	MCMap::iterator it;

	mMap = mMapper[col];
	if(mMap != NULL) {
		it = mMap->find(value.c_str());
		RowSet *set = new RowSet();
		while(it != mMap->end() && (it->first == value)) {
			set->insert(it->second);
			++it;
		}
		return set;
	} else {
		return NULL;
	}
}

void Table::registerObserver(ProxyTableColumn *proxy) {
	observers.insert(proxy);
}

void Table::unregisterObserver(ProxyTableColumn *proxy) {
	observers.erase(proxy);
}

void Table::finalize() {

	ObserversSet::iterator current_it,next_it,j;
	std::string old_value,old_name;
	MCMap *mMap;
	MCMap::iterator row_it;
	TableRow *row;
	ProxyTableColumn *proxy;
	int last_dimension = -1;
	bool modified = false;

	while(!observers.empty()) {
		if(observers.size() == last_dimension && !modified) {
			std::cerr << "Broken cycle in table >" << table_name->c_str() << "<" << std::endl;
			std::cerr << observers.size() << " entities lost/unfilled" << std::endl;
			break;
		}
		last_dimension = observers.size();
		next_it = observers.begin();
		modified = false;
		do {
			current_it = next_it;
			next_it++;
			old_value = (*current_it)->toString();
			old_name = (*current_it)->getName();
			mMap = mMapper[old_name];
			row_it = mMap->find(old_value.c_str());
			row = row_it->second;
			if((proxy = (*current_it)->finalize()) != NULL ) {
				if(delayedKey.find(proxy) == delayedKey.end()) {
					while(proxy->getRow() != row) {
						++row_it;
						row = row_it->second;
				}
					mMap->erase(row_it);
					mMap->insert(MCMap::value_type(proxy->getRepresentation(),row));
				} else {
					row = proxy->getRow();
					if(!insertRow(row)) {
						delete row;
					};
				}
				modified = true;
			};
		} while(next_it != observers.end());
	}

	IdMapper::iterator i;

	for(i=iMapper.begin();i != iMapper.end(); ++i) {
		(*i).second->freeze();
	}

}

std::string Table::getColumnValue(int id, std::string &column) {
	
	TableRow *row = NULL;
	if(id > 0 && id <= iMapper.size() && col_id.find(column) != col_id.end()) {
		row = iMapper[id];
		return row->getValue(col_id[column]);
	}
	return "<ERROR>";
}
