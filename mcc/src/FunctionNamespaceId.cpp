#include "FunctionNamespaceId.h"
#include "ConcreteTableColumn.h"
#include "FuncDeclaration.h"
#include "FunctionScopeId.h"
#include "TypesTable.h"
#include "NamespaceTable.h"
#include "NamespaceName.h"

FunctionNamespaceId::FunctionNamespaceId(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition, TypesTable *types, NamespaceTable *namespaces):DataExtractor(next,prototype,condition) {

	this->types = types;
	this->namespaces = namespaces;
	this->the_scope = new FunctionScopeId(NULL,prototype,NULL,types);
	this->the_namespace = new NamespaceName(NULL,prototype,NULL);
};

FunctionNamespaceId::~FunctionNamespaceId() {
	delete the_scope;
	delete the_namespace;
}

TableColumn* FunctionNamespaceId::handleExtraction(AbstractTree &tree) {
	
	TableColumn *column = prototype->clone(),*tmp_column;
	std::string qualified_id = "qualified_id";
	std::string columnName = "NamespaceName";
	std::string value,qualified,nestedin;
	VTP_TreeP tmp_tree,child;
	int id;
	char buff[12];

	tmp_column = the_scope->extract(tree);
	value = tmp_column->toString();
	delete tmp_column;

	if(value == "<NO_ONE>") {
		//Find the qualified_id
		tmp_tree = VTP_TreeDown(tree.tree,0);
		if(qualified_id == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		    ITERATOR_MAP(VTP_TreeChild, tmp_tree, child);
			if(qualified == "") {
				qualified = VTP_NAME_STRING(VTP_TreeAtomValue(child));
			} else {
				qualified += "::";
				qualified += VTP_NAME_STRING(VTP_TreeAtomValue(child));
			}
			ITERATOR_END_MAP(VTP_TreeChild);
	    }
		//Find the namespace where we are
		tmp_column = the_namespace->extract(tree);
		nestedin = tmp_column->toString();
		delete tmp_column;
		if(qualified == "") {
			//We don't have scope
			if(nestedin != "") {
				id = namespaces->find_id(columnName,nestedin);
				if(id != -1) {
					sprintf(buff,"%d",id);
					value = buff;
				} else {
					value = "<ERROR>";
				}
			} else {
				value = "<NO_ONE>";
			}
		} else {
			//Value contains the scope from de definition
			std::string X,Y,Z;
			std::string::size_type pos;

			X = nestedin;
			Y = qualified;
			pos = X.size();
			if(Y.size() >= X.size() && X == Y.substr(0,pos)) {
				Z = Y;
			} else if(X != "") {
				Z = X + "::" + Y;
			} else {
				Z = Y;
			}

			id = namespaces->find_id(columnName,Z);
			if(id > 0) {
				sprintf(buff,"%d",id);
				value = buff;
			} else {
				value = "<ERROR>";
			}
		}
	} else {
		value = "NULL";
	}
	
	column->init(value,true);
	return column;
}
