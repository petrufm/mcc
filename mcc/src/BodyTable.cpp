#include "BodyTable.h"
#include "MapAll.h"
#include "FuncBody.h"
#include "FileName.h"
#include "FilePositionStart.h"
#include "FilePositionStop.h"
#include "BodyMetrics.h"
#include "PackageId.h"

BodyTable::BodyTable(char *name, PackagesTable *packages):Table(name) {

	this->packages = packages;

}

BodyTable::~BodyTable() {}

void BodyTable::init() {
	buildColumn(std::string("FileName"));
	buildColumn(std::string("StartLine"));
	buildColumn(std::string("StopLine"));
	buildColumn(std::string("PackageId"));
	buildColumn(std::string("Metrics"));
}

void BodyTable::extract(ATCollection &trees) {

	MapAll::VectorOfChain myVector;
	MapAll::VectorOfTrigger myTrigger;
	
	ConcreteTableColumn columnFileName(std::string("FileName"),true);
	ConcreteTableColumn columnStartLine(std::string("StartLine"),true);
	ConcreteTableColumn columnStopLine(std::string("StopLine"),true);
	ConcreteTableColumn columnPackageId(std::string("PackageId"),true);
	ConcreteTableColumn columnMetrics(std::string("Metrics"),true);

	FuncBody fbCondition;
	myTrigger.push_back(&fbCondition);

	FileName columnFileNameExtractor0(NULL,&columnFileName,&fbCondition);

	FilePositionStart columnStartLineExtractor0(NULL,&columnStartLine,&fbCondition);

	FilePositionStop columnStopLineExtractor0(NULL,&columnStopLine,&fbCondition,0);

	PackageID columnPackageIdExtractor0(NULL,&columnPackageId,&fbCondition,packages);

	BodyMetrics columnMetricsExtractor0(NULL,&columnMetrics,&fbCondition);
	
	myVector.push_back(&columnFileNameExtractor0);
	myVector.push_back(&columnStartLineExtractor0);
	myVector.push_back(&columnStopLineExtractor0);
	myVector.push_back(&columnPackageIdExtractor0);
	myVector.push_back(&columnMetricsExtractor0);

	MapAll element(trees,&myVector,&myTrigger);
	element.accept(this);

	finalize();
}
