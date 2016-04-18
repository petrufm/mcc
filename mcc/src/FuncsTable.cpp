#include "FuncsTable.h"
#include "MapAll.h"
#include "TypePointerToFunctionName.h"
#include "TypeIsPointerToFunction.h"
#include "Pointer2Function.h"
#include "PointerToFunctionSignature.h"
#include "PointerToFunctionScopeId.h"
#include "PointerToFunctionReturnType.h"
#include "FuncDeclaration.h"
#include "MethodDeclaration.h"
#include "FunctionName.h"
#include "FunctionSignature.h"
#include "FunctionReturnType.h"
#include "IsRealFunction.h"
#include "FunctionScopeId.h"
#include "FunctionIsVirtual.h"
#include "FunctionIsStatic.h"
#include "FileName.h"
#include "FunctionAccess.h"
#include "FunctionBodyId.h"
#include "FunctionNamespaceId.h"
#include "FunctionParameters.h"


FuncsTable::FuncsTable(char *name, NamespaceTable *namespaces, TypesTable *types, BodyTable *body):Table(name) {
	
	this->namespaces = namespaces;
	this->types = types;
	this->body = body;

}

FuncsTable::~FuncsTable() {}

void FuncsTable::init() {
	buildColumn(std::string("FuncName"));
	buildColumn(std::string("KindOf"));
	buildColumn(std::string("Signature"));
	buildColumn(std::string("ReturnType"));
	buildColumn(std::string("ScopeId"));
	buildColumn(std::string("NamespaceId"));
	buildColumn(std::string("Access"));
	buildColumn(std::string("isStatic"));
	buildColumn(std::string("isVirtual"));
	buildColumn(std::string("BodyId"));
	buildColumn(std::string("Parameters"));
}

void FuncsTable::extract(ATCollection &trees) {

	MapAll::VectorOfChain myVector;
	MapAll::VectorOfTrigger myTrigger;
	
	ConcreteTableColumn columnFuncName(std::string("FuncName"),true);
	ConcreteTableColumn columnKindOf(std::string("KindOf"),true);
	ConcreteTableColumn columnSignature(std::string("Signature"),true);
	ConcreteTableColumn columnRetType(std::string("ReturnType"),true);
	ConcreteTableColumn columnScopeId(std::string("ScopeId"),true);
	ConcreteTableColumn columnNamespaceId(std::string("NamespaceId"),true);
	ConcreteTableColumn columnAccess(std::string("Access"),true);
	ConcreteTableColumn columnisStatic(std::string("isStatic"),true);
	ConcreteTableColumn columnisVirtual(std::string("isVirtual"),true);
	ConcreteTableColumn columnBodyId(std::string("BodyId"),true);
	ConcreteTableColumn columnParameters(std::string("Parameters"),false);

	FuncDeclaration fCondition;
	Pointer2Function p2fCondition;
	MethodDeclaration mCondition;
	myTrigger.push_back(&fCondition);
	myTrigger.push_back(&p2fCondition);
	myTrigger.push_back(&mCondition);

	FunctionName columnNameExtractor0(NULL,&columnFuncName,&fCondition);
	TypePointerToFunctionName columnNameExtractor1(&columnNameExtractor0,&columnFuncName,&p2fCondition);

	IsRealFunction columnKindOfExtractor0(NULL,&columnKindOf,&fCondition);
	TypeIsPointerToFunction columnKindOfExtractor1(&columnKindOfExtractor0,&columnKindOf,&p2fCondition);

	FunctionSignature columnSignatureExtractor0(NULL,&columnSignature,&fCondition);
	PointerToFunctionSignature columnSignatureExtractor1(&columnSignatureExtractor0,&columnSignature,&p2fCondition);
	
	FunctionReturnType columnRetTypeExtractor0(NULL,&columnRetType, &fCondition, types);
	PointerToFunctionReturnType columnRetTypeExtractor1(&columnRetTypeExtractor0,&columnRetType, &p2fCondition, types);

	FunctionScopeId columnScopeIdExtractor0(NULL,&columnScopeId,&fCondition,types);
	PointerToFunctionScopeId columnScopeIdExtractor1(&columnScopeIdExtractor0,&columnScopeId,&p2fCondition,types);

	FunctionNamespaceId columnNamespaceIdExtractor0(NULL,&columnNamespaceId,&fCondition,types,namespaces);

	FunctionAccess columnAccessExtractor0(NULL,&columnAccess,&mCondition);

	FunctionIsStatic columnisStaticExtractor0(NULL,&columnisStatic,&fCondition);

	FunctionIsVirtual columnisVirtualExtractor0(NULL,&columnisVirtual,&mCondition);

	FunctionBodyId columnBodyExtractor0(NULL,&columnBodyId,&fCondition,body);

	FunctionParameters columnParmExtractor0(NULL,&columnParameters,&fCondition);
		
	myVector.push_back(&columnNameExtractor1);
	myVector.push_back(&columnKindOfExtractor1);
	myVector.push_back(&columnSignatureExtractor1);
	myVector.push_back(&columnRetTypeExtractor1);
	myVector.push_back(&columnScopeIdExtractor1);
	myVector.push_back(&columnNamespaceIdExtractor0);
	myVector.push_back(&columnAccessExtractor0);
	myVector.push_back(&columnisStaticExtractor0);
	myVector.push_back(&columnisVirtualExtractor0);
	myVector.push_back(&columnBodyExtractor0);
	myVector.push_back(&columnParmExtractor0);

	MapAll element(trees,&myVector,&myTrigger);
	element.accept(this);

	finalize();
}
