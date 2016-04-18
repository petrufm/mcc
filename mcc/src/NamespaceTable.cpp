#include "NamespaceTable.h"
#include "NamespaceName.h"
#include "NamespaceDeclaration.h"
#include "MapDeclarations.h"

NamespaceTable::NamespaceTable(char *name):Table(name) {}

NamespaceTable::~NamespaceTable() {}

void NamespaceTable::init() {

	buildColumn(std::string("NamespaceName"));

}

void NamespaceTable::extract(ATCollection &trees) {

	MapDeclarations::VectorOfChain myVector;
	MapDeclarations::VectorOfTrigger myTrigger;

	ConcreteTableColumn columnNamespaceName(std::string("NamespaceName"),true);

	NamespaceDeclaration ndCondition;
	myTrigger.push_back(&ndCondition);

	NamespaceName columnNameExtractors(NULL,&columnNamespaceName,&ndCondition);

	myVector.push_back(&columnNameExtractors);

	MapDeclarations element(trees,&myVector,&myTrigger);

	element.accept(this);

	finalize();

}
