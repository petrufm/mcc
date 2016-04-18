#include "TableRow.h"

TableRow::TableRow() {

	freezed = 0;
	row		= new TableRow::ColumnVector();

}

TableRow::~TableRow() {

	if(!freezed) {

		ColumnVectorIterator i;
		for(i=row->begin(); i!= row->end(); ++i) {
			delete *i;
		}
		delete row;

	} else {

		delete columns;
		delete printFlags;

	}

}

void TableRow::add(TableColumn *column) {

	if(!freezed) {

		row->push_back(column);
		column->addedTo(this);

	} else {

		throw 1;

	}

}

void TableRow::print(const std::ostream &stream) {

	if(!freezed) {

		ColumnVectorIterator i;
		for(i=row->begin(); i!= row->end(); ++i) {
			(*i)->print(stream);
			((std::ostream&)stream) << std::string("\t");
		}

	} else {

		int i;
		for(i = 0; i < freezed; i++) {
			if(printFlags[i / 8] & ( 1 << (i % 8))) {
				((std::ostream&)stream)  << std::string(columns[i]) << std::string("\t");
			}
		}
	}
}

std::string TableRow::getValue(int id) {

	if(!freezed) {

		if(id < row->size()) {
			ColumnVectorIterator i = row->begin();
			return (*(i + id))->toString();
		}
		
		return "<ERROR>";

	} else {

		if(id < freezed) {
			
			return columns[id];

		}
		
		return "<ERROR>";

	}

}

void TableRow::freeze() {

	if(!freezed) {

		int j;
		ColumnVectorIterator i;

		freezed = row->size();
		columns = new char*[freezed];
		printFlags = new char[freezed / 8 + (freezed % 8 ? 1 : 0)];
		j = 0;
		for(i = row->begin(); i != row->end(); ++i) {
			columns[j] = (char*)(*i)->getRepresentation(true);
			printFlags[j / 8] = (*i)->isPrintable() ? 
				printFlags[j / 8] | ( 1 << (j % 8)) :
			    printFlags[j / 8] & ~( 1 << (j % 8));
			delete (*i);
			j++;
		}
	}
}

TableRow::ColumnVectorIterator TableRow::begin() {

	if(freezed) {
		throw 1;
	}

	return row->begin();
}

TableRow::ColumnVectorIterator TableRow::end() {

	if(freezed) {
		throw 1;
	}

	return row->end();
}
