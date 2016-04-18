#include "TypesTable.h"
#include "TypeNamePrimitive.h"
#include "TypeNameClass.h"
#include "TypeIsPrimitive.h"
#include "TypeIsClass.h"
#include "ClassDeclaration.h"
#include "PrimitiveType.h"
#include "FileName.h"
#include "FilePositionStart.h"
#include "FilePositionStop.h"
#include "PackageID.h"
#include "NamespaceIDClass.h"
#include "TypeIsAbstractClass.h"
#include "TypeIsInterfaceClass.h"
#include "TypeIsGenericClass.h"
#include "TypeScopeIDClass.h"
#include "TypeTemplateParameterName.h"
#include "TypeIsTemplateParameter.h"
#include "TypeIsGenericTemplateParameter.h"
#include "TypeScopeIDTemplateParameter.h"
#include "TypePointerToFunctionName.h"
#include "TypeIsPointerToFunction.h"
#include "TypeScopeIDPointerToFunction.h"
#include "Pointer2Function.h"
#include "LibraryType.h"
#include "TypeLibraryName.h"
#include "Never.h"
#include "ColumnMarker.h"
#include "PRADecorator.h"
#include "TypeDecoratedPRAName.h"
#include "TypeIsDecoratedPRA.h"
#include "TemplateInstance.h"
#include "TypeDecoratorTemplateInstanceName.h"
#include "TypeIsDecoratorTemplateInstance.h"
#include "TypeIsDecoratorTypedef.h"
#include "TypeDecoratorTypedefName.h"
#include "Typedefdecorator.h"
#include "NamespaceId.h"
#include "TypeIsLibraryType.h"
#include "TypeScopeIDTypedefDecorator.h"
#include "DecoratedTypeTypedefDecorator.h"
#include "DecoratedTypeTemplateInstance.h"
#include "MapAll.h"
#include "DecoratedTypePRA.h"
#include "TypeTemplateParameterContext.h"
#include "TypeTemplateInstanceContext.h"
#include "TypePointerToFunctionContext.h"
#include "TypePRAContext.h"
#include "TypeTemplateParameterPosition.h" 
#include "TypeLibraryIsGeneric.h"

TypesTable::TypesTable(char *name,PackagesTable *packages,NamespaceTable *namespaces,BodyTable *bodies):Table(name) {

	this->packages = packages;
	this->namespaces = namespaces;
	this->bodies = bodies;

}

TypesTable::~TypesTable() {}

void TypesTable::init() {

	buildColumn(std::string("FileName"));
	buildColumn(std::string("StartPosition"));
	buildColumn(std::string("StopPosition"));
	buildColumn(std::string("TypeName"));
	buildColumn(std::string("KindOf"));
	buildColumn(std::string("PackageID"));
	buildColumn(std::string("NamespaceID"));
	buildColumn(std::string("IsAbstract"));
	buildColumn(std::string("IsInterface"));
	buildColumn(std::string("IsGeneric"));
	buildColumn(std::string("ScopeID"));
	buildColumn(std::string("DecoratedType"));
	buildColumn(std::string("Context"));
	buildColumn(std::string("Position"));
}

