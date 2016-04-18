#ifndef IDENTIFYVARIABLE_H
#define IDENTIFYVARIABLE_H

#include <string>
#include "fast_include.h"
#include "DataExtractor.h"
#include "Table.h"

class VariablesTable;
class BodyTable;
class FuncsTable;
class TypesTable;
class InheritanceTable;
class NamespaceTable;
class TemplateParTypesRelation;

class IdentifyVariable {

public:    

    IdentifyVariable(
		VariablesTable *vars,
		BodyTable *bodies, 
		FuncsTable *funcs,
		TypesTable *types,
		InheritanceTable *inh,
		NamespaceTable *namespaces,
		TemplateParTypesRelation *tp2t);

	~IdentifyVariable();

	std::string findVariable(AbstractTree &tree);
	void setReset();

private:
	
	void fillVars(AbstractTree &tree);
	std::string findRelativeGlobal(AbstractTree &tree, bool checkNamespaces);
	std::string findAbsoluteGlobal(AbstractTree &tree);
	std::string findRelativeAttribute(AbstractTree &tree,std::string &the_classId);
	std::string findAbsoluteAttribute(AbstractTree &tree);
	std::string findLocal(AbstractTree& tree);
	std::string findParameter();
	std::string eliminateDecoration(std::string &typeId);

	VariablesTable *vars;
	BodyTable *bodies;
	FuncsTable *funcs;
	TypesTable *types;
	InheritanceTable *inh;
	NamespaceTable *namespaces;
	TemplateParTypesRelation *tp2t;

	std::string this_bodyId;
	std::string this_namespace;
	std::string this_classId;

	bool reset;
	Table::RowSet *possibleName;
	Table::RowSet *possibleLocal;
	Table::RowSet *possibleParam;
	Table::RowSet *possibleAttrLoc;
	Table::RowSet *possibleAttr;
	Table::RowSet *possibleGlobal;

};
#endif //IDENTIFYVARIABLE_H