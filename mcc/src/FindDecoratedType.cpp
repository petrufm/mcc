#include "FindDecoratedType.h"
#include "FindPointerToFunctionType.h"
#include "FindBaseType.h"

std::string FindDecoratedType::find(VTP_TreeP &tree,std::vector<std::string> *types) {

	std::string ptr_dcltr				= "ptr_dcltr";
	std::string ref_dcltr				= "ref_dcltr";
	std::string array_dcltr				= "array_dcltr";
	std::string parenth_dcltr			= "parenth_dcltr";
	std::string func_dcltr				= "func_dcltr";
	std::string declaration_specifiers	= "declaration_specifiers";
	std::string type_id					= "type_id";
	std::string type_specifiers			= "type_specifiers";

	VTP_TreeP tmp_tree,tmp;
	std::string name;
	bool stop = false;

	FindBaseType base_type;
	FindPointerToFunctionType pointer_2_function;

	tmp_tree = tree;

	do {

		if(ptr_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			name = "*" + name;
		} else if(ref_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			name = "&" + name;
		} else if(array_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			name = "[]" + name;
		} else if(parenth_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			name = pointer_2_function.find(tmp_tree,types);
			stop = true;
		}

		tmp = tmp_tree;
		do {
			tmp = VTP_TreeLeft(tmp);
		} while(tmp != NULL && declaration_specifiers != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) &&
			type_specifiers != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) &&
			type_id != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)));

		if(tmp != NULL && !stop) {
			name = base_type.find(tmp,types) + name;
			break;
		}
		
		tmp_tree = VTP_TreeUp(tmp_tree);

	} while(tmp_tree!=NULL && !stop);

	return name;
}
