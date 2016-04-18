#include "FindPointerToFunctionType.h"
#include "FindDecoratedType.h"
#include "FindChildByName.h"
#include "FindSignature.h"

//Is receives a parenth_ptr in the context of a pointer to function
std::string FindPointerToFunctionType::find(VTP_TreeP & tree,std::vector<std::string> *types) {

	std::string name;
	std::string member;
	std::string memptr_dcltr			= "memptr_dcltr";
	std::string last_member;
	VTP_TreeP tmp_tree,tmp;
	FindChildByName child_by_name;
	FindSignature signature;

	//Extracting member
	tmp_tree = VTP_TreeDown(tree,0);
	if(memptr_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = child_by_name.find(tmp_tree,"scope");
		if(tmp_tree != NULL) {
			ITERATOR_MAP(VTP_TreeChild, tmp_tree, tmp); {
				member = member + VTP_NAME_STRING(VTP_TreeAtomValue(tmp)) + "::";
				last_member = VTP_NAME_STRING(VTP_TreeAtomValue(tmp));
			}
			ITERATOR_END_MAP(VTP_TreeChild);
		}
	}

	if(last_member != "") {
		types->push_back(last_member);
	}

	//Extracting return type
	FindDecoratedType ret_type;
	tmp_tree = VTP_TreeUp(tree);
	name = ret_type.find(tmp_tree,types);

	//Return name->Member::{returnType}(parameters)
	tmp_tree = VTP_TreeRight(tree);
	if(tmp_tree != NULL) {
		return member + "{" + name + "}" + signature.find(tmp_tree,types);
	} else {
		return member + "{" + name + "}" + "(<ERROR>)";
	}
}