void TypesTable::extract(ATCollection &trees) {

	MapAll::VectorOfChain myVector;
	MapAll::VectorOfTrigger myTrigger;

	ConcreteTableColumn columnFileName(std::string("FileName"),true);
	ConcreteTableColumn columnStart(std::string("StartPosition"),true);
	ConcreteTableColumn columnStop(std::string("StopPosition"),true);
	ConcreteTableColumn columnTypeName(std::string("TypeName"),true);
	ConcreteTableColumn columnKindOf(std::string("KindOf"),true);
	ConcreteTableColumn columnPackageId(std::string("PackageID"),true);
	ConcreteTableColumn columnNamespaceId(std::string("NamespaceID"),true);
	ConcreteTableColumn columnIsAbstract(std::string("IsAbstract"),true);
	ConcreteTableColumn columnIsInterface(std::string("IsInterface"),true);
	ConcreteTableColumn columnIsGeneric(std::string("IsGeneric"),true);
	ConcreteTableColumn columnScopeID(std::string("ScopeID"),true);
	ConcreteTableColumn columnDecorated(std::string("DecoratedType"),true);
	ConcreteTableColumn columnContext(std::string("Context"),false);
	ConcreteTableColumn columnPosition(std::string("Position"),false);

	PrimitiveType			ptCondition;
	ClassDeclaration		cdCondition;
	ClassTemplateParameter	tpCondition;
	Pointer2Function		p2fCondition;
	TypedefDecorator		tdefCondition;
	Never					neverCondition;

	myTrigger.push_back(&ptCondition);
	myTrigger.push_back(&cdCondition);
	myTrigger.push_back(&tdefCondition);
	myTrigger.push_back(&tpCondition);
	myTrigger.push_back(&p2fCondition);
	
	FileName columnFileExtractor0(NULL,&columnFileName,&cdCondition);
	FileName columnFileExtractor1(&columnFileExtractor0,&columnFileName,&tpCondition);
	FileName columnFileExtractor2(&columnFileExtractor1,&columnFileName,&tdefCondition);

	FilePositionStart columnStartExtractor0(NULL,&columnStart,&cdCondition);
	FilePositionStart columnStartExtractor1(&columnStartExtractor0,&columnStart,&tpCondition);
	FilePositionStart columnStartExtractor2(&columnStartExtractor1,&columnStart,&tdefCondition);

	FilePositionStop columnStopExtractor0(NULL,&columnStop,&cdCondition,1);
	FilePositionStop columnStopExtractor1(&columnStopExtractor0,&columnStop,&tdefCondition,2);

	TypeNamePrimitive columnNameExtractor0(NULL,&columnTypeName,&ptCondition);
	TypeNameClass columnNameExtractor1(&columnNameExtractor0,&columnTypeName,&cdCondition);
	TypeTemplateParameterName columnNameExtractor2(&columnNameExtractor1,&columnTypeName,&tpCondition);
	TypePointerToFunctionName columnNameExtractor3(&columnNameExtractor2, &columnTypeName, &p2fCondition);
	TypeDecoratorTypedefName columnNameExtractor4(&columnNameExtractor3, &columnTypeName, &tdefCondition);

	TypeIsPrimitive columnKindOfExtractor0(NULL,&columnKindOf,&ptCondition);
	TypeIsClass columnKindOfExtractor1(&columnKindOfExtractor0,&columnKindOf,&cdCondition);
	TypeIsTemplateParameter columnKindOfExtractor2(&columnKindOfExtractor1,&columnKindOf,&tpCondition);
	TypeIsPointerToFunction columnKindOfExtractor3(&columnKindOfExtractor2,&columnKindOf,&p2fCondition);
	TypeIsDecoratorTypedef columnKindOfExtractor4(&columnKindOfExtractor3,&columnKindOf,&tdefCondition);	

	PackageID columnPackageIdExtractor0(NULL,&columnPackageId,&cdCondition,packages);
	PackageID columnPackageIdExtractor1(&columnPackageIdExtractor0,&columnPackageId,&tdefCondition,packages);

	NamespaceIDClass columnNamespaceIdExtractor0(NULL,&columnNamespaceId,&cdCondition,namespaces);
	NamespaceID columnNamespaceIdExtractor1(&columnNamespaceIdExtractor0,&columnNamespaceId,&tdefCondition,namespaces);

	TypeIsAbstractClass columnTypeIsAbstractExtractor0(NULL,&columnIsAbstract,&cdCondition);

	TypeIsInterfaceClass columnTypeIsInterfaceExtractor0(NULL,&columnIsInterface,&cdCondition);

	TypeIsGenericClass columnTypeIsGenericExtractor0(NULL,&columnIsGeneric,&cdCondition);
	TypeIsGenericTemplateParameter columnTypeIsGenericExtractor1(&columnTypeIsGenericExtractor0,&columnIsGeneric,&tpCondition);

	TypeScopeIDClass columnTypeScopeIDExtractor0(NULL,&columnScopeID,&cdCondition,this,bodies);
	TypeScopeIDTemplateParameter columnTypeScopeIDExtractor1(&columnTypeScopeIDExtractor0,&columnScopeID,&tpCondition,this);
	TypeScopeIDPointerToFunction columnTypeScopeIDExtractor2(&columnTypeScopeIDExtractor1,&columnScopeID,&p2fCondition,this);
	TypeScopeIDTypedefDecorator columnTypeScopeIDExtractor3(&columnTypeScopeIDExtractor2,&columnScopeID,&tdefCondition,this,bodies);

	DecoratedTypeTypedefDecorator columnDecoratedExtractor0(NULL,&columnDecorated,&tdefCondition,this);

	TypeTemplateParameterContext columnContextExtractor0(NULL,&columnContext,&tpCondition);
	TypePointerToFunctionContext columnContextExtractor1(&columnContextExtractor0,&columnContext,&p2fCondition,this);

	TypeTemplateParameterPosition columnPositionExtractor0(NULL,&columnPosition,&tpCondition);

	myVector.push_back(&columnFileExtractor2);
	myVector.push_back(&columnStartExtractor2);
	myVector.push_back(&columnStopExtractor1);
	myVector.push_back(&columnNameExtractor4);
	myVector.push_back(&columnKindOfExtractor4);
	myVector.push_back(&columnPackageIdExtractor1);
	myVector.push_back(&columnNamespaceIdExtractor1);
	myVector.push_back(&columnTypeIsAbstractExtractor0);
	myVector.push_back(&columnTypeIsInterfaceExtractor0);
	myVector.push_back(&columnTypeIsGenericExtractor1);
	myVector.push_back(&columnTypeScopeIDExtractor3);
	myVector.push_back(&columnDecoratedExtractor0);
	myVector.push_back(&columnContextExtractor1);
	myVector.push_back(&columnPositionExtractor0);

	MapAll element_first(trees,&myVector,&myTrigger);

	element_first.accept(this);

	LibraryType ltCondition(this);
	PRADecorator praCondition;
	TemplateInstance tInstance;

	myVector.clear();
	myTrigger.clear();
	myTrigger.push_back(&praCondition);
	myTrigger.push_back(&tInstance);
	myTrigger.push_back(&ltCondition);

	ColumnMarker columnFileNameMarker(NULL,&columnFileName,&neverCondition);

	ColumnMarker columnStartMarker(NULL,&columnStart,&neverCondition);

	ColumnMarker columnStopMarker(NULL,&columnStop,&neverCondition);

	TypeDecoratedPRAName columnNameExtractor5(NULL, &columnTypeName, &praCondition);
	TypeDecoratorTemplateInstanceName columnNameExtractor6(&columnNameExtractor5, &columnTypeName, &tInstance);
	TypeLibraryName columnNameExtractor7(&columnNameExtractor6,&columnTypeName,&ltCondition);
		
	TypeIsDecoratedPRA columnKindOfExtractor5(NULL,&columnKindOf,&praCondition);
	TypeIsDecoratorTemplateInstance columnKindOfExtractor6(&columnKindOfExtractor5,&columnKindOf,&tInstance);
	TypeIsLibraryType columnKindOfExtractor7(&columnKindOfExtractor6,&columnKindOf,&ltCondition);
	
	ColumnMarker columnPackageMarker(NULL,&columnPackageId,&neverCondition);
	
	ColumnMarker columnNamespaceMarker(NULL,&columnNamespaceId,&neverCondition);
	
	ColumnMarker columnIsAbstractMarker(NULL,&columnIsAbstract,&neverCondition);
	
	ColumnMarker columnIsInterfaceMarker(NULL,&columnIsInterface,&neverCondition);
	
	TypeLibraryIsGeneric columnIsGenericExtractor0(NULL,&columnIsGeneric,&ltCondition);

	ColumnMarker columnTypeScopeIDMarker(NULL,&columnScopeID,&neverCondition);

	DecoratedTypeTemplateInstance columnDecoratedExtractor1(NULL,&columnDecorated,&tInstance,this);
	DecoratedTypePRA columnDecoratedExtractor2(&columnDecoratedExtractor1,&columnDecorated,&praCondition,this);

	TypeTemplateInstanceContext columnContextExtractor2(NULL,&columnContext,&tInstance,this);
	TypePRAContext columnContextExtractor3(&columnContextExtractor2,&columnContext,&praCondition,this);
	
	ColumnMarker columnPositionMarker(NULL,&columnPosition,&neverCondition);

	myVector.push_back(&columnFileNameMarker);
	myVector.push_back(&columnStartMarker);
	myVector.push_back(&columnStopMarker);
	myVector.push_back(&columnNameExtractor7);
	myVector.push_back(&columnKindOfExtractor7);
	myVector.push_back(&columnPackageMarker);
	myVector.push_back(&columnNamespaceMarker);
	myVector.push_back(&columnIsAbstractMarker);
	myVector.push_back(&columnIsInterfaceMarker);
	myVector.push_back(&columnIsGenericExtractor0);
	myVector.push_back(&columnTypeScopeIDMarker);
	myVector.push_back(&columnDecoratedExtractor2);
	myVector.push_back(&columnContextExtractor3);
	myVector.push_back(&columnPositionMarker);

	MapAll element_second(trees,&myVector,&myTrigger);

	element_second.accept(this);
	
	finalize();
}
