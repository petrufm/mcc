#include "PackageID.h"
#include "stdio.h"

PackageID::PackageID(DataExtractor *next, ConcreteTableColumn *prototype,TriggerCondition *condition,PackagesTable *packages):DataExtractor(next,prototype,condition) {

	this->tmp_condition = new Always();
	this->lnkPackageName = new PackageName(NULL,prototype,tmp_condition);
	this->packages = packages;

}

PackageID::~PackageID() {

	delete lnkPackageName;
	delete tmp_condition;

}

TableColumn* PackageID::handleExtraction(AbstractTree &tree) {

	TableColumn *column = lnkPackageName->extract(tree);
	std::string name,search,value;
	int res;
	char buff[12];

	search = "PackageName";
	value = column->toString();
	res = packages->find_id(search,value);
	if(res != -1) {
		sprintf(buff,"%d",res);
		name = buff;
	} else {
		name = "<ERROR>";
	}

	column->init(name,false);

	return column;
}	