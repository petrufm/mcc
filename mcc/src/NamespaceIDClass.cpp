#include "NamespaceIDClass.h"
#include "stdio.h"

NamespaceIDClass::NamespaceIDClass(DataExtractor *next, ConcreteTableColumn *prototype, ClassDeclaration *condition, NamespaceTable *namespaces):DataExtractor(next,prototype,condition) {

	this->namespaces = namespaces;
	this->tmp_condition = new Always();
	this->lnkNamespaceName = new NamespaceName(NULL,prototype,tmp_condition);

}

NamespaceIDClass::~NamespaceIDClass() {

	delete tmp_condition;
	delete lnkNamespaceName;

}

TableColumn* NamespaceIDClass::handleExtraction(AbstractTree &tree) {

	TableColumn *column = lnkNamespaceName->extract(tree);

	std::string name, columnName, value,tmp_value;
	std::string qualified_id	= "qualified_id";
	VTP_TreeP child,tmp_tree;
	int id;
	char buff[12];

	if(qualified_id != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tree.tree,1)))) {
		//When the definition is "class X or anonymous {"
		value = column->toString();
		if(value != "") {
			columnName = "NamespaceName";
			id = namespaces->find_id(columnName,value);
			if(id != -1) {
				sprintf(buff,"%d",id);
				name = buff;
			} else {
				name = "<ERROR>";
			}
		} else {
			name = "<NO_ONE>";
		}
	} else {
		//When the definition is "class name_space::X {"
		//Go into scope operator
		tmp_tree = VTP_TreeDown(VTP_TreeDown(tree.tree,1),0);
	    ITERATOR_MAP(VTP_TreeChild, tmp_tree, child); {
			if(value == "") {
				value = VTP_NAME_STRING(VTP_TreeAtomValue(child));
			} else {
				value += "::";
				value += VTP_NAME_STRING(VTP_TreeAtomValue(child));
			}

	    }
		ITERATOR_END_MAP(VTP_TreeChild);

		//Value contains the scope from de definition
		std::string X,Y,Z;
		std::string::size_type pos;

		X = column->toString();
		Y = value;
		pos = X.size();
		if(Y.size() >= X.size() && X == Y.substr(0,pos)) {
			Z = Y;
		} else if(X != "") {
			Z = X + "::" + Y;
		} else {
			Z = Y;
		}

		columnName = "NamespaceName";
		do {
			id = namespaces->find_id(columnName,Z);
			pos = Z.find_last_of(":");
			if(pos > Z.size()) {
				Z = "";
			} else {
				Z = Z.substr(0,pos - 1);
			}
		} while(id < 0 && Z != "");

		if(id > 0) {
			sprintf(buff,"%d",id);
			name = buff;
		} else if(X == "") {
			name = "<NO_ONE>";
		} else {
			name = "<ERROR>";
		}
	}

	column->init(name,false);

	return column;

}
