#include "TemplateArgumentAsType.h"

bool TemplateArgumentAsType::isTriggered(AbstractTree &tree){

	std::string qualified_id		= "qualified_id";
	std::string type_id				= "type_id";
	std::string identifier			= "identifier";
	std::string template_arg_list	= "template_arg_list";
	std::string type_parameter		= "type_parameter";
	std::string type_specifiers			= "type_specifiers";
	std::string declaration_specifiers	= "declaration_specifiers";
	std::string operator_name;
	VTP_TreeP tmp_tree;

	operator_name = VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree));

	if(operator_name != type_id &&
		operator_name != identifier &&
		operator_name != qualified_id) {
		return false;
	}
	
	operator_name = VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(tree.tree)));

	if(operator_name != template_arg_list && operator_name != type_parameter) {
		return false;
	}

	//We are not interested in instances used to specify the scope of a template
	if(operator_name == template_arg_list) {
		tmp_tree = VTP_TreeUp(tree.tree);
		while(tmp_tree != NULL &&
			declaration_specifiers != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
			type_specifiers != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
			type_id != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
				tmp_tree = VTP_TreeUp(tmp_tree);
		}
		if(tmp_tree == NULL) {
			return false;
		}
	}

	return true;
}
