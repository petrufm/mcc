#include "VariableExtern.h"
#include "ConcreteTableColumn.h"
#include "VariablesTable.h"
#include "VariableDeclaration.h"
#include "VariableName.h"
#include "SetOperations.h"
#include "NamespaceTable.h"
#include "NamespaceId.h"

VariableExtern::VariableExtern(DataExtractor *next, ConcreteTableColumn *prototype, VariableDeclaration *condition, VariablesTable *vars,NamespaceTable *namespaces):DelayedDataExtractor(next,prototype,condition) {

	this->vars = vars;
	this->cond = condition;
	this->var_name = new VariableName(NULL,prototype,NULL);
	this->var_namespaces = new NamespaceID(NULL,prototype,NULL,namespaces); 

}

VariableExtern::~VariableExtern() {
	delete var_name;
	delete var_namespaces;
}

TableColumn* VariableExtern::handleExtraction(AbstractTree &tree) {

	TableColumn *column,*tmp_column;
	IContainer *info;
	std::string declaration_specifiers = "declaration_specifiers";
	std::string value;
	std::string name;
	std::string namespace_id;
	bool yes;
	VTP_TreeP tmp_tree,tmp;

	//We have to see if it is extern
	yes = false;
	tmp_tree = tree.tree;
	while(tmp_tree != NULL) {
		tmp = tmp_tree;
		do {
			tmp = VTP_TreeLeft(tmp);
		} while(tmp != NULL && 
			    declaration_specifiers != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)));
		if(tmp != NULL) {
				if(cond->hasStorageClass(tmp,"extern")) {
					yes = true;
				}
				break;
		}
		tmp_tree = VTP_TreeUp(tmp_tree);
	}

	if(yes) {
		//It is extern
		//Find the name
		tmp_column = var_name->extract(tree);
		name = tmp_column->toString();
		delete tmp_column;
		tmp_column = var_namespaces->extract(tree);
		namespace_id = tmp_column->toString();
		delete tmp_column;
		info = new IContainer();
		info->push_back(name);
		info->push_back(tree.file);
		info->push_back(namespace_id);
		column = new ProxyTableColumn(prototype->getName(),(ConcreteTableColumn*)prototype->clone(),this,info);
	} else {
		//It is not extern
		value = "<NO_ONE>";
		column = prototype->clone();
		column->init(value,false);
	}
	return column;
}

bool VariableExtern::finalizeExtraction(TableColumn *column, IContainer *info) {

	std::string name		= (*info)[0];
	std::string file		= (*info)[1];
	std::string namespace_id= (*info)[2];
	SetOperations set_operation;
	Table::RowSet *set1,*set2,*set3;
	std::string varName			= "VariableName";
	std::string kindOf			= "KindOf";
	std::string fileName		= "FileName";
	std::string namespaceName	= "NamespaceID";
	std::string isStatic	=	"IsStatic";
	std::string refersTo	= "RefersTo";
	std::string kind		= "global";
	std::string namespaces	= "<NO_ONE>";
	std::string static_val	= "0";
	std::string refers_to	= "<NO_ONE>";
	std::string value;
	int id;
	char buff[12];

	if(namespace_id != "<NO_ONE>") {
		//If the variable is in a namespace then
		//it will refer a variable in the same namespace or a
		//variable which doesn't have a namespace
		set1 = vars->find_set(varName,name);
		set2 = vars->find_set(kindOf,kind);
		set3 = set_operation.intersection_op(set1,set2);
		delete set1;
		delete set2;
		set1 = vars->find_set(namespaceName,namespace_id);
		set2 = set_operation.intersection_op(set1,set3);
		delete set1;
		delete set3;
		set1 = vars->find_set(refersTo,refers_to);
		set3 = set_operation.intersection_op(set1,set2);
		delete set1;
		delete set2;
		//Set3 contains variables
		//- with the same name
		//- global
		//- the same namespace
		//- it is not extern
		if(set3->size() == 1) {
			id = vars->find_id(*set3->begin());
			sprintf(buff,"%d",id);
			value = buff;
			delete set3;
			column->init(value,false);
			return true;
		} 
		delete set3;
	}

	//It we arrive here then the refered variable has to be global
	//and it does't have a namespace

	//We search for a variable which:
	//- global variable
	//- has the same name
	//- is in the same file
	//- must not be in a namespace
	set1 = vars->find_set(varName,name);
	set2 = vars->find_set(kindOf,kind);
	set3 = set_operation.intersection_op(set1,set2);
	delete set1;
	delete set2;
	set1 = vars->find_set(fileName,file);
	set2 = set_operation.intersection_op(set1,set3);
	delete set1;
	delete set3;
	set1 = vars->find_set(namespaceName,namespaces);
	set3 = set_operation.intersection_op(set1,set2);
	delete set1;
	delete set2;
	set1 = vars->find_set(refersTo,refers_to);
	set2 = set_operation.intersection_op(set1,set3);
	delete set1;
	delete set3;
	if(set2->size() == 1) {
		id = vars->find_id(*set2->begin());
		sprintf(buff,"%d",id);
		value = buff;
		delete set2;
		column->init(value,false);
		return true;
	} else if(set2->size() > 1) {
		value = "<ERROR>";
		delete set2;
		column->init(value,false);
		return true;
	} else {
		delete set2;
		//Now, search for a variable which
		//- is global variable
		//- has the same name
		//- it is not extern nor static
		//- it must not be in a namespace
		set1 = vars->find_set(varName,name);
		set2 = vars->find_set(kindOf,kind);
		set3 = set_operation.intersection_op(set1,set2);
		delete set1;
		delete set2;
		set1 = vars->find_set(namespaceName,namespaces);
		set2 = set_operation.intersection_op(set1,set3);
		delete set1;
		delete set3;
		set1 = vars->find_set(isStatic,static_val);
		set3 = set_operation.intersection_op(set1,set2);
		delete set1;
		delete set2;
		set1 = vars->find_set(refersTo,refers_to);
		set2 = set_operation.intersection_op(set1,set3);
		delete set1;
		delete set3;
		if(set2->size() == 1) {
			id = vars->find_id(*set2->begin());
			sprintf(buff,"%d",id);
			value = buff;
			column->init(value,false);
			delete set2;
			return true;
		} else if(set2->size() > 1) {
			value = "<ERROR>";
			column->init(value,false);
			delete set2;
			return true;
		} else {
			delete set2;
			return false;
		}
	}	
}