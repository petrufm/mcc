#include "TypedefDecorator.h"
#include "FindChildByName.h"

bool TypedefDecorator::isTriggered(AbstractTree &tree) {
	
	std::string storage_class			= "storage_class";
	std::string typedef_op				= "typedef";
	std::string declaration_specifiers	= "declaration_specifiers";
	std::string identifier				= "identifier";
	std::string initdecls				= "initdecls";
	std::string parmlist				= "parmlist";
	std::string operator_op;
	VTP_TreeP tmp;
	FindChildByName child_by_name;


	if(identifier != VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {
		return false;
	}

	//Parent must be a particular set of operators
	operator_op = VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(tree.tree)));
	if(	operator_op == "qualified_id" ||
		operator_op == "func_dcltr" ||
		operator_op == "array_dcltr" ||
		operator_op == "ptr_dcltr" ||
		operator_op == "ref_dcltr" ||
		operator_op == "memptr_dcltr" ||
		operator_op == "parenth_dcltr" ||
		operator_op == "dcltr_noinit" ||
		operator_op == "dcltr_affinit" ||
		operator_op == "dcltr_callinit") {

		//It must not be a parameter
		tmp = tree.tree;
		while(tmp != NULL && parmlist != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
			tmp = VTP_TreeUp(tmp);
		}
		if(tmp != NULL) {
			return false;
		}

		//Go to initdecls
		tmp = tree.tree;
		while(tmp != NULL && initdecls != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
			tmp = VTP_TreeUp(tmp);
		}
		if(tmp == NULL) {
			return false;
		}

		tmp = VTP_TreeLeft(tmp);

		if(declaration_specifiers != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
			return false;
		}

		tmp = child_by_name.find(tmp,storage_class);

		if(tmp == NULL) {
			return false;
		}

		if(typedef_op != VTP_NAME_STRING(VTP_TreeAtomValue(tmp))) {
			return false;
		}
		
		return true;

	} 
	
	return false;
}
