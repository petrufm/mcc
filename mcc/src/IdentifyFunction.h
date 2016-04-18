#ifndef IDENTIFYFUNCTION_H
#define IDENTIFYFUNCTION_H

#include <string>
#include <vector>
#include "fast_include.h"
#include "DataExtractor.h"
#include "Table.h"

class VariablesTable;
class BodyTable;
class FuncsTable;
class TypesTable;
class InheritanceTable;
class NamespaceTable;
class IdentifyVariable;
class TemplateParTypesRelation;

class IdentifyFunction {

public:    

    IdentifyFunction(
		VariablesTable *vars,
		BodyTable *bodies, 
		FuncsTable *funcs,
		TypesTable *types,
		InheritanceTable *inh,
		NamespaceTable *namespaces,
		TemplateParTypesRelation *tp2t);

	~IdentifyFunction();

	std::string findFunction(AbstractTree &tree, std::vector<std::string> &calledFunctions);
	void setReset();

private:

	void fillVars(AbstractTree &tree);
	void inferSignature(AbstractTree &tree, std::vector<std::string> &signature);
	std::string inferParameterType(AbstractTree &tree);
	std::string findType(std::string &dir, std::string &file, VTP_TreeP tree);
	std::string eliminateDecoration(const std::string &typeId);
	void findGlobalFunc(Table::RowSet *possible, std::map<TableRow*,int> &scores, Table::RowSet *called, bool checkNamespace, std::string &known_qualified);
	void findRelativeMeth(Table::RowSet *possible, std::map<TableRow*,int> &scores, Table::RowSet *called, std::string &type_id);
	int  computeScore(std::string &func_id, std::vector<std::string> &signature);


	VariablesTable *vars;
	BodyTable *bodies;
	FuncsTable *funcs;
	TypesTable *types;
	InheritanceTable *inh;
	NamespaceTable *namespaces;
	TemplateParTypesRelation *tp2t;

	bool reset;

	std::string this_bodyId;
	std::string this_namespace;
	std::string this_classId;

	IdentifyVariable* identifVar;

};
#endif //IDENTIFYFUNCTION_H
