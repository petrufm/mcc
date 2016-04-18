#include "VariablesTable.h"
#include "ParameterVariable.h"
#include "AttributeVariable.h"
#include "GlobalVariable.h"
#include "LocalVariable.h"
#include "ConcreteTableColumn.h"
#include "MapAll.h"
#include "VariableName.h"
#include "VariableKindOf.h"
#include "AttributeAccess.h"
#include "VariableType.h"
#include "LocalBodyId.h"
#include "ParameterBodyId.h"
#include "VariableIsConst.h"
#include "VariableIsStatic.h"
#include "AttributeClassId.h"
#include "PackageId.h"
#include "NamespaceId.h"
#include "FileName.h"
#include "FilePositionStart.h"
#include "VariableExtern.h"
#include "VariableLocalVisibility.h"

VariablesTable::VariablesTable(char *name, PackagesTable *packages, NamespaceTable *namespaces, TypesTable *types, BodyTable *bodies):Table(name) {

	this->packages = packages;
	this->types = types;
	this->namespaces = namespaces;
	this->bodies = bodies;

}

VariablesTable::~VariablesTable() {};

void VariablesTable::init() {
	buildColumn(std::string("FileName"));
	buildColumn(std::string("DeclarationLine"));
	buildColumn(std::string("VariableName"));
	buildColumn(std::string("KindOf"));
	buildColumn(std::string("TypeID"));
	buildColumn(std::string("Access"));
	buildColumn(std::string("ClassID"));
	buildColumn(std::string("BodyID"));
	buildColumn(std::string("PackageID"));
	buildColumn(std::string("NamespaceID"));
	buildColumn(std::string("IsStatic"));
	buildColumn(std::string("IsConst"));
	buildColumn(std::string("RefersTo"));
	buildColumn(std::string("VisibleUntilLine"));
}

