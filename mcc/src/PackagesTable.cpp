#include "PackagesTable.h"
#include "PackageName.h"
#include "MapFiles.h"
#include "Always.h"

PackagesTable::PackagesTable(char *name):Table(name) {}

PackagesTable::~PackagesTable() {}

void PackagesTable::init() {

	buildColumn(std::string("PackageName"));

}

void PackagesTable::extract(ATCollection &trees) {
	
	MapFiles::VectorOfChain myVector;
	MapFiles::VectorOfTrigger myTrigger;

	ConcreteTableColumn columnPackageName(std::string("PackageName"),true);

	Always aCondition;
	myTrigger.push_back(&aCondition);

	PackageName columnNameExtractors(NULL,&columnPackageName,&aCondition);

	myVector.push_back(&columnNameExtractors);

	MapFiles element(trees,&myVector,&myTrigger);

	element.accept(this);

	finalize();
}