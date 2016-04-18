#include "FindBaseType.h"
#include "FindChildByName.h"
#include "FindSignature.h"

//The function receives a declaration_specifiers, type_specifiers, type_id or
//other non terminal sub-operators of this operators
std::string FindBaseType::find(VTP_TreeP &tree,std::vector<std::string> *types) {

	VTP_TreeP child,tmp;
	std::string typespec = "typespec";
	std::string name;

	name = "";

	FindChildByName child_by_name;
	FindSignature template_arguments;

	if(child_by_name.find(tree,"typespec") != NULL) {
		//It is a (composed) primitive type
		ITERATOR_MAP(VTP_TreeChild, tree, child); {
			if(typespec == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) 
				if(!name.empty()) {
					name = name + " " + VTP_NAME_VALUE(VTP_TreeAtomValue(child));
				} else {
					name = VTP_NAME_VALUE(VTP_TreeAtomValue(child));
				}
			}
		ITERATOR_END_MAP(VTP_TreeChild);
		types->push_back(name);
	} else if(child_by_name.find(tree,"qualified_id") != NULL) {
		//It is a nested type in some namespaces/classes
		//The scope is not considered
		tmp = child_by_name.find(tree,"qualified_id");
		name += find(tmp,types);
	} else if(child_by_name.find(tree,"identifier") != NULL) {
		//It is an identifier for a type
		name = VTP_NAME_STRING(VTP_TreeAtomValue(child_by_name.find(tree,"identifier")));
		types->push_back(name);
	} else if(child_by_name.find(tree,"class") != NULL ) {
		//It is a class
		tmp = VTP_TreeDown(child_by_name.find(tree,"class"),0);
		name = find(tmp,types);
		if(name == "") {
			name = "<ANONYMOUS>";
			types->push_back(name);
		}
	} else if(child_by_name.find(tree,"typename_id")) {
		tmp = child_by_name.find(tree,"typename_id");
		name = find(tmp,types);
	} else if(child_by_name.find(tree,"template_name")) {
		tmp = child_by_name.find(tree,"template_name");
		tmp = child_by_name.find(tmp,"identifier");
		name = VTP_NAME_STRING(VTP_TreeAtomValue(tmp));
		tmp = VTP_TreeRight(tmp);
		name+= template_arguments.find(tmp,types);
		name.replace(name.find_first_of('('),1,"<");
		name.replace(name.find_last_of(')'),1,">");
	}	
	return name;
}
