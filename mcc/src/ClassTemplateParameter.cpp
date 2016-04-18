#include "ClassTemplateParameter.h"

bool ClassTemplateParameter::isTriggered(AbstractTree &tree) {

	std::string type_parameter		= "type_parameter";
	std::string parm_decl			= "parm_decl";
	std::string template_parameter	= "template_parameter";
	std::string template_parms		= "template_parms";
	std::string class_head			= "class_head";
	std::string class_decls			= "class_decls";
	std::string extdecl				= "extdecl";
	std::string absdcltr			= "absdcltr";

	VTP_TreeP tmp_tree;

	if(type_parameter != VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree)) &&
	   parm_decl != VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree)) && 
	   template_parameter != VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {
		return false;
	}

	if(parm_decl == VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {
		tmp_tree = VTP_TreeDown(tree.tree,1);
		if(absdcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			return false;
		}
	}

	tmp_tree = VTP_TreeUp(tree.tree);

	if(template_parms != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return false;
	}

	if(extdecl != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeRight(tmp_tree)))) {
		return false;
	}

	tmp_tree = VTP_TreeDown(VTP_TreeDown(VTP_TreeDown(VTP_TreeRight(tmp_tree),0),0),0);

	if(tmp_tree == NULL || class_head != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return false;
	}

	if(class_decls != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeRight(tmp_tree)))) {
		return false;
	}

	return true;

}
