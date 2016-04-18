#include "TemplateInstance.h"
#include "FindChildByName.h"

bool TemplateInstance::isTriggered(AbstractTree &tree) {

	std::string type_specifiers			= "type_specifiers";
	std::string type_id					= "type_id";
	std::string declaration_specifiers	= "declaration_specifiers";
	std::string base_class				= "base_class";
	FindChildByName child_by_name;
	VTP_TreeP tmp;

	if(declaration_specifiers == VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree)) ||
	   type_specifiers == VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree)) ||
	   type_id == VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree)) ||
	   base_class == VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {
		
		if(child_by_name.find(tree.tree,"template_name") != NULL) {
			return true;
		};

		if((tmp = child_by_name.find(tree.tree,"qualified_id")) != NULL && 
			child_by_name.find(tmp,"template_name") != NULL) {
			return true;
		};

	}
	return false;
}