void VariablesTable::extract(ATCollection &trees) {

	MapAll::VectorOfChain myVector;
	MapAll::VectorOfTrigger myTrigger;
	
	ConcreteTableColumn columnFileName(std::string("FileName"),true);
	ConcreteTableColumn columnDeclarationLine(std::string("DeclarationLine"),true);
	ConcreteTableColumn columnVariableName(std::string("VariableName"),true);
	ConcreteTableColumn columnKindOf(std::string("KindOf"),true);
	ConcreteTableColumn columnTypeID(std::string("TypeID"),true);
	ConcreteTableColumn columnAccess(std::string("Access"),true);
	ConcreteTableColumn columnClassId(std::string("ClassID"),true);
	ConcreteTableColumn columnBodyId(std::string("BodyID"),true);
	ConcreteTableColumn columnPackageId(std::string("PackageID"),true);
	ConcreteTableColumn columnNamespaceId(std::string("NamespaceID"),true);
	ConcreteTableColumn columnIsStatic(std::string("IsStatic"),true);
	ConcreteTableColumn columnIsConst(std::string("IsConst"),true);
	ConcreteTableColumn columnRefersTo(std::string("RefersTo"),true);
	ConcreteTableColumn columnVisibility(std::string("VisibleUntilLine"),false);

	ParameterVariable pCondition;
	AttributeVariable aCondition;
	GlobalVariable gCondition;
	LocalVariable lCondition;
	myTrigger.push_back(&pCondition);
	myTrigger.push_back(&aCondition);
	myTrigger.push_back(&gCondition);
	myTrigger.push_back(&lCondition);

	FileName columnFileNameExtractor0(NULL,&columnFileName,&gCondition);

	FilePositionStart columnPositionExtractor0(NULL,&columnDeclarationLine,&aCondition);
	FilePositionStart columnPositionExtractor1(&columnPositionExtractor0,&columnDeclarationLine,&pCondition);
	FilePositionStart columnPositionExtractor2(&columnPositionExtractor1,&columnDeclarationLine,&lCondition);
	FilePositionStart columnPositionExtractor3(&columnPositionExtractor2,&columnDeclarationLine,&gCondition);

	VariableName columnVariableNameExtractor0(NULL,&columnVariableName,&pCondition);
	VariableName columnVariableNameExtractor1(&columnVariableNameExtractor0,&columnVariableName,&aCondition);
	VariableName columnVariableNameExtractor2(&columnVariableNameExtractor1,&columnVariableName,&gCondition);
	VariableName columnVariableNameExtractor3(&columnVariableNameExtractor2,&columnVariableName,&lCondition);

	VariableKindOf columnKindOfExtractor0(NULL,&columnKindOf,&pCondition);
	VariableKindOf columnKindOfExtractor1(&columnKindOfExtractor0,&columnKindOf,&aCondition);
	VariableKindOf columnKindOfExtractor2(&columnKindOfExtractor1,&columnKindOf,&gCondition);
	VariableKindOf columnKindOfExtractor3(&columnKindOfExtractor2,&columnKindOf,&lCondition);

	VariableType columnTypeIDExtractor0(NULL,&columnTypeID,&pCondition,types);
	VariableType columnTypeIDExtractor1(&columnTypeIDExtractor0,&columnTypeID,&aCondition,types);
	VariableType columnTypeIDExtractor2(&columnTypeIDExtractor1,&columnTypeID,&gCondition,types);
	VariableType columnTypeIDExtractor3(&columnTypeIDExtractor2,&columnTypeID,&lCondition,types);

	AttributeAccess columnAccessExtractor0(NULL,&columnAccess,&aCondition);

	AttributeClassId columnClassIdExtractor0(NULL,&columnClassId,&aCondition,types);

	LocalBodyId columnBodyIdExtractor0(NULL,&columnBodyId,&lCondition,bodies);
	ParameterBodyID columnBodyIdExtractor1(&columnBodyIdExtractor0,&columnBodyId,&pCondition,bodies);

	PackageID columnPackageIdExtractor0(NULL,&columnPackageId,&gCondition,packages);

	NamespaceID columnNamespaceIdExtractor0(NULL,&columnNamespaceId,&gCondition,namespaces);

	VariableIsStatic columnIsStaticExtractor0(NULL,&columnIsStatic,&lCondition);
	VariableIsStatic columnIsStaticExtractor1(&columnIsStaticExtractor0,&columnIsStatic,&pCondition);
	VariableIsStatic columnIsStaticExtractor2(&columnIsStaticExtractor1,&columnIsStatic,&aCondition);
	VariableIsStatic columnIsStaticExtractor3(&columnIsStaticExtractor2,&columnIsStatic,&gCondition);

	VariableIsConst columnIsConstExtractor0(NULL,&columnIsConst,&lCondition);
	VariableIsConst columnIsConstExtractor1(&columnIsConstExtractor0,&columnIsConst,&pCondition);
	VariableIsConst columnIsConstExtractor2(&columnIsConstExtractor1,&columnIsConst,&aCondition);
	VariableIsConst columnIsConstExtractor3(&columnIsConstExtractor2,&columnIsConst,&gCondition);

	VariableExtern columnRefersToExtractor0(NULL,&columnRefersTo,&gCondition,this,namespaces);
	VariableExtern columnRefersToExtractor1(&columnRefersToExtractor0,&columnRefersTo,&lCondition,this,namespaces);

	VariableLocalVisibility columnVisibleColumn0(NULL,&columnVisibility,&lCondition);

	myVector.push_back(&columnFileNameExtractor0);
	myVector.push_back(&columnPositionExtractor3);
	myVector.push_back(&columnVariableNameExtractor3);
	myVector.push_back(&columnKindOfExtractor3);
	myVector.push_back(&columnTypeIDExtractor3);
	myVector.push_back(&columnAccessExtractor0);
	myVector.push_back(&columnClassIdExtractor0);
	myVector.push_back(&columnBodyIdExtractor1);
	myVector.push_back(&columnPackageIdExtractor0);
	myVector.push_back(&columnNamespaceIdExtractor0);
	myVector.push_back(&columnIsStaticExtractor3);
	myVector.push_back(&columnIsConstExtractor3);
	myVector.push_back(&columnRefersToExtractor1);
	myVector.push_back(&columnVisibleColumn0);

	MapAll element(trees,&myVector,&myTrigger);
	element.accept(this);

	finalize();
}
